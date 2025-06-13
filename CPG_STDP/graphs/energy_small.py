from collections import defaultdict
import numpy as np
from bokeh.plotting import figure, output_file, show
from bokeh.models import ColumnDataSource, LabelSet
from matplotlib import cm
from matplotlib.colors import to_hex

# Исходные данные
data = [
    (0.36e-15, "ST"), (2.08e-15, "ST"), (0.29e-15, "ST"), (1.28e-15, "ST"), (98.71e-15, "ST"),
    (9e-15, "FET"), (93.1e-18, "FET"), (48e-18, "FET"), (230e-15, "FET"), (0.99e-15, "FET"), (15e-15, "FET"),
    (1e-15, "ST"), (0.0675e-18, "ST"),
    (39.56e-15, 'ORGANIC'), (10.48e-18, 'NO_OXID'), (25e-15, 'ORGANIC'), (0.7e-15, 'ORGANIC'),
    (6e-15, 'ORGANIC'), (4.05e-12, 'ORGANIC'), (0.35e-15, 'ORGANIC'), (5e-15, "ORGANIC"),
    (170e-15, 'NO_OXID'), (3.076e-12, 'OXID'), (4.1e-12, 'OXID'), (8.5e-15, 'NO_OXID'),
    (198e-15, 'NO_OXID'), (1.8e-12, 'NO_OXID'), (1.15e-12, 'NO_OXID'), (0.1e-12, 'OXID'),
    (1e-15, 'OXID'), (1.9e-15, 'OXID'), (32.65e-15, 'OXID')
]

# Группировка
categories = defaultdict(list)
for value, category in data:
    categories[category].append(value)

priority_categories = ["OXID", "NO_OXID"]
sorted_categories = (
    priority_categories +
    sorted([cat for cat in categories if cat not in priority_categories],
           key=lambda cat: max(categories[cat]), reverse=True)
)
category_mapping = {category: i + 1 for i, category in enumerate(sorted_categories)}

# Градиент зелёных цветов: тёмно-зелёный = max значение
all_values = sorted(data, key=lambda x: x[0], reverse=False)
cmap = cm.get_cmap("Greens")
hex_colors = [to_hex(cmap(i)) for i in np.linspace(0.4, 1.0, len(all_values))]

value_to_color = {entry: hex_colors[i] for i, entry in enumerate(all_values)}

# Подготовка данных для отрисовки квадратов
x_list, y_list, color_list = [], [], []
for val, cat in all_values:
    x_list.append(category_mapping[cat])
    y_list.append(val)
    color_list.append(value_to_color[(val, cat)])

source = ColumnDataSource(data=dict(
    x=x_list,
    y=y_list,
    color=color_list
))

# Фигура
fig = figure(width=900, height=500,
             y_axis_type="log", y_axis_label='Energy [J]', x_axis_label='Technology',
             x_range=[0, len(sorted_categories) + 1],
             y_range=(min(y_list) / 2, max(y_list) * 2))

# Фоновые зоны
fig.quad(left=-0.5, right=len(sorted_categories) + 1,
         top=10 ** (-12), bottom=10 ** (-15), color="blue", alpha=0.15)
fig.quad(left=-0.5, right=len(sorted_categories) + 1,
         top=10 ** (-13), bottom=10 ** (-14), color="red", alpha=0.1)

# Квадраты
fig.square(x='x', y='y', size=20, color='color', alpha=1.0, line_color=None, source=source)

# Подписи в каждой колонке сверху вниз: 1, 2, 3...
label_texts = []
label_x = []
label_y = []
x_offset = []
aligns = []

for cat in sorted_categories:
    values = sorted(categories[cat], reverse=True)
    x = category_mapping[cat]
    for i, val in enumerate(values):
        label_texts.append(str(i + 1))
        label_x.append(x)
        label_y.append(val)
        if i % 2 == 0:
            x_offset.append(13)
            aligns.append("left")
        else:
            x_offset.append(-13)
            aligns.append("right")

label_source = ColumnDataSource(data=dict(
    x=label_x,
    y=label_y,
    text=label_texts,
    x_offset=x_offset,
    align=aligns
))

labels = LabelSet(
    x='x', y='y', text='text',
    x_offset='x_offset', y_offset=-5,
    text_align='align',
    text_font_size="10pt",
    source=label_source
)
fig.add_layout(labels)

# Оси
fig.xaxis.ticker = list(category_mapping.values())
fig.xaxis.major_label_overrides = {v: k for k, v in category_mapping.items()}
fig.xaxis.axis_label_text_font_style = "bold"
fig.yaxis.axis_label_text_font_style = "bold"
fig.xaxis.major_label_text_font_style = "bold"
fig.yaxis.major_label_text_font_style = "bold"
fig.legend.visible = False

# Вывод
output_file('GreenSquares_Gradient_Numbered.html')
show(fig)
