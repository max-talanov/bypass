from collections import defaultdict
import numpy as np
from bokeh.plotting import figure, output_file, show
from bokeh.models import ColumnDataSource, HoverTool, LabelSet

# Исходные данные
data = []

# Новые значения
new_values = [
    (10264230.418 * 10 ** (-15), "LSTM_IMDB", "GPU_A100"),
    (2153699.856 * 10 ** (-15), "LSTM_IMDB", "GPU_RTX_3050"),
    (16286613.872 * 10 ** (-15), "RESNET_18_MNIST", "GPU_RTX_3050"),
    (1891932.713 * 10 ** (-15), "RESNET_18_MNIST", "NPU_910A"),
    (756070.149 * 10 ** (-15), "TRANSFORMER_IMDB", "GPU_A100"),
    (7713273.120 * 10 ** (-15), "TRANSFORMER_IMDB", "GPU_RTX_3050"),
    (17140769.132 * 10 ** (-15), "TRANSFORMER_IMDB", "NPU_910A")
]

new_known_values = [
    (680000 * 10 ** (-15), "KNOWN", "Siemens")
]

# Добавляем новые значения в data с метками
for value, label, text_label in new_values:
    data.append([value, label, text_label])
for value, label, text_label in new_known_values:
    data.append([value, label, text_label])

# Группируем значения по категориям
categories = defaultdict(list)
labels_dict = defaultdict(list)
for value, category, text_label in data:
    categories[category].append(value)
    labels_dict[category].append(text_label)

# Сортируем категории по убыванию максимального значения в группе
sorted_categories = sorted(categories.keys(), key=lambda cat: max(categories[cat]), reverse=True)

# Определяем числовые координаты для категорий
category_mapping = {category: i + 1 for i, category in enumerate(sorted_categories)}

# Цвета для каждой категории
category_colors = {
    "TRANSFORMER_IMDB": "#c73601",
    "RESNET_18_MNIST": "#fb580d",
    "LSTM_IMDB": "#ffa602",
    "KNOWN": "#f9d692"
}

# Оптимизированная шкала
y_min, y_max = 3.4e-10, 2.5711153698e-08

# Создаем фигуру для всех категорий
fig = figure(width=900, height=500,
             y_axis_type="log", y_axis_label='Energy [J]', x_axis_label='Technology',
             x_range=[0, len(sorted_categories) + 1], y_range=(y_min, y_max))

# Добавляем точки и подписи для каждой категории
for category in sorted_categories:
    values = categories[category]
    x_positions = [category_mapping[category]] * len(values)
    labels = labels_dict[category]
    source = ColumnDataSource(data={"x": x_positions, "y": values, "label": labels})

    fig.scatter(x="x", y="y", size=25, color=category_colors.get(category, "gray"),
                line_color="black", line_width=1.5, alpha=0.8, source=source)

    label_set = LabelSet(x="x", y="y", text="label", level="glyph",
                         x_offset=10, y_offset=10, text_font_size="13pt", source=source)
    fig.add_layout(label_set)

# Настраиваем подписи для категорий
fig.xaxis.ticker = list(category_mapping.values())
fig.xaxis.major_label_overrides = {v: k for k, v in category_mapping.items()}

# Настройка шрифтов
fig.xaxis.axis_label_text_font_style = "bold"
fig.yaxis.axis_label_text_font_style = "bold"
fig.xaxis.major_label_text_font_style = "bold"
fig.yaxis.major_label_text_font_style = "bold"

# Убираем легенду
fig.legend.visible = False

# Сохраняем и показываем график
output_file('NN_KNOWN_Energy.html')
show(fig)
