#!/usr/bin/env python3
"""Generate deterministic synthetic brain scene data for visualization tests."""
import json, math, random
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
OUT = ROOT / "data" / "generated_demo_brain.json"
R = random.Random(20261010)
neurons=[]
for hemisphere, sign in (("L",-1),("R",1)):
    for i in range(250):
        a=2*math.pi*(i/250.0)
        fold=0.82+0.10*math.sin(7*a)+0.05*math.sin(13*a)
        x=sign*(0.10+0.72*fold*math.cos(a))
        y=0.82*fold*math.sin(a)
        z=0.28*math.sin(3*a+i*0.07)
        neurons.append({"id":len(neurons),"hemisphere":hemisphere,"x":round(x,9),"y":round(y,9),"z":round(z,9),"type":"inhibitory" if i%8==0 else "excitatory"})
connections=[]
for n in neurons:
    candidates=[]
    for m in neurons:
        if n["id"]==m["id"]: continue
        d=math.sqrt((n["x"]-m["x"])**2+(n["y"]-m["y"])**2+(n["z"]-m["z"])**2)
        if d<0.18: candidates.append((d,m["id"]))
    candidates.sort()
    for d,j in candidates[:3]:
        if n["id"]<j: connections.append({"source":n["id"],"target":j,"distance":round(d,9),"weight":round(0.2+0.8*R.random(),6)})
scene={"dataset_id":"NB-DEMO-BRAIN-001","status":"synthetic_demo","coordinate_system":"normalized_brain_xyz","neurons":neurons,"connections":connections}
OUT.write_text(json.dumps(scene,indent=2),encoding="utf-8")
print(f"wrote {OUT} neurons={len(neurons)} connections={len(connections)}")
