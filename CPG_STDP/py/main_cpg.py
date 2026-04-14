#!/usr/bin/env python3
import sys
import os
import time

# Fix for macOS having PYTHONPATH pointing to system NEURON
if "darwin" in sys.platform:
    sys.path = [p for p in sys.path if "/Applications/NEURON/lib/python" not in p]
    if "PYTHONPATH" in os.environ:
        del os.environ["PYTHONPATH"]

from constants import *
from utils_cpg import *
from leg import *
from recorg_cpg import *


def count_group_neurons(groups):
    total = 0
    details = []
    for group in groups:
        try:
            n = len(group[k_nrns])
            name = group[k_name]
        except Exception:
            n = 0
            name = "unknown"
        total += n
        details.append((name, n))
    return total, details


def count_leg_neurons(leg):
    result = {}

    for attr in ["motogroups", "affgroups", "intgroups", "musclegroups"]:
        groups = getattr(leg, attr, [])
        total, details = count_group_neurons(groups)
        result[attr] = {
            "total": total,
            "details": details
        }

    result["grand_total"] = sum(v["total"] for k, v in result.items() if isinstance(v, dict))
    return result


def log_leg_stats(leg, leg_name="LEG"):
    stats = count_leg_neurons(leg)

    logging.info(f"[{leg_name}] total neurons: {stats['grand_total']}")
    for attr in ["motogroups", "affgroups", "intgroups", "musclegroups"]:
        logging.info(f"[{leg_name}] {attr}: {stats[attr]['total']}")
        for group_name, n in stats[attr]["details"]:
            logging.info(f"[{leg_name}]   {group_name}: {n}")

    return stats


def try_count_synapses(leg):
    """
    Пытаемся найти списки соединений / syn / netcon по типовым именам.
    Это эвристика: если в классе LEG уже есть такие атрибуты, будет полезно.
    """
    candidates = [
        "synapses",
        "all_synapses",
        "netcons",
        "connections",
        "all_connections",
        "nc",
        "nclist",
        "exnclist",
        "innclist",
        "weight_changes_vectors",
    ]

    counts = {}
    total = 0

    for name in candidates:
        if hasattr(leg, name):
            value = getattr(leg, name)
            try:
                cnt = len(value)
                counts[name] = cnt
                total += cnt
            except Exception:
                pass

    return total, counts


def prun(speed, step_number):
    logging.info(f"prun start: speed={speed}, steps={step_number}, time_sim={time_sim}")
    sim_t0 = time.perf_counter()

    try:
        pc.timeout(0)

        t = h.Vector().record(h._ref_t)
        h.tstop = time_sim

        import platform
        is_macos = platform.system() == "Darwin"

        if is_macos:
            h.dt = 0.025
            h.cvode_active(0)
            pc.set_maxstep(1)
        else:
            pc.set_maxstep(10)

        h.finitialize(-65)
        logging.info(f"Integrator settings: dt={h.dt}, tstop={h.tstop}, is_macos={is_macos}")
        logging.info("finitialize completed")

        if is_macos:
            next_log_t = 500.0
            while h.t < time_sim:
                h.fadvance()
                if h.t >= next_log_t:
                    logging.info(f"Progress: {h.t:.1f}/{time_sim} ms")
                    next_log_t += 500.0
        else:
            pc.psolve(time_sim)

        sim_elapsed = time.perf_counter() - sim_t0
        logging.info(f"Simulation completed successfully in {sim_elapsed:.3f} s")
        return t, sim_elapsed

    except Exception as sim_error:
        logging.exception(f"Simulation error: {sim_error}")
        raise


def finish():
    """proper exit"""
    pc.runworker()
    pc.done()
    h.quit()


if __name__ == '__main__':
    """
    cpg_ex: cpg
        topology of central pattern generation + reflex arc
    """
    logging.info("=== MAIN EXECUTION START ===")
    logging.info(f"Rank {rank} of {nhost} processes")
    logging.info(f"Parameters: N={N}, speed={speed}, bs_fr={bs_fr}, versions={versions}")
    logging.info(f"Step number: {step_number}, one_step_time: {one_step_time}")
    logging.info(f"Total simulation time: {time_sim} ms")

    if rank == 0:
        os.makedirs(file_name, exist_ok=True)
        logging.info(f"Created directory: {file_name}")

    pc.barrier()

    main_t0 = time.perf_counter()

    for i in range(versions):
        version_t0 = time.perf_counter()
        logging.info(f"=== VERSION {i + 1} START ===")

        try:
            build_t0 = time.perf_counter()

            LEG_L = LEG(speed, bs_fr, 100, step_number, N, leg_l=True)
            LEG_R = LEG(speed, bs_fr, 100, step_number, N, leg_l=False)
            create_connect_bs(LEG_L, LEG_R)
            add_external_connections(LEG_L, LEG_R)

            build_time = time.perf_counter() - build_t0
            logging.info(f"[version {i + 1}] network build time: {build_time:.3f} s")

            pc.barrier()

            stats_l = log_leg_stats(LEG_L, "LEG_L")
            stats_r = log_leg_stats(LEG_R, "LEG_R")

            total_neurons = stats_l["grand_total"] + stats_r["grand_total"]
            logging.info(f"[version {i + 1}] total neurons in simulation: {total_neurons}")

            syn_l_total, syn_l_details = try_count_synapses(LEG_L)
            syn_r_total, syn_r_details = try_count_synapses(LEG_R)
            total_synapses = syn_l_total + syn_r_total

            logging.info(f"[version {i + 1}] estimated synapses LEG_L: {syn_l_total}, details={syn_l_details}")
            logging.info(f"[version {i + 1}] estimated synapses LEG_R: {syn_r_total}, details={syn_r_details}")
            logging.info(f"[version {i + 1}] estimated total synapses: {total_synapses}")

            pc.barrier()
            recorder_t0 = time.perf_counter()

            motorecorders_l = []
            motorecorders_mem_l = []
            musclerecorders_l = []
            muscle_units_recorders_l = []
            muscle_am_recorders_l = []
            force_recorders_l = []
            affrecorders_l = []
            recorders_l = []

            motorecorders_r = []
            motorecorders_mem_r = []
            musclerecorders_r = []
            muscle_units_recorders_r = []
            muscle_am_recorders_r = []
            force_recorders_r = []
            affrecorders_r = []
            recorders_r = []

            setup_recorders(LEG_L, motorecorders_mem_l, 'motogroups', 'motor')
            setup_recorders(LEG_R, motorecorders_mem_r, 'motogroups', 'motor')
            setup_recorders(LEG_L, affrecorders_l, 'affgroups', 'afferent')
            setup_recorders(LEG_R, affrecorders_r, 'affgroups', 'afferent')
            setup_recorders(LEG_L, recorders_l, 'intgroups', 'interneuron')
            setup_recorders(LEG_R, recorders_r, 'intgroups', 'interneuron')

            for group in getattr(LEG_L, "musclegroups"):
                musclerecorders_l.append(spike_record(group[k_nrns]))
                force_recorders_l.append(force_record(group[k_nrns]))
                muscle_units_recorders_l.append(spike_record(group[k_nrns], location='muscle'))
                muscle_am_recorders_l.append(spike_record(group[k_nrns], location='am'))

            for group in LEG_R.musclegroups:
                musclerecorders_r.append(spike_record(group[k_nrns]))
                force_recorders_r.append(force_record(group[k_nrns]))
                muscle_units_recorders_r.append(spike_record(group[k_nrns], location='muscle'))
                muscle_am_recorders_r.append(spike_record(group[k_nrns], location='am'))

            recorder_time = time.perf_counter() - recorder_t0

            logging.info(f"[version {i + 1}] recorder setup time: {recorder_time:.3f} s")
            logging.info(
                f"[version {i + 1}] recorders count: "
                f"motor_mem_l={len(motorecorders_mem_l)}, motor_mem_r={len(motorecorders_mem_r)}, "
                f"aff_l={len(affrecorders_l)}, aff_r={len(affrecorders_r)}, "
                f"int_l={len(recorders_l)}, int_r={len(recorders_r)}, "
                f"muscle_l={len(musclerecorders_l)}, muscle_r={len(musclerecorders_r)}, "
                f"force_l={len(force_recorders_l)}, force_r={len(force_recorders_r)}"
            )

            pc.barrier()

            logging.info(f"[version {i + 1}] simulation start")
            t, sim_time_sec = prun(speed, step_number)
            logging.info(f"[version {i + 1}] simulation time: {sim_time_sec:.3f} s")

            save_t0 = time.perf_counter()

            if rank == 0:
                with open(f'./{file_name}/time.txt', 'w') as time_file:
                    for time_val in t:
                        time_file.write(str(time_val) + "\n")

            for group, recorder in zip(LEG_L.musclegroups, musclerecorders_l):
                spikeout(group[k_nrns], group[k_name], i, recorder, "left")
            for group, recorder in zip(LEG_L.motogroups, motorecorders_mem_l):
                spikeout(group[k_nrns], f'mem_{group[k_name]}', i, recorder, "left")
            for group, recorder in zip(LEG_L.affgroups, affrecorders_l):
                spikeout(group[k_nrns], group[k_name], i, recorder, "left")
            for group, recorder in zip(LEG_L.intgroups, recorders_l):
                spikeout(group[k_nrns], group[k_name], i, recorder, "left")
            for group, recorder in zip(LEG_L.musclegroups, force_recorders_l):
                spikeout(group[k_nrns], f'force_{group[k_name]}', i, recorder, "left")
            for group, recorder in zip(LEG_L.musclegroups, muscle_units_recorders_l):
                spikeout(group[k_nrns], f'units_{group[k_name]}', i, recorder, "left")
            for group, recorder in zip(LEG_L.musclegroups, muscle_am_recorders_l):
                spikeout(group[k_nrns], f'am_{group[k_name]}', i, recorder, "left")

            for group, recorder in zip(LEG_R.musclegroups, musclerecorders_r):
                spikeout(group[k_nrns], group[k_name], i, recorder, "right")
            for group, recorder in zip(LEG_R.motogroups, motorecorders_mem_r):
                spikeout(group[k_nrns], f'mem_{group[k_name]}', i, recorder, "right")
            for group, recorder in zip(LEG_R.affgroups, affrecorders_r):
                spikeout(group[k_nrns], group[k_name], i, recorder, "right")
            for group, recorder in zip(LEG_R.intgroups, recorders_r):
                spikeout(group[k_nrns], group[k_name], i, recorder, "right")
            for group, recorder in zip(LEG_R.musclegroups, force_recorders_r):
                spikeout(group[k_nrns], f'force_{group[k_name]}', i, recorder, "right")
            for group, recorder in zip(LEG_R.musclegroups, muscle_units_recorders_r):
                spikeout(group[k_nrns], f'units_{group[k_name]}', i, recorder, "right")
            for group, recorder in zip(LEG_R.musclegroups, muscle_am_recorders_r):
                spikeout(group[k_nrns], f'am_{group[k_name]}', i, recorder, "right")

            if rank == 0:
                stdp_dir = f'./{file_name}/stdp_1'
                if not os.path.exists(stdp_dir):
                    os.makedirs(stdp_dir)

                stdp_count = 0
                for src_gid, post_gid, weight_vec in LEG_L.weight_changes_vectors:
                    try:
                        src_obj = pc.gid2cell(src_gid) if pc.gid_exists(src_gid) else None
                        post_obj = pc.gid2cell(post_gid) if pc.gid_exists(post_gid) else None

                        src_type = type(src_obj).__name__ if src_obj is not None else "None"
                        post_type = type(post_obj).__name__ if post_obj is not None else "None"

                        safe_name = safe_filename(f'{src_type}_{src_gid}_to_{post_type}_{post_gid}.hdf5')
                        fname = f'{stdp_dir}/{safe_name}'

                        with hdf5.File(fname, 'w') as file:
                            file.create_dataset(f'#0_step_{i}', data=np.array(weight_vec), compression="gzip")
                        stdp_count += 1

                    except Exception as e:
                        logging.warning(f"Error saving STDP weight {src_gid} -> {post_gid}: {e}")

                logging.info(f"[version {i + 1}] saved STDP weight files: {stdp_count}")

            save_time = time.perf_counter() - save_t0
            logging.info(f"[version {i + 1}] save time: {save_time:.3f} s")
            total_version_time = time.perf_counter() - version_t0
            logging.info(
                f"[version {i + 1}] summary: "
                f"neurons={total_neurons}, "
                f"estimated_synapses={total_synapses}, "
                f"build_time={build_time:.3f} s, "
                f"recorder_time={recorder_time:.3f} s, "
                f"simulation_time={sim_time_sec:.3f} s, "
                f"save_time={save_time:.3f} s, "
                f"total_version_time={total_version_time:.3f} s"
            )

        except Exception as version_error:
            logging.exception(f"Version {i + 1} error: {version_error}")
            break

    logging.info("=== MAIN EXECUTION END ===")
    main_total_time = time.perf_counter() - main_t0
    logging.info(f"Total main execution time: {main_total_time:.3f} s")
    finish()