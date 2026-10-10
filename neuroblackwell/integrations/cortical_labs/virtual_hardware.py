"""Deterministic virtual CL1-like hardware for integration and CI testing.

This is software-only and must never be represented as a biological or electrical
model of a real CL1 device. It provides channels, synthetic spikes, recording,
and bounded stimulation events so the same NeuroBlackwell API can be tested
without physical hardware.
"""
from dataclasses import dataclass,field
import random,time
@dataclass
class VirtualHardware:
 channels:int=1024
 seed:int=0
 connected:bool=False
 events:list[dict]=field(default_factory=list)
 def __enter__(self): self.connected=True; return self
 def __exit__(self,*args): self.connected=False
 def status(self): return {'connected':self.connected,'mode':'virtual','channels':self.channels}
 def stimulate(self,channel:int,current_ua:float):
  if not self.connected: raise RuntimeError('virtual hardware is not connected')
  if not 0<=channel<self.channels: raise ValueError('invalid virtual channel')
  event={'timestamp_s':time.time(),'channel':channel,'current_ua':current_ua}
  self.events.append(event); return event
 def record(self,duration_s:float,rate_hz:float=5.0):
  if not self.connected: raise RuntimeError('virtual hardware is not connected')
  rng=random.Random(self.seed); n=max(0,int(duration_s*rate_hz)); return [{'t_s':i/max(rate_hz,1e-9),'channel':rng.randrange(self.channels)} for i in range(n) if rng.random()<0.5]
