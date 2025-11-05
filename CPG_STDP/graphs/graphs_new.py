import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
from matplotlib import patheffects
from matplotlib.ticker import LogLocator, FuncFormatter, ScalarFormatter


def plot_graph():
    # --- 1. Загрузка и подготовка данных ---
    df = pd.read_excel("energy.xlsx")
    df.columns = df.columns.str.strip().str.lower()

    df['fj'] = (
        df['fj'].astype(str)
        .str.replace(' ', '')
        .str.replace(',', '.')
        .astype(float)
    )
    df['type'] = df['type'].astype(str).str.strip().str.lower()
    df['results'] = df['results'].astype(str).str.strip().str.lower()

    # --- 1.1. Заменяем "lit" → "literature" ---
    df['results'] = df['results'].replace({'lit': 'literature'})

    # --- 2. Сортировка по убыванию максимального значения ---
    max_by_type = df.groupby('type')['fj'].max().sort_values(ascending=False)
    types_order = max_by_type.index.tolist()

    # --- 2.1. Фиксируем GPU, NPU, FPGA в начале ---
    priority = ['gpu', 'npu', 'fpga', 'digital snn']
    custom_order = [t for t in priority if t in types_order]

    # Добавляем остальные типы (кроме уже указанных)
    for t in types_order:
        if t not in priority:
            custom_order.append(t)

    # --- 3. Построение Swarmplot ---
    plt.figure(figsize=(12, 7))

    ax = sns.swarmplot(
        data=df,
        x='type', y='fj', hue='results',
        order=custom_order,
        dodge=False,
        size=8,
        alpha=0.9,
        edgecolor='black',
        linewidth=0.7,
        palette={'experimental': '#4A90E2', 'literature': '#F64278'}
    )

    # 🔵 Синий диапазон: от 10^3 до 10^6
    ax.axhspan(
        1e3, 1e6,
        color="#ADFA71",
        alpha=0.45,
        zorder=0  # чтобы было под точками
    )

    # 💗 Розовый диапазон: от 10 до 100
    ax.axhspan(
        1e1, 1e2,
        color="#5C5470",
        alpha=0.2,
        zorder=0
    )
    # --- 4. Оформление ---
    plt.yscale('log')
    plt.xlabel("TECHNOLOGY", fontweight='bold', fontsize=12)
    plt.ylabel(r'$\mathbf{Energy\ [fJ,\ lg\ scale]}$', fontweight='bold', fontsize=12)

    # --- Горизонтальные и крупные подписи типов ---
    plt.xticks(
        ticks=range(len(custom_order)),
        labels=[t.upper() for t in custom_order],
        rotation=0,
        ha='center',
        fontsize=11,
        fontweight='bold'
    )
    plt.yticks(fontweight='bold')
    plt.grid(alpha=0.3, which='both')

    # --- Легенда ---
    handles, labels = plt.gca().get_legend_handles_labels()
    by_label = dict(zip(labels, handles))
    legend = plt.legend(by_label.values(), by_label.keys(), title="Results", loc='upper right')
    plt.setp(legend.get_texts(), fontweight='bold')
    plt.setp(legend.get_title(), fontweight='bold')

    plt.tight_layout()
    plt.savefig("landscape.png", dpi=300)
    plt.show()

    print("✅ Сохранено: energy_swarmplot.png")

def plot_bokeh_from_excel(filename="energy_arch.xlsx", change=False):# 🔹 если change True → ось X = architecture, легенда = type+subtype
    """
    Создаёт интерактивный Bokeh-график только для GPU и NPU.
    Ось X: Architecture
    Ось Y: fJ (логарифмическая шкала)
    Цвет: по величине энергии (от жёлтого к оранжевому)
    Категория: Type + Subtype
    """
    # --- 1. Загрузка данных ---
    df = pd.read_excel(filename)

    # --- 2. Предобработка ---
    df.columns = df.columns.str.strip().str.lower()
    df['fj'] = (
        df['fj'].astype(str)
        .str.replace(' ', '')
        .str.replace(',', '.')
        .astype(float)
    )
    df = df[df['type'].isin(['GPU', 'NPU'])]

    # создаём поле device = type+subtype
    df['device'] = df['type'].astype(str) + '_' + df['subtype'].astype(str)

    # --- 3. Перестановка данных в зависимости от флага ---
    if change:
        x_col = 'architecture'
        hue_col = 'device'
    else:
        x_col = 'device'
        hue_col = 'architecture'

    # --- 4. Построение ---
    plt.figure(figsize=(11, 7))
    sns.set(style="whitegrid")

    ax = sns.swarmplot(
        data=df,
        x=x_col,
        y='fj',
        hue=hue_col,
        palette='Blues_r',
        size=10,
        edgecolor='black',
        linewidth=0.8,
        alpha=0.9,
        dodge=True
    )

    # --- 5. Логарифмическая шкала ---
    ax.set_yscale('log')
    ax.yaxis.set_major_locator(LogLocator(base=10.0, numticks=15))
    ax.yaxis.set_minor_locator(LogLocator(base=10.0, subs=np.arange(2, 10) * 0.1, numticks=100))
    ax.yaxis.set_major_formatter(ScalarFormatter())
    ax.yaxis.set_minor_formatter(ScalarFormatter())

    # --- 6. Подписи ---
    ax.set_xlabel(
        'ARCHITECTURE' if change else 'TECHNOLOGY',
        fontsize=16, fontweight='bold', labelpad=12
    )
    ax.set_ylabel(r'$\mathbf{Energy\ [fJ,\ lg\ scale]}$', fontsize=16, labelpad=15)

    plt.xticks(rotation=0, fontsize=13, fontweight='bold')
    plt.yticks(fontsize=13, fontweight='bold')

    # --- 7. Разделительные линии ---
    for i in range(len(df[x_col].unique()) - 1):
        plt.axvline(i + 0.5, color='gray', linestyle='--', linewidth=0.8, alpha=0.5)

    # --- 8. Легенда ---
    if change:
        # 👉 Легенда справа снизу
        legend = plt.legend(
            title='TECHNOLOGY',
            title_fontsize=14,
            fontsize=13,
            loc='lower right',
            bbox_to_anchor=(1.0, 0.02),
            frameon=True,
            fancybox=True,
            framealpha=0.9
        )
    else:
        # 👉 Легенда сверху слева
        legend = plt.legend(
            title='ARCHITECTURE',
            title_fontsize=14,
            fontsize=13,
            loc='upper left',
            bbox_to_anchor=(0.01, 0.99),
            frameon=True,
            fancybox=True,
            framealpha=0.9
        )
    plt.setp(legend.get_texts(), fontweight='bold')
    plt.setp(legend.get_title(), fontweight='bold')

    # --- 9. Сетка и вывод ---
    plt.grid(which='major', linestyle='-', linewidth=0.4, alpha=0.4)
    plt.grid(which='minor', linestyle=':', linewidth=0.3, alpha=0.3)

    plt.tight_layout()
    name = "energy_swarm.png"
    if change:
        name = "energy_swarm_change.png"
    plt.savefig(name, dpi=400, bbox_inches='tight')
    plt.show()


def plot_filtered_swarm(filename="energy_arch.xlsx", change=False):
    """
    Отрисовывает swarmplot только для архитектур RESNET18 и Network.
    Масштаб подбирается автоматически, чтобы точки не были сильно разбросаны.
    Цветовая схема — тёплая (Purples+Oranges).
    """
    # --- 1. Загрузка данных ---
    df = pd.read_excel(filename)
    df.columns = df.columns.str.strip().str.lower()

    # --- 2. Подготовка ---
    df['fj'] = (
        df['fj'].astype(str)
        .str.replace(' ', '')
        .str.replace(',', '.')
        .astype(float)
    )

    # Берём только нужные архитектуры
    df = df[df['architecture'].isin(['RESNET18', 'Network'])]
    df['device'] = df['type'].astype(str) + '_' + df['subtype'].astype(str)

    # --- 3. Выбор осей ---
    if change:
        x_col = 'architecture'
        hue_col = 'device'
    else:
        x_col = 'device'
        hue_col = 'architecture'

    # --- 4. Построение ---
    plt.figure(figsize=(10, 7))
    sns.set(style="whitegrid")

    # Тёплая палитра
    palette = sns.color_palette("rocket_r", n_colors=len(df[hue_col].unique()))

    ax = sns.swarmplot(
        data=df,
        x=x_col,
        y='fj',
        hue=hue_col,
        palette=palette,
        size=9,
        edgecolor='black',
        linewidth=0.9,
        alpha=0.9,
        dodge=True
    )

    # --- 5. Логарифмическая шкала ---
    ax.set_yscale('log')
    ymin, ymax = df['fj'].min(), df['fj'].max()
    ax.set_ylim(ymin * 0.8, ymax * 1.2)  # небольшой отступ для аккуратности

    ax.yaxis.set_major_locator(LogLocator(base=10.0, numticks=10))
    ax.yaxis.set_minor_locator(LogLocator(base=10.0, subs=np.arange(2, 10)*0.1, numticks=100))
    ax.yaxis.set_major_formatter(ScalarFormatter())

    # --- 6. Подписи ---
    ax.set_xlabel(
        'ARCHITECTURE' if change else 'TECHNOLOGY',
        fontsize=16, fontweight='bold', labelpad=12
    )
    ax.set_ylabel(r'$\mathbf{Energy\ [fJ,\ lg\ scale]}$', fontsize=16, labelpad=15)

    plt.xticks(rotation=0, fontsize=13, fontweight='bold')
    plt.yticks(fontsize=13, fontweight='bold')

    # --- 7. Разделительные линии ---
    for i in range(len(df[x_col].unique()) - 1):
        plt.axvline(i + 0.5, color='gray', linestyle='--', linewidth=0.7, alpha=0.5)

    # --- 8. Легенда ---
    if change:
        legend = plt.legend(
            title='TECHNOLOGY',
            title_fontsize=14,
            fontsize=13,
            loc='lower right',
            bbox_to_anchor=(1.0, 0.02),
            frameon=True,
            fancybox=True,
            framealpha=0.9
        )
    else:
        legend = plt.legend(
            title='ARCHITECTURE',
            title_fontsize=14,
            fontsize=13,
            loc='upper left',
            bbox_to_anchor=(0.01, 0.99),
            frameon=True,
            fancybox=True,
            framealpha=0.9
        )
    plt.setp(legend.get_texts(), fontweight='bold')
    plt.setp(legend.get_title(), fontweight='bold')

    # --- 9. Сетка и вывод ---
    plt.grid(which='major', linestyle='-', linewidth=0.4, alpha=0.4)
    plt.grid(which='minor', linestyle=':', linewidth=0.3, alpha=0.3)

    plt.tight_layout()
    name = "energy_filtered.png" if not change else "energy_filtered_change.png"
    plt.savefig(name, dpi=400, bbox_inches='tight')
    plt.show()


def plot_type_graph_with_labels_centered(filename="energy.xlsx"):
    import pandas as pd
    import matplotlib.pyplot as plt
    import seaborn as sns
    import numpy as np
    from matplotlib.ticker import LogLocator, ScalarFormatter
    import re

    df = pd.read_excel(filename)
    df.columns = df.columns.str.strip().str.lower()

    # --- Подготовка данных ---
    df['fj'] = (
        df['fj'].astype(str)
        .str.replace(' ', '')
        .str.replace(',', '.')
        .astype(float)
    )

    df['type_graph'] = df['type_graph'].astype(str).str.strip()
    df['results'] = (
        df['results'].astype(str)
        .str.strip()
        .str.lower()
        .replace({'lit': 'literature'})
    )

    df = df[df['type_graph'].notna() & (df['type_graph'] != 'nan')]
    if df.empty:
        print("⚠️ Нет данных с полем type_graph.")
        return

    # --- Вспомогательная функция: извлекаем базовое имя без oxide / no oxide ---
    def base_name(name):
        n = name.lower().strip()
        n = re.sub(r'\s*no oxide$', '', n)
        n = re.sub(r'\s*oxide$', '', n)
        return n.strip()

    df['base'] = df['type_graph'].apply(base_name)

    # --- 1️⃣ Вычисляем максимум fj по каждой категории ---
    max_fj = df.groupby('type_graph')['fj'].max().reset_index()

    # --- 2️⃣ Добавляем базовое имя ---
    max_fj['base'] = max_fj['type_graph'].apply(base_name)

    # --- 3️⃣ Разделяем на oxide/no oxide и прочие ---
    ox_related = max_fj[max_fj['type_graph'].str.lower().str.contains('oxide')]
    others = max_fj[~max_fj['type_graph'].str.lower().str.contains('oxide')]

    # --- 4️⃣ Группируем oxide/no oxide по base и сортируем: no oxide → oxide ---
    ox_ordered = []
    for base, group in ox_related.groupby('base', sort=False):
        def oxide_sort_key(x):
            xl = x.lower().strip()
            if 'no oxide' in xl:
                return 0
            elif 'oxide' in xl:
                return 1
            return 2

        group_sorted = sorted(group['type_graph'], key=oxide_sort_key)
        ox_ordered.extend(group_sorted)

    # --- 5️⃣ Остальные сортируем по убыванию максимального значения fj ---
    others_sorted = others.sort_values('fj', ascending=False)['type_graph'].tolist()

    # --- 6️⃣ Итоговый порядок ---
    order = ox_ordered + others_sorted

    # --- Приведение категорий ---
    df['type_graph'] = pd.Categorical(df['type_graph'], categories=order, ordered=True)

    # --- Построение ---
    palette = {'literature': '#F64278', 'experimental': '#4A90E2'}

    plt.figure(figsize=(11, 7))
    sns.set(style="whitegrid")

    ax = sns.swarmplot(
        data=df,
        x='type_graph',
        y='fj',
        hue='results',
        palette=palette,
        size=16,
        edgecolor='black',
        linewidth=0.9,
        alpha=0.95,
        dodge=False,
        order=order
    )

    # --- Масштаб ---
    ax.set_yscale('log')
    ymin, ymax = df['fj'].min(), df['fj'].max()
    ax.set_ylim(ymin * 0.3, ymax * 4)
    # 🔵 Синий диапазон: от 10^3 до 10^6
    ax.axhspan(
        1e3, 1e6,
        color="#ADFA71",
        alpha=0.45,
        zorder=0  # чтобы было под точками
    )

    # 💗 Розовый диапазон: от 10 до 100
    ax.axhspan(
        1e1, 1e2,
        color="#5C5470",
        alpha=0.2,
        zorder=0
    )

    # --- Подписи ---
    ax.set_xlabel('TECHNOLOGY', fontsize=16, fontweight='bold', labelpad=12)
    ax.set_ylabel(r'$\mathbf{Energy\ [fJ,\ lg\ scale]}$', fontsize=16, labelpad=15)

    labels = [tg.upper() for tg in order]
    plt.xticks(ticks=range(len(order)), labels=labels, rotation=0, fontsize=13, fontweight='bold')
    ax.set_xticklabels(labels, ha='center')
    plt.yticks(fontsize=13, fontweight='bold')

    # --- Разделительные линии ---
    for i in range(len(order) - 1):
        plt.axvline(i + 0.5, color='gray', linestyle='--', linewidth=0.6, alpha=0.4)

    # --- Легенда ---
    legend = plt.legend(
        title='Results',
        title_fontsize=14,
        fontsize=13,
        loc='upper right',
        frameon=True,
        fancybox=True,
        framealpha=0.9
    )
    plt.setp(legend.get_texts(), fontweight='bold')
    plt.setp(legend.get_title(), fontweight='bold')

    plt.grid(which='major', linestyle='-', linewidth=0.4, alpha=0.4)
    plt.grid(which='minor', linestyle=':', linewidth=0.3, alpha=0.3)

    plt.tight_layout()
    plt.savefig("min_value_memristors.png", dpi=400, bbox_inches='tight')
    plt.show()
# --- 5. Пример вызова ---
if __name__ == "__main__":
    # при необходимости просто вызови:
    plot_graph()
    #plot_bokeh_from_excel("energy_1.xlsx", True)
    # plot_filtered_swarm("energy_1.xlsx")
    # plot_type_graph_with_labels_centered("energy_1.xlsx")
    pass
