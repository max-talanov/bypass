import logging
from dataclasses import dataclass

from constants import pc, rank, h, CV_number
from utils_cpg import get_gid, genconnect, logger_addgener

logger = logging.getLogger("bs_command")


@dataclass
class BSMode:
    name: str

    start_ms: float          # when the command fires
    burst_duration_ms: float # how long the tonic drive lasts
    drive_freq_hz: float     # spike frequency inside burst (not the step rhythm)
    drive_weight_RG: float   # synaptic weight onto RG pools
    drive_weight_In: float   # synaptic weight onto InE / InF (for mutual inhibition seeding)

    rg_self_weight: float    # RG→RG recurrent excitation (within-nucleus)
    InEF_inh_weight: float   # InE→RG_F / InF→RG_E inhibitory weight
    rg2mns_weight: float     # RG → motoneuron drive


WALK = BSMode(
    name="walk",
    start_ms=5.0,
    burst_duration_ms=50.0,
    drive_freq_hz=40.0,
    drive_weight_RG=1.2,
    drive_weight_In=0.4,
    rg_self_weight=0.35,
    InEF_inh_weight=0.5,
    rg2mns_weight=2.75,
)

RUN = BSMode(
    name="run",
    start_ms=5.0,
    burst_duration_ms=80.0,
    drive_freq_hz=80.0,
    drive_weight_RG=1.8,
    drive_weight_In=0.9,
    rg_self_weight=0.55,
    InEF_inh_weight=0.7,
    rg2mns_weight=3.5,
)

def _make_command_stim(leg_obj, start_ms: float, duration_ms: float,
                       freq_hz: float) -> int:
    gid = get_gid()
    interval_ms = 1000.0 / freq_hz
    n_spikes = max(1, int(duration_ms / interval_ms))

    if rank == 0:
        stim = h.NetStim()
        stim.start = start_ms
        stim.interval = interval_ms
        stim.number = n_spikes
        stim.noise = 0.0

        logger_addgener.info(
            "BS_CMD STIM | gid=%s | start=%.1f | interval=%.1f | number=%d",
            gid, stim.start, stim.interval, stim.number,
        )

        leg_obj.stims.append(stim)
        pc.set_gid2node(gid, rank)
        ncstim = h.NetCon(stim, None)
        spike_times = h.Vector()
        ncstim.record(spike_times)
        leg_obj.gen_spike_vectors.append((gid, spike_times))
        leg_obj.netcons.append(ncstim)
        pc.cell(gid, ncstim)
    else:
        pc.set_gid2node(gid, 0)

    leg_obj.gener_gids.append(gid)
    return gid


class BSCommand:
    def __init__(self, mode: BSMode):
        self.mode = mode
        self.left_cmd_gids: list[int] = []
        self.right_cmd_gids: list[int] = []

    def connect(self, LEG_L, LEG_R) -> None:
        m = self.mode
        logger.info("BSCommand.connect: mode=%s", m.name)

        # (leg, gid_store, label, E_delay, F_delay, E_weight_scale, F_weight_scale)
        leg_configs = [
            (LEG_L, self.left_cmd_gids,  "LEFT",   1.0, 15.0, 1.0, 0.15),
            (LEG_R, self.right_cmd_gids, "RIGHT", 15.0,  1.0, 0.15, 1.0),
        ]

        for leg_obj, gid_store, label, e_delay, f_delay, e_scale, f_scale in leg_configs:
            cmd_gid = _make_command_stim(
                leg_obj,
                start_ms=m.start_ms,
                duration_ms=m.burst_duration_ms,
                freq_hz=m.drive_freq_hz,
            )
            gid_store.append(cmd_gid)

            for layer in range(CV_number):
                genconnect(
                    leg_obj, cmd_gid, leg_obj.dict_RG_E[layer],
                    weight=m.drive_weight_RG * e_scale, delay=e_delay,
                    gen_name=f"BS_CMD_{label}_E",
                    target_name=f"{label}_RG_E_{layer+1}",
                )
                genconnect(
                    leg_obj, cmd_gid, leg_obj.dict_RG_F[layer],
                    weight=m.drive_weight_RG * f_scale, delay=f_delay,
                    gen_name=f"BS_CMD_{label}_F",
                    target_name=f"{label}_RG_F_{layer+1}",
                )

            genconnect(
                leg_obj, cmd_gid, leg_obj.InE,
                weight=m.drive_weight_In * e_scale, delay=e_delay,
                gen_name=f"BS_CMD_{label}_InE",
                target_name=f"{label}_InE",
            )
            genconnect(
                leg_obj, cmd_gid, leg_obj.InF,
                weight=m.drive_weight_In * f_scale, delay=f_delay,
                gen_name=f"BS_CMD_{label}_InF",
                target_name=f"{label}_InF",
            )

            logger.info(
                "BSCommand wired %s: cmd_gid=%d, RG layers=%d, "
                "E_scale=%.1f F_scale=%.1f E_delay=%.1f F_delay=%.1f",
                label, cmd_gid, CV_number, e_scale, f_scale, e_delay, f_delay,
            )

    @property
    def all_cmd_gids(self) -> list[int]:
        return self.left_cmd_gids + self.right_cmd_gids


def apply_bs_mode_to_cpg(LEG_L, LEG_R, mode: BSMode) -> None:
    logger.info("apply_bs_mode_to_cpg: mode=%s", mode.name)

    for leg_obj in (LEG_L, LEG_R):
        _scale_connections_by_name(
            leg_obj,
            src_pools=sum([list(leg_obj.dict_RG_E[l]) for l in range(CV_number)], [])
                    + sum([list(leg_obj.dict_RG_F[l]) for l in range(CV_number)], []),
            dst_pools=sum([list(leg_obj.dict_RG_E[l]) for l in range(CV_number)], [])
                    + sum([list(leg_obj.dict_RG_F[l]) for l in range(CV_number)], []),
            new_weight=mode.rg_self_weight,
            label="RG self-excitation",
        )

        _scale_connections_by_name(
            leg_obj,
            src_pools=leg_obj.InE,
            dst_pools=leg_obj.RG_F,
            new_weight=mode.InEF_inh_weight,
            label="InE->RG_F inhibition",
        )
        _scale_connections_by_name(
            leg_obj,
            src_pools=leg_obj.InF,
            dst_pools=leg_obj.RG_E,
            new_weight=mode.InEF_inh_weight,
            label="InF->RG_E inhibition",
        )

        _scale_connections_by_name(
            leg_obj,
            src_pools=leg_obj.RG_E,
            dst_pools=leg_obj.mns_E,
            new_weight=mode.rg2mns_weight,
            label="RG_E->mns_E",
        )
        _scale_connections_by_name(
            leg_obj,
            src_pools=leg_obj.RG_F,
            dst_pools=leg_obj.mns_F,
            new_weight=mode.rg2mns_weight,
            label="RG_F->mns_F",
        )

    logger.info("apply_bs_mode_to_cpg done for mode=%s", mode.name)


def _scale_connections_by_name(leg_obj, src_pools, dst_pools,
                                new_weight: float, label: str) -> int:
    src_set = set(src_pools)

    cell_to_gid: dict = {}
    for gid in dst_pools:
        if pc.gid_exists(gid):
            cell_to_gid[id(pc.gid2cell(gid))] = gid

    updated = 0
    for nc in leg_obj.netcons:
        try:
            pre_gid = int(nc.srcgid())
            if pre_gid not in src_set:
                continue
            syn = nc.syn()
            if syn is None:
                continue
            seg = syn.get_segment()
            if seg is None:
                continue
            post_cell = seg.sec.cell()
            if id(post_cell) in cell_to_gid:
                nc.weight[0] = new_weight
                updated += 1
        except Exception:
            pass

    logger.info("  %-30s: %d NetCons updated -> weight=%.3f", label, updated, new_weight)
    return updated
