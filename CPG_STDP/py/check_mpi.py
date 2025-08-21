import platform
import subprocess
import sys
from neuron import h


def check_mpi_installation():
    """Детальная проверка MPI на macOS"""
    print(f"🔍 Detailed MPI diagnostics on {platform.system()}:")

    # 1. Проверяем версию системы
    if platform.system() == "Darwin":
        print(f"   macOS version: {platform.mac_ver()[0]}")
        print(f"   Architecture: {platform.machine()}")

    # 2. Проверяем установленные MPI библиотеки
    mpi_commands = ['mpirun --version', 'mpiexec --version', 'which mpirun', 'which mpiexec']

    for cmd in mpi_commands:
        try:
            result = subprocess.run(cmd.split(), capture_output=True, text=True, timeout=5)
            if result.returncode == 0:
                print(f"   ✅ {cmd}: {result.stdout.strip()[:100]}")
            else:
                print(f"   ❌ {cmd}: {result.stderr.strip()[:100]}")
        except Exception as e:
            print(f"   ❌ {cmd}: {e}")

    # 3. Проверяем переменные окружения
    import os
    mpi_env_vars = ['OMPI_MCA_btl', 'OMPI_MCA_plm', 'MPICH_VERSION', 'I_MPI_ROOT']
    print(f"   Environment variables:")
    for var in mpi_env_vars:
        value = os.environ.get(var, 'Not set')
        print(f"     {var}: {value}")

    # 4. Проверяем NEURON MPI capabilities
    print(f"   NEURON MPI capabilities:")
    try:
        print(f"     NEURON version: {h.nrnversion()}")

        # Проверяем доступность MPI функций
        mpi_functions = [
            ('h.nrnmpi_init', hasattr(h, 'nrnmpi_init')),
            ('h.nrnmpi_is_initialized', hasattr(h, 'nrnmpi_is_initialized')),
            ('h.nrnmpi_numprocs', hasattr(h, 'nrnmpi_numprocs')),
            ('h.nrnmpi_myid', hasattr(h, 'nrnmpi_myid')),
        ]

        for func_name, available in mpi_functions:
            status = "✅" if available else "❌"
            print(f"     {func_name}: {status}")

    except Exception as neuron_error:
        print(f"     ❌ NEURON MPI check failed: {neuron_error}")


def test_mpi_initialization():
    """Тестирование различных способов инициализации MPI"""
    print(f"\n🧪 Testing MPI initialization methods:")

    # Метод 1: Стандартная инициализация
    try:
        print(f"   Method 1: Standard h.nrnmpi_init()")
        h.nrnmpi_init()
        pc = h.ParallelContext()
        rank = int(pc.id())
        nhost = int(pc.nhost())
        print(f"   ✅ Success: rank={rank}, nhost={nhost}")

        # Проверяем статус
        if hasattr(h, 'nrnmpi_is_initialized'):
            init_status = h.nrnmpi_is_initialized()
            print(f"   MPI initialized: {init_status}")

        return pc, rank, nhost, "standard"

    except Exception as std_error:
        print(f"   ❌ Standard method failed: {std_error}")

    # Метод 2: Без MPI инициализации
    try:
        print(f"   Method 2: ParallelContext without MPI")
        pc = h.ParallelContext()
        rank = 0
        nhost = 1
        print(f"   ✅ Success (single process): rank={rank}, nhost={nhost}")
        return pc, rank, nhost, "no_mpi"

    except Exception as no_mpi_error:
        print(f"   ❌ No-MPI method failed: {no_mpi_error}")

    # Метод 3: Принудительная одиночная инициализация
    try:
        print(f"   Method 3: Force single process mode")
        import os
        os.environ['NEURON_MPI'] = '0'  # Отключаем MPI в NEURON

        pc = h.ParallelContext()
        rank = 0
        nhost = 1
        print(f"   ✅ Success (forced single): rank={rank}, nhost={nhost}")
        return pc, rank, nhost, "forced_single"

    except Exception as forced_error:
        print(f"   ❌ Forced single method failed: {forced_error}")

    raise RuntimeError("All MPI initialization methods failed")


def check_parallel_context_capabilities(pc, rank, nhost, method):
    """Проверка возможностей ParallelContext"""
    print(f"\n🔧 Testing ParallelContext capabilities (method: {method}):")

    capabilities = {}

    # Тестируем основные функции
    test_functions = [
        ('pc.id()', lambda: pc.id()),
        ('pc.nhost()', lambda: pc.nhost()),
        ('pc.timeout(0)', lambda: pc.timeout(0)),
        ('pc.set_maxstep(10)', lambda: pc.set_maxstep(10)),
        ('pc.barrier()', lambda: pc.barrier()),
        ('pc.gid_exists(999)', lambda: pc.gid_exists(999)),
    ]

    for func_name, func in test_functions:
        try:
            result = func()
            capabilities[func_name] = True
            print(f"   ✅ {func_name}: {result}")
        except Exception as e:
            capabilities[func_name] = False
            print(f"   ❌ {func_name}: {e}")

    # Специальные тесты для macOS
    if platform.system() == "Darwin":
        print(f"   macOS specific tests:")

        # Тест создания простого объекта
        try:
            test_gid = 12345
            pc.set_gid2node(test_gid, rank)
            print(f"   ✅ set_gid2node works")
            capabilities['set_gid2node'] = True
        except Exception as e:
            print(f"   ❌ set_gid2node failed: {e}")
            capabilities['set_gid2node'] = False

    return capabilities


if __name__ == '__main__':
    # Запускаем диагностику
    check_mpi_installation()

    try:
        pc, rank, nhost, method = test_mpi_initialization()
        capabilities = check_parallel_context_capabilities(pc, rank, nhost, method)

        print(f"\n📊 Summary:")
        print(f"   Method used: {method}")
        print(f"   Rank: {rank}, Hosts: {nhost}")
        print(f"   Capabilities: {sum(capabilities.values())}/{len(capabilities)} working")

        # Рекомендации для macOS
        if platform.system() == "Darwin":
            print(f"\n💡 macOS Recommendations:")
            if method == "no_mpi" or method == "forced_single":
                print(f"   ✅ Use single-process mode for macOS")
                print(f"   ✅ Avoid pc.psolve() - use h.continuerun()")
                print(f"   ✅ Set h.cvode_active(0) for stability")
            else:
                print(f"   ⚠️ MPI working but may be unstable on macOS")

    except Exception as main_error:
        print(f"\n❌ All tests failed: {main_error}")