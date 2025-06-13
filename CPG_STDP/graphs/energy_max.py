from collections import defaultdict
from bokeh.plotting import figure, output_file, show
from bokeh.models import ColumnDataSource, LabelSet

# Исходные данные
data = []

# Значения
new_values = [
    (10264230.418 * 10 ** (-15), "GPU_A100", "LSTM_IMDB"),
    (2153699.856 * 10 ** (-15), "GPU_RTX_3050", "LSTM_IMDB"),
    (16286613.872 * 10 ** (-15), "GPU_RTX_3050", "RESNET_18_MNIST"),
    (1891932.713 * 10 ** (-15), "NPU_910A", "RESNET_18_MNIST"),
    (756070.149 * 10 ** (-15), "GPU_A100", "TRANSFORMER_IMDB"),
    (7713273.120 * 10 ** (-15), "GPU_RTX_3050", "TRANSFORMER_IMDB"),
    (17140769.132 * 10 ** (-15), "NPU_910A", "TRANSFORMER_IMDB")
]

# new_values = [
#     (10264230.418 * 10 ** (-15), "LSTM_IMDB", "GPU_A100"),
#     (2153699.856 * 10 ** (-15), "LSTM_IMDB", "GPU_RTX_3050"),
#     (16286613.872 * 10 ** (-15), "RESNET_18_MNIST", "GPU_RTX_3050"),
#     (1891932.713 * 10 ** (-15), "RESNET_18_MNIST", "NPU_910A"),
#     (756070.149 * 10 ** (-15), "TRANSFORMER_IMDB", "GPU_A100"),
#     (7713273.120 * 10 ** (-15), "TRANSFORMER_IMDB", "GPU_RTX_3050"),
#     (17140769.132 * 10 ** (-15), "TRANSFORMER_IMDB", "NPU_910A")
# ]

# new_known_values = [
#     (680000 * 10 ** (-15), "KNOWM", "KNOWM")
# ]

# Объединяем данные
for value, label, text_label in new_values:
    data.append([value, label, text_label])

# Сортировка категорий
categories = defaultdict(list)
labels_dict = defaultdict(list)
for value, category, text_label in data:
    categories[category].append(value)
    labels_dict[category].append(text_label)

sorted_categories = sorted(categories.keys(), key=lambda cat: max(categories[cat]), reverse=True)

# Яркая палитра
orange_gradient = [
    "#ffc04c", "#ffa726", "#ff8f00", "#ff6f00",
    "#fb580d", "#e65100", "#c44200", "#a93200"
]

# Назначаем цвета
sorted_data = sorted(data, key=lambda x: x[0], reverse=False)
value_to_color = {}
for i, (value, label, text_label) in enumerate(sorted_data):
    value_to_color[(label, text_label)] = orange_gradient[i % len(orange_gradient)]

# Подготовка данных
x_list, top_list, bottom_list, color_list, label_list = [], [], [], [], []
for value, label, text_label in sorted_data:
    x_list.append(label)
    top_list.append(value)
    bottom_list.append(value * 0.9)  # тонкий прямоугольник по высоте
    color_list.append(value_to_color[(label, text_label)])
    label_list.append(text_label)

source = ColumnDataSource(data=dict(
    x=x_list,
    top=top_list,
    bottom=bottom_list,
    color=color_list,
    label=label_list,
    y_label=[t * 1.05 for t in top_list]  # над прямоугольником
))

# Фигура
fig = figure(width=900, height=500,
             y_axis_type="log", y_axis_label='Energy [J]', x_axis_label='NPU, GPU',
             x_range=sorted_categories)

# Прямоугольники без обводки
fig.vbar(x='x', top='top', bottom='bottom', width=0.5,
         color='color', line_color=None, alpha=0.9, source=source)

# Подписи над прямоугольниками
labels = LabelSet(x='x', y='y_label', text='label', level='glyph',
                  x_offset=0, y_offset=0, text_align='center',
                  text_font_size="11pt", source=source)
fig.add_layout(labels)

# Стили
fig.xaxis.axis_label_text_font_style = "bold"
fig.yaxis.axis_label_text_font_style = "bold"
fig.xaxis.major_label_text_font_style = "bold"
fig.yaxis.major_label_text_font_style = "bold"
fig.legend.visible = False

# Вывод
output_file('NPU_Final.html')
show(fig)
