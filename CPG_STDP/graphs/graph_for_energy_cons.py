from collections import defaultdict

import numpy as np
from bokeh.plotting import figure, output_file, show
from bokeh.models import ColumnDataSource, HoverTool

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
    [5 * 10 ** (-15), 'ORGANIC'], #POLY
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
    [32.65 * 10 ** (-15), 'VOLATILE'],
    [0.13 * 10 ** (-3), 'FPGA']
]

# Новые значения
new_values = [
    10264230.418 * 10 ** (-15),
    2153699.856 * 10 ** (-15),
    16286613.872 * 10 ** (-15),
    1891932.713 * 10 ** (-15),
    756070.149 * 10 ** (-15),
    7713273.120 * 10 ** (-15),
    17140769.132  * 10 ** (-15)
]

new_knowm_values = [
    680000 * 10 ** (-15)
]


# Добавляем новые значения в data с метками
for value in new_values:
    data.append([value, "ANN"])
for value in new_knowm_values:
    data.append([value, "KNOWM"])

# Цвета для каждой категории
category_colors = {
    "ANN": "#fb580d",
    "FPGA": "#fb580d",
    "KNOWM": "#fb580d",
    "VOLATILE": "#76ae0a",
    "ORGANIC": "#76ae0a",
    "FET": "#76ae0a",
    "ST": "#76ae0a"
}
# Группируем значения по категориям
categories = defaultdict(list)
for value, category in data:
    categories[category].append({"value":value, "color":category_colors[category]})

# Сортируем категории: KNOWM и NN идут первыми, остальные по убыванию максимального значения
sorted_categories = sorted(
    categories.keys(),
    key=lambda cat: float('-inf') if cat in ['FPGA', 'KNOWM', 'ANN'] else -max(v["value"] for v in categories[cat])
)

# Создаем фигуру
fig = figure(width=900, x_range=sorted_categories, height=400,
             y_axis_type="log", y_axis_label='Energy [J]', x_axis_label='Technology')
fig.quad(
    left=-0.5,  # По x-оси прямоугольник будет занимать всё пространство
    right=len(sorted_categories),
    top=10**(-12),
    bottom=10**(-15),
    color="blue",
    alpha=0.15
)

fig.quad(
    left=-0.5,  # По x-оси прямоугольник будет занимать всё пространство
    right=len(sorted_categories),
    top=10**(-13),
    bottom=10**(-14),
    color="red",
    alpha=0.1
)

# Добавляем столбцы
for category in sorted_categories:
    values = [v["value"] for v in categories[category]]
    colors = [v["color"] for v in categories[category]]

    fig.vbar(
        x=[category] * len(values),
        top=values,
        width=0.5,
        bottom=[v / 2 for v in values],
        alpha=0.8,
        color=colors
    )
# # Добавляем горизонтальные линии
# fig.hspan(
#     y=[10 ** (-12), 10 ** (-15)],
#     line_width=[3, 3], line_color="blue", alpha=0.6
# )

# Настройка шрифтов
fig.xaxis.axis_label_text_font_style = "bold"
fig.yaxis.axis_label_text_font_style = "bold"
fig.xaxis.major_label_text_font_style = "bold"
fig.yaxis.major_label_text_font_style = "bold"

# Сохраняем и показываем график
output_file('Sorted_Clustered_Energy_1.html')
show(fig)
