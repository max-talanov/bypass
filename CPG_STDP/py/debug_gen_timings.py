
from neuron import h
from constants import *
import utils_cpg

# Dummy class to mock LEG
class DummyLeg:
    def __init__(self):
        self.stims = []
        self.gener_gids = []
        self.netcons = []

def check_timings():
    print(f"speed: {speed}")
    print(f"bs_fr: {bs_fr}")
    print(f"one_step_time: {one_step_time}")
    print(f"step_number: {step_number}")
    
    leg_l = DummyLeg()
    leg_r = DummyLeg()
    
    utils_cpg.add_bs_geners(bs_fr, leg_l, leg_r)
    
    print(f"Left Leg Stims: {len(leg_l.stims)}")
    print(f"Right Leg Stims: {len(leg_r.stims)}")
    
    all_stims = []
    # Collect all stims with their info
    for i, stim in enumerate(leg_l.stims):
        all_stims.append({
            "leg": "L",
            "id": i,
            "start": stim.start,
            "interval": stim.interval,
            "number": stim.number,
            "end": stim.start + (stim.number * stim.interval) # Approximation of end time
        })
        
    for i, stim in enumerate(leg_r.stims):
        all_stims.append({
            "leg": "R",
            "id": i,
            "start": stim.start,
            "interval": stim.interval,
            "number": stim.number,
            "end": stim.start + (stim.number * stim.interval)
        })
        
    # Sort by start time
    all_stims.sort(key=lambda x: x["start"])
    
    print("\nGenerator Timings:")
    for s in all_stims:
        print(f"Leg {s['leg']} ID {s['id']}: Start={s['start']:.2f}, Int={s['interval']}, Num={s['number']}, End={s['end']:.2f}")
        
    # Check for overlaps within the same leg
    print("\nChecking for overlaps within Left Leg:")
    check_overlap(leg_l.stims, "Left")
    
    print("\nChecking for overlaps within Right Leg:")
    check_overlap(leg_r.stims, "Right")

def check_overlap(stims, name):
    sorted_stims = sorted(stims, key=lambda x: x.start)
    for i in range(len(sorted_stims) - 1):
        curr = sorted_stims[i]
        next_stim = sorted_stims[i+1]
        
        curr_end = curr.start + (curr.number * curr.interval)
        next_start = next_stim.start
        
        if curr_end > next_start:
            print(f"❌ OVERLAP detected in {name} leg!")
            print(f"   Stim {i} ends at {curr_end:.2f}")
            print(f"   Stim {i+1} starts at {next_start:.2f}")
            print(f"   Overlap: {curr_end - next_start:.2f} ms")
        else:
            gap = next_start - curr_end
            # print(f"   Gap between {i} and {i+1}: {gap:.2f} ms")

if __name__ == "__main__":
    check_timings()
