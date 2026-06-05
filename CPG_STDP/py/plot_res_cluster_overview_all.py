import argparse
import os
import re
from typing import Dict, List, Optional, Tuple

import h5py
import numpy as np


def read_time_file(path: str) -> np.ndarray:
    values: List[float] = []
    with open(path, "r", encoding="utf-8") as f:
        for line in f:
            s = line.strip()
            if s:
                values.append(float(s))
    return np.asarray(values, dtype=np.float32)


def dataset_sort_key(name: str):
    m = re.search(r"step_(\d+)$", name)
    if m:
        return int(m.group(1))
    return name


def read_hdf5_trace(path: str) -> np.ndarray:
    chunks: List[np.ndarray] = []
    with h5py.File(path, "r") as f:
        for key in sorted(f.keys(), key=dataset_sort_key):
            arr = np.asarray(f[key], dtype=np.float32).ravel()
            if arr.size:
                chunks.append(arr)
    if not chunks:
        return np.empty(0, dtype=np.float32)
    return np.concatenate(chunks).astype(np.float32, copy=False)


def parse_group_and_leg(filename: str) -> Optional[Tuple[str, str]]:
    m = re.match(r"(.+)_sp_\d+_CVs_\d+_bs_\d+_(left|right)\.hdf5$", filename)
    if not m:
        return None
    return m.group(1), m.group(2)


def natural_key(text: str):
    parts = re.split(r"(\d+)", text)
    out = []
    for part in parts:
        if part.isdigit():
            out.append(int(part))
        else:
            out.append(part.lower())
    return out


def group_order_key(group_name: str):
    low = group_name.lower()
    priority = 99
    if low.startswith("rg"):
        priority = 0
    elif low.startswith("in"):
        priority = 1
    elif low.startswith("v"):
        priority = 2
    elif low.startswith("ia"):
        priority = 3
    elif low.startswith("cv"):
        priority = 4
    elif low.startswith("r_"):
        priority = 5
    elif low.startswith("mem_"):
        priority = 6
    elif low.startswith("muscle_"):
        priority = 7
    elif low.startswith("force_"):
        priority = 8
    elif low.startswith("units_"):
        priority = 9
    elif low.startswith("am_"):
        priority = 10
    return (priority, natural_key(group_name))


def normalize_for_row(trace: np.ndarray) -> np.ndarray:
    arr = np.asarray(trace, dtype=np.float32)
    span = float(np.max(arr) - np.min(arr))
    if span < 1e-9:
        return np.zeros_like(arr)
    return (arr - np.median(arr)) / span


def draw_overview_plot(
    t_values: np.ndarray,
    labeled_traces: List[Tuple[str, np.ndarray]],
    output_path: str,
    title: str,
    separator_after: int,
) -> None:
    import matplotlib

    if not os.environ.get("DISPLAY", "").strip():
        matplotlib.use("Agg")
    import matplotlib.pyplot as plt

    fig_height = max(8, 0.32 * len(labeled_traces))
    fig, ax = plt.subplots(figsize=(16, fig_height))

    y_positions: List[int] = []
    y_labels: List[str] = []
    color_cycle = plt.rcParams["axes.prop_cycle"].by_key().get("color", ["C0"])

    for idx, (label, trace) in enumerate(labeled_traces):
        arr = np.asarray(trace, dtype=np.float32)
        n = min(arr.size, t_values.size)
        if n == 0:
            continue
        arr = arr[:n]
        t_local = t_values[:n]
        norm = normalize_for_row(arr)

        row = len(labeled_traces) - idx
        y = row + 0.8 * norm
        color = color_cycle[idx % len(color_cycle)]
        ax.plot(t_local, y, lw=0.9, color=color)
        y_positions.append(row)
        y_labels.append(label)

    ax.set_yticks(y_positions)
    ax.set_yticklabels(y_labels, fontsize=8)
    if 0 < separator_after < len(labeled_traces):
        y_sep = len(labeled_traces) - separator_after + 0.5
        ax.axhline(y=y_sep, color="black", lw=1.0, alpha=0.7)
    ax.set_xlabel("t (ms)")
    ax.set_title(title)
    ax.grid(axis="x", alpha=0.3)
    if t_values.size:
        ax.set_xlim(float(t_values[0]), float(t_values[-1]))
    plt.tight_layout()
    plt.savefig(output_path, dpi=140)
    plt.close(fig)


def main() -> None:
    here = os.path.abspath(os.path.dirname(__file__))
    parser = argparse.ArgumentParser(description="Build full overview from all res_cluster hdf5 files")
    parser.add_argument(
        "--input-dir",
        default=os.path.join(here, "res_14_04"),
        help="Directory with *.hdf5 and time.txt",
    )
    parser.add_argument(
        "--time-file",
        default="time.txt",
        help="Time file name inside --input-dir",
    )
    parser.add_argument(
        "--output",
        default=os.path.join(here, "res_14_04", "overview_all_from_hdf5.png"),
        help="Output png path",
    )
    args = parser.parse_args()

    input_dir = os.path.abspath(args.input_dir)
    time_path = os.path.join(input_dir, args.time_file)
    t = read_time_file(time_path)
    if t.size == 0:
        raise ValueError(f"Empty time file: {time_path}")

    left_map: Dict[str, np.ndarray] = {}
    right_map: Dict[str, np.ndarray] = {}

    for name in sorted(os.listdir(input_dir)):
        if not name.endswith(".hdf5"):
            continue
        parsed = parse_group_and_leg(name)
        if parsed is None:
            continue
        group_name, leg = parsed
        trace = read_hdf5_trace(os.path.join(input_dir, name))
        if trace.size == 0:
            continue
        if leg == "left":
            left_map[group_name] = trace
        else:
            right_map[group_name] = trace

    all_groups = sorted(set(left_map.keys()) | set(right_map.keys()), key=group_order_key)
    if not all_groups:
        raise RuntimeError("No valid *.hdf5 files found in input directory.")

    labeled_traces: List[Tuple[str, np.ndarray]] = []
    for group_name in all_groups:
        if group_name in left_map:
            labeled_traces.append((f"{group_name} left", left_map[group_name]))
    left_count = len(labeled_traces)
    for group_name in all_groups:
        if group_name in right_map:
            labeled_traces.append((f"{group_name} right", right_map[group_name]))

    os.makedirs(os.path.dirname(os.path.abspath(args.output)), exist_ok=True)
    draw_overview_plot(
        t_values=t,
        labeled_traces=labeled_traces,
        output_path=os.path.abspath(args.output),
        title=f"Full overview (all groups), left={left_count}, right={len(labeled_traces) - left_count}",
        separator_after=left_count,
    )
    print(f"Saved: {os.path.abspath(args.output)}")
    print(f"Plotted rows: {len(labeled_traces)}")
    print(f"Unique groups: {len(all_groups)}")


if __name__ == "__main__":
    main()
