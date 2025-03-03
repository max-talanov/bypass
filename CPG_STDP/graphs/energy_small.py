from collections import defaultdict
import numpy as np
from bokeh.plotting import figure, output_file, show
from bokeh.models import ColumnDataSource, HoverTool

# Исходные данные
data = [
    (0.36 * 10 ** (-15), "ST"),
    (2.08 * 10 ** (-15), "ST"),
    (0.29 * 10 ** (-15), "ST"),
    (1.28 * 10 ** (-15), "ST"),
    (98.71 * 10 ** (-15), "ST"),
    (9 * 10 ** (-15), "FET"),
    (93.1 * 10 ** (-18), "FET"),
    (48 * 10 ** (-18), "FET"),
    (230 * 10 ** (-15), "FET"),
    (0.99 * 10 ** (-15), "FET"),
    (15 * 10 ** (-15), "FET"),
    (1 * 10 ** (-15), "ST"),
    (0.0675 * 10 ** (-18), "ST"),
    (39.56 * 10 ** (-15), 'ORGANIC'),
    (10.48 * 10 ** (-18), 'NO_OXID'),
    (25 * 10 ** (-15), 'ORGANIC'),
    (0.7 * 10 ** (-15), 'ORGANIC'),
    (6 * 10 ** (-15), 'ORGANIC'),
    (4.05 * 10 ** (-12), 'ORGANIC'),
    (0.35 * 10 ** (-15), 'ORGANIC'),
    (170 * 10 ** (-15), 'NO_OXID'),
    (3.076 * 10 ** (-12), 'OXID'),
    (4.1 * 10 ** (-12), 'OXID'),
    (8.5 * 10 ** (-15), 'NO_OXID'),
    (198 * 10 ** (-15), 'NO_OXID'),
    (1.8 * 10 ** (-12), 'NO_OXID'),
    (1.15 * 10 ** (-12), 'NO_OXID'),
    (0.1 * 10 ** (-12), 'OXID'),
    (1 * 10 ** (-15), 'OXID'),
    (1.9 * 10 ** (-15), 'OXID'),
    (32.65 * 10 ** (-15), 'OXID'),
    (5 * 10 ** (-15), "ORGANIC") #POLY
]

# Группируем значения по категориям
categories = defaultdict(list)
for value, category in data:
    categories[category].append(value)

# Сортируем категории по убыванию максимального значения в группе
priority_categories = ["OXID", "NO_OXID"]
sorted_categories = (priority_categories +
                     sorted([cat for cat in categories.keys() if cat not in priority_categories],
                            key=lambda cat: max(categories[cat]), reverse=True))

# Определяем числовые координаты для категорий
category_mapping = {category: i + 1 for i, category in enumerate(sorted_categories)}

# Цвета для каждой категории
category_colors = {
    "OXID": "#264301",
    "NO_OXID": "#5c8a03",
    "ORGANIC": "#82b21e",
    "FET": "#d6f58e",
    "ST": "#d3e3b6",
}

# Оптимизированная шкала
padding_factor = 2.0  # Увеличиваем пространство сверху и снизу
y_min, y_max = min(min(values) for values in categories.values()) / padding_factor, max(
    max(values) for values in categories.values()) * padding_factor

# Создаем фигуру для всех категорий
fig = figure(width=900, height=500,
             y_axis_type="log", y_axis_label='Energy [J]', x_axis_label='Technology',
             x_range=[0, len(sorted_categories) + 1], y_range=(y_min, y_max))

# Добавляем точки для каждой категории с обводкой
for category in sorted_categories:
    values = categories[category]
    x_positions = [category_mapping[category]] * len(values)
    source = ColumnDataSource(data={"x": x_positions, "y": values})

    fig.scatter(x="x", y="y", size=25, color=category_colors.get(category, "gray"),
                line_color="black", line_width=1.5, alpha=0.8, source=source)

fig.hspan(
    y=[10 ** (-12), 10 ** (-15)],
    line_width=[3, 3], line_color="green", alpha=0.5
)
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
output_file('Sorted_Clustered_Energy_1.html')
show(fig)