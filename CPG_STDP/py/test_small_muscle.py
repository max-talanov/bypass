from neuron import h, gui
import matplotlib.pyplot as plt
from muscle import muscle
from interneuron import interneuron

from bokeh.plotting import figure, show, output_notebook
from bokeh.layouts import column

from bokeh.plotting import output_file
# output_file("muscle_plot.html")

output_notebook()  # Для Jupyter Notebook. Если не используешь — можно заменить на output_file("muscle_plot.html")

# Инициализация двух мышц
cell1 = muscle()
cell2 = muscle()

cell3 = interneuron()
cell4 = interneuron()

# Настройка стимуляторов
stim1 = h.NetStim()
stim1.number = 20
stim1.start = 0
stim1.interval = 5

stim2 = h.NetStim()
stim2.number = 20
stim2.start = 80
stim2.interval = 5

# # Используем встроенные синапсы из muscle.synlistex
# syn1 = cell1.synlistex[0]
# nc1 = h.NetCon(stim1, syn1)
# nc1.weight[0] = 50  # Подбери значение по силе
#
# syn2 = cell2.synlistex[0]
# nc2 = h.NetCon(stim2, syn2)
# nc2.weight[0] = 50  # Подбери значение по силе

# Используем встроенные синапсы из muscle.synlistex
syn3 = cell3.synlistex[0]
nc3 = h.NetCon(stim1, syn3)
nc3.weight[0] = 25  # Подбери значение по силе

syn4 = cell4.synlistex[0]
nc4 = h.NetCon(stim2, syn4)
nc4.weight[0] = 25  # Подбери значение по силе

syn_to_muscle1 = cell1.synlistex[0]
nc5 = cell3.connect2target(syn_to_muscle1)
nc5.weight[0] = 25

syn_to_muscle2 = cell2.synlistex[0]
nc6 = cell4.connect2target(syn_to_muscle2)
nc6.weight[0] = 25


# # Тормозящая связь: cell2 подавляет cell1
# inh_syn1 = h.ExpSyn(cell1.soma(0.5))
# inh_syn1.e = -80  # Обратный потенциал для торможения
# inh_nc1 = h.NetCon(cell2.soma(0.5)._ref_v, inh_syn1, sec=cell2.soma)
# inh_nc1.threshold = -20
# inh_nc1.delay = 1
# inh_nc1.weight[0] = 1.0

# Запись переменных
t = h.Vector().record(h._ref_t)

v1_soma = h.Vector().record(cell1.soma(0.5)._ref_v)
v1_mu   = h.Vector().record(cell1.muscle_unit(0.5)._ref_v)
f1      = h.Vector().record(cell1.muscle_unit(0.5)._ref_F_fHill)

v2_soma = h.Vector().record(cell2.soma(0.5)._ref_v)
v2_mu   = h.Vector().record(cell2.muscle_unit(0.5)._ref_v)
f2      = h.Vector().record(cell2.muscle_unit(0.5)._ref_F_fHill)

# Моделирование
h.tstop = 110
h.run()
print("max F_fHill cell1:", max(f1))
print("max Vm soma1:", max(v1_soma))
# Преобразуем h.Vector() в списки
t_data = list(t)
v1_soma_data = list(v1_soma)
v2_soma_data = list(v2_soma)
v1_mu_data = list(v1_mu)
v2_mu_data = list(v2_mu)
f1_data = list(f1)
f2_data = list(f2)

# Теперь передаём списки в Bokeh

# Указать HTML-выходной файл
output_file("muscle_plot.html")



# Отрисовка в Bokeh
p1 = figure(title="Soma Vm", width=800, height=250, x_axis_label="Time (ms)", y_axis_label="Vm (mV)")
p1.line(t_data, v1_soma_data, color="blue", legend_label="cell1 soma")
p1.line(t_data, v2_soma_data, color="green", legend_label="cell2 soma")

p2 = figure(title="Muscle Unit Vm", width=800, height=250, x_axis_label="Time (ms)", y_axis_label="Vm (mV)")
p2.line(t_data, v1_mu_data, color="blue", legend_label="cell1 muscle_unit")
p2.line(t_data, v2_mu_data, color="green", legend_label="cell2 muscle_unit")

p3 = figure(title="Muscle Force (F_fHill)", width=800, height=250, x_axis_label="Time (ms)", y_axis_label="Force")
p3.line(t_data, f1_data, color="blue", legend_label="cell1 fHill")
p3.line(t_data, f2_data, color="green", legend_label="cell2 fHill")

# Показ графиков
show(column(p1, p2, p3))
