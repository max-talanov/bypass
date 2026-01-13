import nest
import numpy as np

# Проверка версии NEST
print(f"Версия NEST: {nest.__version__}")

# Сброс ядра NEST
nest.ResetKernel()

# Создаем два нейрона типа integrate-and-fire
neuron1 = nest.Create("iaf_psc_alpha")
neuron2 = nest.Create("iaf_psc_alpha")

# Создаем генератор спайков
spike_gen = nest.Create("spike_generator")
nest.SetStatus(spike_gen, {"spike_times": [10.0, 50.0, 100.0]})

# Создаем вольтметр для записи мембранного потенциала
voltmeter = nest.Create("voltmeter")
nest.SetStatus(voltmeter, {"withtime": True, "record_from": ["V_m"]})

# Соединяем генератор спайков с первым нейроном
nest.Connect(spike_gen, neuron1, syn_spec={"weight": 1000.0})

# Соединяем первый нейрон со вторым
nest.Connect(neuron1, neuron2, syn_spec={"weight": 1000.0})

# Подключаем вольтметр ко второму нейрону
nest.Connect(voltmeter, neuron2)

# Запускаем симуляцию на 150 мс
nest.Simulate(150.0)

# Получаем данные
data = nest.GetStatus(voltmeter)[0]["events"]
times = data["times"]
voltages = data["V_m"]

# Сохраняем время в отдельный HDF5 файл
import h5py
with h5py.File('time.h5', 'w') as f:
    f['/res_nest/'] = times

# Сохраняем напряжение в отдельный HDF5 файл
with h5py.File('voltage.h5', 'w') as f:
    f['/res_nest/'] = voltages

print("Симуляция NEST успешно завершена!")
print("Время сохранено в файл 'time.h5'")
print("Напряжение сохранено в файл 'voltage.h5'")

