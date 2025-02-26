from collections import defaultdict

import numpy as np
from bokeh.plotting import figure, output_file, show
from bokeh.models import ColumnDataSource, Rect, Range1d, Label, HoverTool

# Исходные данные
data = [
    [0.36 * 10 ** (-15), "ST"],
    [2.08 * 10 ** (-15), "ST"],
    [0.29 * 10 ** (-15), "ST"],
    [1.28 * 10 ** (-15), "ST"],
    [98.71 * 10 ** (-15), "ST"],
    [9 * 10 ** (-15), "FET"],
    [93.1 * 10 ** (-18), "FET"],
    [48 * 10 ** (-18), "FET"],
    [230 * 10 ** (-15), "FET"],
    [0.99 * 10 ** (-15), "FET"],
    [15 * 10 ** (-15), "FET"],
    [1 * 10 ** (-15), "ST"],
    [0.0675 * 10 ** (-18), "ST"],
    [39.56 * 10 ** (-15), 'ORGANIC'],
    [10.48 * 10 ** (-18), 'VOLATILE'],
    [25 * 10 ** (-15), 'ORGANIC'],
    [0.7 * 10 ** (-15), 'ORGANIC'],
    [6 * 10 ** (-15), 'ORGANIC'],
    [4.05 * 10 ** (-12), 'ORGANIC'],
    [0.35 * 10 ** (-15), 'ORGANIC'],
    [170 * 10 ** (-15), 'VOLATILE'],
    [3.76 * 10 ** (-12), 'VOLATILE'],
    [4.1 * 10 ** (-12), 'VOLATILE'],
    [8.5 * 10 ** (-15), 'VOLATILE'],
    [198 * 10 ** (-15), 'VOLATILE'],
    [1.8 * 10 ** (-12), 'VOLATILE'],
    [1.15 * 10 ** (-12), 'VOLATILE'],
    [0.1 * 10 ** (-12), 'VOLATILE'],
    [1 * 10 ** (-15), 'VOLATILE'],
    [1.9 * 10 ** (-15), 'VOLATILE'],
    [32.65 * 10 ** (-15), 'VOLATILE']
]

# Новые значения
new_values = [
    10264230.418 * 10 ** (-15) ,
    2153699.856 * 10 ** (-15),
    16286613.872 * 10 ** (-15),
    1891932.713 * 10 ** (-15),
    756070.149 * 10 ** (-15),
    7713273.120 * 10 ** (-15),
    17140769.132  * 10 ** (-15)
]

new_known_values = [
    680000 * 10 ** (-15),
    780000 * 10 ** (-15)
]

poly_values = [
    5 * 10 ** (-15)
]

# Добавляем новые значения в data с меткой "NN"
for value in new_values:
    data.append([value, "NN"])

# Добавляем новые значения в data с меткой "KNOWN"
for value in new_known_values:
    data.append([value, "KNOWN"])

for value in poly_values:
    data.append([value, "POLY"])

# Разделяем данные на оси X и Y
data_x_log = [d[1] for d in data]
data_y_log = [d[0] for d in data]

# Исходные данные
categories = [d[1] for d in data]
values = np.array([d[0] for d in data])

# Группируем близкие значения
log_values = np.log10(values)  # Используем логарифмическую шкалу для группировки
clusters = defaultdict(list)

group_threshold = 0.5  # Чем больше значение, тем сильнее объединение

for category, log_val in zip(categories, log_values):
    added = False
    for key in clusters:
        if abs(key - log_val) < group_threshold:
            clusters[key].append((category, log_val))
            added = True
            break
    if not added:
        clusters[log_val] = [(category, log_val)]

# Создаем данные для графика
rect_x = []
rect_y = []
rect_height = []

for key, points in clusters.items():
    unique_categories = set(p[0] for p in points)
    for category in unique_categories:
        rect_x.append(category)
        rect_y.append(10 ** key)
        rect_height.append(len(points))  # Высота прямоугольника = количество элементов


# Создаем фигуру
categories_sorted = sorted(set(categories))
fig = figure(width=900, x_range=categories_sorted, height=400,
             y_axis_type="log", y_axis_label='Energy [fJ]', x_axis_label='Technology')

# Добавляем горизонтальные линии
fig.hspan(
    y=[10 ** (-12), 10 ** (-15)],
    line_width=[3, 3], line_color="green", alpha=0.5
)


# Добавляем прямоугольники (фильтрованные данные)
fig.vbar(x=rect_x, top=rect_y, width=0.3, bottom=[y / 2 for y in rect_y],
         color="blue", alpha=0.6)

# Настройка шрифтов
fig.xaxis.axis_label_text_font_style = "bold"
fig.yaxis.axis_label_text_font_style = "bold"
fig.xaxis.major_label_text_font_style = "bold"
fig.yaxis.major_label_text_font_style = "bold"

# Сохраняем и показываем график
output_file('Clustered_Energy.html')
show(fig)
