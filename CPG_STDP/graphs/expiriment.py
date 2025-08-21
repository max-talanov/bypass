import os
import sys

from bokeh.models import FactorRange
from bokeh.plotting import figure, output_file, show

sys.path.append('res_weight/')
my_path = os.path.abspath('res_weight/')

themes = 'light_minimal'

# Данные
x = [1, 2, 3, 4, 5]  # Числовые значения для оси X
y = ['А', 'Б', 'В', 'Г', 'Д']  # Названия для оси Y

# Создание объекта графика
p = figure(y_range=list(range(len(y))), title="График с числовыми и текстовыми осями",
           x_axis_label='Числовая ось', y_axis_label='Текстовая ось',
           tools="pan,wheel_zoom,box_zoom,reset", toolbar_location=None)

# Добавление кружков
p.circle(x, y, color="navy", alpha=0.5)

# Отображение графика
output_file('expiriment.html')
show(p)
