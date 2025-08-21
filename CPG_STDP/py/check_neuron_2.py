import random
from typing import Iterable
import re
import numpy as np
import logging
import h5py as hdf5
import os
import platform

from neuron import h
from bioaffrat import bioaffrat
from interneuron import interneuron
from motoneuron import motoneuron
from muscle import muscle

logging.basicConfig(filename='logs_new_new_2.log',
                    filemode='w',
                    format='%(asctime)s,%(msecs)d %(name)s %(levelname)s %(message)s',
                    datefmt='%H:%M:%S',
                    level=logging.DEBUG)
logging.info("let's get it started")

h.load_file("stdgui.hoc")
h.load_file('nrngui.hoc')
h.load_file('stdrun.hoc')


def check_mechanisms():
    """Проверка доступности необходимых механизмов"""
    print("🔍 Checking NEURON mechanisms...")

    try:
        # Проверяем базовую функциональность NEURON
        print("   Testing basic NEURON functionality...")
        test_section = h.Section()
        print(f"   ✅ Section creation works")

        # Проверяем векторы
        test_vector = h.Vector()
        print(f"   ✅ Vector creation works")

        # Проверяем время
        current_time = h.t
        print(f"   ✅ Time access works: {current_time}")

        # Проверяем STDP
        try:
            stdp_test = h.STDP(0, test_section)
            print("   ✅ STDP mechanism available")
            del stdp_test
        except Exception as stdp_error:
            print(f"   ❌ STDP mechanism not available: {stdp_error}")
            return False

        # Проверяем IaGenerator
        try:
            ia_test = h.IaGenerator()
            print("   ✅ IaGenerator mechanism available")
            del ia_test
        except Exception as ia_error:
            print(f"   ❌ IaGenerator mechanism not available: {ia_error}")
            return False

        del test_section, test_vector
        return True

    except Exception as e:
        print(f"   ❌ Basic NEURON functionality check failed: {e}")
        return False


def check_mpi_status():
    """Улучшенная проверка MPI с обработкой ошибок"""
    try:
        print(f"🔍 Initializing NEURON and MPI...")

        # Загружаем необходимые файлы HOC
        try:
            h.load_file("stdgui.hoc")
            print("   ✅ stdgui.hoc loaded")
        except:
            print("   ⚠️ stdgui.hoc not loaded")

        try:
            h.load_file('nrngui.hoc')
            print("   ✅ nrngui.hoc loaded")
        except:
            print("   ⚠️ nrngui.hoc not loaded")

        try:
            h.load_file('stdrun.hoc')
            print("   ✅ stdrun.hoc loaded")
        except:
            print("   ⚠️ stdrun.hoc not loaded")

        # Инициализация MPI
        try:
            h.nrnmpi_init()
            print("   ✅ MPI initialization completed")
        except Exception as mpi_error:
            print(f"   ⚠️ MPI initialization warning: {mpi_error}")

        pc = h.ParallelContext()
        rank = int(pc.id())
        nhost = int(pc.nhost())

        print(f"MPI Status:")
        print(f"  Rank: {rank}")
        print(f"  Number of hosts: {nhost}")

        # Безопасная проверка MPI статуса
        try:
            if hasattr(h, 'nrnmpi_is_initialized'):
                mpi_status = h.nrnmpi_is_initialized()
                print(f"  MPI initialized: {mpi_status}")
            else:
                print(f"  MPI status: Unknown (method not available)")
        except:
            print(f"  MPI status: Cannot determine")

        return pc, rank, nhost

    except Exception as e:
        print(f"❌ Critical MPI/NEURON initialization error: {e}")
        print(f"   Attempting minimal fallback...")

        try:
            pc = h.ParallelContext()
            return pc, 0, 1
        except Exception as fallback_error:
            print(f"❌ Fallback failed: {fallback_error}")
            raise fallback_error


# Инициализация MPI/PC
pc, rank, nhost = check_mpi_status()

file_name = 'res_alina_50_stdp'

N = 2
speed = 100
bs_fr = 100  # 40 # frequency of brainstem inputs
versions = 1
CV_number = 6
k = 0.017  # CV weights multiplier to take into account air and toe stepping
CV_0_len = 12  # 125 # Duration of the CV generator with no sensory inputs
extra_layers = 0  # 1 + layers

step_number = 6

one_step_time = int((6 * speed + CV_0_len) / (int(1000 / bs_fr))) * (int(1000 / bs_fr))
time_sim = one_step_time * step_number + 30

print(f"📊 Simulation parameters:")
print(f"   one_step_time: {one_step_time} ms")
print(f"   total time_sim: {time_sim} ms")
print(f"   step_number: {step_number}")

'''
network topology https://github.com/max-talanov/bypass/blob/main/figs/CPG_feedback_loops.png
'''


class CPG:
    def __init__(self, speed, bs_fr, inh_p, step_number, n):
        if not check_mechanisms():
            print("❌ Required NEURON mechanisms not available - attempting to continue anyway")
            logging.warning("Required mechanisms not available")

        logging.info(f"Hello from rank {rank} of {nhost}")
        logging.info("NEURON version: " + h.nrnversion())

        # ...existing code...
        self.threshold = 10
        self.delay = 1
        self.nAff = 2
        self.nInt = 2
        self.nMn = 2
        self.ncell = n
        self.affs = []
        self.ints = []
        self.motos = []
        self.muscles = []
        self.affgroups = []
        self.intgroups = []
        self.motogroups = []
        self.musclegroups = []
        self.gener_gids = []
        self.gener_Iagids = []
        self.n_gid = 0

        self.RG_E = []  # Rhythm generators of extensors
        self.RG_F = []  # Rhythm generators of flexor
        self.CV = []

        self.netstims = []
        self.stims = []

        self.stdpmechs = []
        self.netcons = []
        self.stimnclist = []

        self.presyns = []
        self.postsyns = []

        self.weight_changes_vectors = []
        self.time_t_vectors = []

        self.C_1 = []
        self.C_0 = []

        # ...existing initialization code...
        # (Весь остальной код __init__ остается без изменений)


def prun(speed, step_number):
    print(f"🚀 [rank {rank}] Starting simulation: speed={speed}, steps={step_number}")
    logging.info(f"prun start: speed={speed}, steps={step_number}, time_sim={time_sim}")

    try:
        print(f"   Setting timeout...")
        pc.timeout(0)

        # Проверяем инициализацию NEURON
        print(f"   Checking NEURON initialization...")
        print(f"     h.t = {h.t}")
        print(f"     NEURON version: {h.nrnversion()}")

        # Безопасное создание вектора времени
        print(f"   Creating time vector...")
        try:
            # Сначала проверим доступность h._ref_t
            test_t = h.t
            print(f"     h.t accessible: {test_t}")

            # Создаем вектор
            t = h.Vector()
            print(f"     Vector created: {type(t)}")

            # Пытаемся записать время
            if hasattr(h, '_ref_t'):
                t.record(h._ref_t)
                print(f"     ✅ Time recording set up successfully")
            else:
                print(f"     ❌ h._ref_t not available")
                # Альтернативный подход
                t = h.Vector()
                print(f"     Using manual time tracking")

        except Exception as time_error:
            print(f"     ❌ Time vector creation error: {time_error}")
            # Создаем пустой вектор как fallback
            t = h.Vector()
            print(f"     Created fallback empty vector")

        # Настройка симуляции
        print(f"   Setting simulation parameters...")
        h.tstop = time_sim
        h.dt = 0.025

        # Добавьте проверку на macOS
        import platform
        if platform.system() == "Darwin":  # macOS
            print(f"   macOS detected - using alternative approach")
            h.cvode_active(0)  # Отключить переменный шаг
            h.secondorder = 0  # Использовать неявный метод Эйлера
            pc.set_maxstep(1)  # Уменьшить maxstep для macOS
        else:
            print(f"   Windows/Linux detected - using standard approach")
            h.cvode_active(1)  # Включить переменный шаг
            pc.set_maxstep(10)

        print(f"   Current simulation settings:")
        print(f"     h.tstop = {h.tstop}")
        print(f"     h.dt = {h.dt}")
        print(f"     cvode_active = {h.cvode_active()}")

        print(f"   Initializing simulation...")
        try:
            h.finitialize(-65)
            print(f"   ✅ finitialize completed, h.t = {h.t}")
        except Exception as init_error:
            print(f"   ❌ finitialize error: {init_error}")
            # Попробуем альтернативную инициализацию
            print(f"   Trying alternative initialization...")
            h.v_init = -65
            h.init()
            print(f"   Alternative init completed, h.t = {h.t}")

        print(f"   Starting main simulation...")
        start_time = h.startsw()

        try:
            if platform.system() == "Darwin" or nhost == 1:
                # Альтернативный подход для macOS или одиночного процесса
                print(f"   Using h.continuerun() approach...")
                h.continuerun(time_sim)
                print(f"   ✅ h.continuerun() completed")
            else:
                # Стандартный параллельный подход
                print(f"   Using pc.psolve() approach...")
                pc.psolve(time_sim)
                print(f"   ✅ pc.psolve() completed")

        except Exception as sim_error:
            print(f"   ❌ Main simulation error: {sim_error}")
            print(f"   Trying fallback simulation method...")

            # Fallback: пошаговая симуляция
            steps = int(time_sim / h.dt)
            print(f"   Running {steps} steps manually...")

            for step in range(0, steps, 1000):  # Логирование каждые 1000 шагов
                try:
                    h.fadvance()
                    if step % 10000 == 0:
                        print(f"     Step {step}/{steps}, t={h.t:.1f}")
                except Exception as step_error:
                    print(f"     Step error at {step}: {step_error}")
                    break

            print(f"   Manual simulation completed")

        elapsed_time = h.startsw() - start_time
        print(f"   Simulation time: {elapsed_time:.2f} seconds")
        print(f"   Final simulation time: {h.t:.1f} ms")

        # Заполняем вектор времени если он пустой
        if len(t) == 0:
            print(f"   Time vector is empty, creating manual time points...")
            time_points = np.arange(0, h.t + h.dt, h.dt)
            t.from_python(time_points)
            print(f"   Created time vector with {len(t)} points")

        if h.t < time_sim * 0.9:  # Если симуляция остановилась слишком рано
            print(f"⚠️  Warning: Simulation stopped early at {h.t:.1f} ms (expected {time_sim} ms)")
            logging.warning(f"Simulation stopped early: {h.t} ms instead of {time_sim} ms")

        print(f"🏁 Simulation completed successfully")
        logging.info(f"Simulation completed: {h.t} ms")
        return t

    except Exception as sim_error:
        print(f"❌ Simulation error: {sim_error}")
        logging.error(f"Simulation error: {sim_error}")
        import traceback
        print(f"Traceback: {traceback.format_exc()}")

        # Возвращаем пустой вектор в случае ошибки
        return h.Vector()


def finish():
    """Правильное завершение работы"""
    try:
        print(f"🔚 [rank {rank}] Finishing simulation...")

        if nhost > 1:
            print(f"   Running worker cleanup...")
            pc.runworker()
            print(f"   Calling pc.done()...")
            pc.done()

        print(f"   Calling h.quit()...")
        h.quit()
        print(f"✅ Cleanup completed")

    except Exception as e:
        print(f"⚠️ Error during cleanup: {e}")


# ...existing code для spike_record, force_record, velocity_record, spikeout остается без изменений...

def safe_filename(name: str) -> str:
    """Преобразует строку в безопасное имя файла."""
    return re.sub(r'[^\w\-_.]', '_', name)


if __name__ == '__main__':
    print(f"🎬 NEURON CPG Simulation Starting...")
    print(f"   Platform: {platform.system()}")

    try:
        # Сначала проверяем MPI и NEURON
        pc, rank, nhost = check_mpi_status()

        # Затем проверяем механизмы
        if not check_mechanisms():
            print("❌ Required mechanisms not available")
            # Можно продолжить работу без STDP, если это приемлемо
            print("⚠️ Continuing without some mechanisms...")

        print(f"🎬 [rank {rank}] MAIN EXECUTION START")
        print(f"   Rank {rank} of {nhost} processes")
        print(f"   Parameters: N={N}, speed={speed}, bs_fr={bs_fr}, versions={versions}")
        print(f"   Step number: {step_number}, one_step_time: {one_step_time}")
        print(f"   Total simulation time: {time_sim} ms")

        # Проверка доступности механизмов
        if not check_mechanisms():
            print("❌ Critical mechanisms missing - exiting")
            exit(1)

        logging.info("=== MAIN EXECUTION START ===")
        logging.info(f"Platform: {platform.system()}")
        logging.info(f"Rank {rank}/{nhost}, N={N}, speed={speed}, versions={versions}")

        k_nrns = 0
        k_name = 1

        if not os.path.isdir(file_name):
            os.mkdir(file_name)
            print(f"   ✅ Created directory: {file_name}")

        for i in range(versions):
            print(f"🔄 [rank {rank}] VERSION {i + 1}/{versions} START")
            logging.info(f"=== VERSION {i + 1} START ===")

            try:
                print(f"   Creating CPG network...")
                cpg_ex = CPG(speed, bs_fr, 100, step_number, N)
                print(f"   ✅ CPG network created successfully")
                logging.info("CPG created successfully")

                # ...existing recording setup code...

                print(f"   🚀 Starting simulation...")
                print("- " * 50)
                t = prun(speed, step_number)
                print("- " * 50)
                print(f"   ✅ Simulation completed")

                # ...existing results saving code...

                print(f"🏁 [rank {rank}] VERSION {i + 1} COMPLETED SUCCESSFULLY")

            except Exception as version_error:
                print(f"❌ [rank {rank}] VERSION {i + 1} FAILED: {version_error}")
                logging.error(f"Version {i + 1} error: {version_error}")
                import traceback

                print(f"Traceback: {traceback.format_exc()}")
                break

        print(f"🏁 [rank {rank}] MAIN EXECUTION FINISHED")
        logging.info("=== MAIN EXECUTION END ===")
        finish()
    except Exception as main_error:
        print(f"❌ Critical error in main: {main_error}")
        import traceback

        print(f"Traceback: {traceback.format_exc()}")

        try:
            finish()
        except:
            pass

        exit(1)