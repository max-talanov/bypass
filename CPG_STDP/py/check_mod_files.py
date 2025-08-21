from neuron import h
import traceback


def detailed_mechanism_check():
    print("🔍 Detailed mechanism check:")

    # 1. Проверяем базовые механизмы
    basic_mechanisms = ['hh', 'pas', 'extracellular']
    for mech in basic_mechanisms:
        try:
            test_sec = h.Section()
            test_sec.insert(mech)
            print(f"   ✅ {mech}: available")
            del test_sec
        except Exception as e:
            print(f"   ❌ {mech}: {e}")

    # 2. Проверяем STDP механизм
    print(f"\n   STDP mechanism test:")
    try:
        dummy = h.Section()
        print(f"     Creating section... ✅")

        stdp = h.STDP(0, dummy)
        print(f"     Creating STDP(0, section)... ✅")
        print(f"     STDP type: {type(stdp)}")

        # Проверяем атрибуты STDP
        if hasattr(stdp, 'synweight'):
            print(f"     synweight attribute: ✅")
        else:
            print(f"     synweight attribute: ❌")

        del stdp, dummy

    except Exception as stdp_error:
        print(f"     ❌ STDP error: {stdp_error}")
        print(f"     Traceback: {traceback.format_exc()}")

    # 3. Проверяем IaGenerator
    print(f"\n   IaGenerator mechanism test:")
    try:
        ia_gen = h.IaGenerator()
        print(f"     Creating IaGenerator()... ✅")
        print(f"     IaGenerator type: {type(ia_gen)}")

        # Проверяем атрибуты
        attrs_to_check = ['start', 'interval', 'number', 'fhill', 'fhill2']
        for attr in attrs_to_check:
            if hasattr(ia_gen, attr):
                print(f"     {attr} attribute: ✅")
            else:
                print(f"     {attr} attribute: ❌")

        del ia_gen

    except Exception as ia_error:
        print(f"     ❌ IaGenerator error: {ia_error}")
        print(f"     Traceback: {traceback.format_exc()}")

    # 4. Проверяем загрузку .mod файлов
    print(f"\n   Checking .mod compilation:")
    try:
        # Пытаемся найти nrnivmodl или другие признаки скомпилированных механизмов
        import os
        current_dir = os.getcwd()
        print(f"     Current directory: {current_dir}")

        # Ищем файлы механизмов
        mod_files = []
        dll_files = []
        for file in os.listdir('./mod_files'):
            if file.endswith('.mod'):
                mod_files.append(file)
            elif file.endswith('.dll') or file.endswith('.so'):
                dll_files.append(file)

        print(f"     .mod files found: {len(mod_files)} - {mod_files}")
        print(f"     .dll/.so files found: {len(dll_files)} - {dll_files}")

        # Проверяем наличие nrnmech.dll
        if 'nrnmech.dll' in dll_files:
            print(f"     ✅ nrnmech.dll found - mechanisms should be available")
        else:
            print(f"     ❌ nrnmech.dll not found - may need to compile mechanisms")

    except Exception as mod_error:
        print(f"     ❌ .mod check error: {mod_error}")


if __name__ == '__main__':
    detailed_mechanism_check()