"""Synthetic tissue/network simulator.

Educational computational model inspired by published neuron/tissue-computing
literature. It is not a biological replica, medical model, or validated CL1
emulator. Parameters are deliberately explicit and inspectable.
"""
from __future__ import annotations
from dataclasses import dataclass
import math, random

@dataclass
class TissueParameters:
    neurons: int = 128
    dt_ms: float = 0.1
    tau_m_ms: float = 20.0
    resting_mv: float = -65.0
    threshold_mv: float = -50.0
    reset_mv: float = -68.0
    refractory_ms: float = 2.0
    synaptic_decay_ms: float = 5.0
    learning_rate: float = 0.002
    connection_probability: float = 0.05
    noise_std: float = 0.4

class SyntheticTissue:
    def __init__(self, params: TissueParameters|None=None, seed:int=0):
        self.p=params or TissueParameters()
        if self.p.neurons<1 or not 0<self.p.dt_ms<=10: raise ValueError("invalid tissue dimensions or timestep")
        self.rng=random.Random(seed)
        n=self.p.neurons
        self.v=[self.p.resting_mv]*n
        self.syn=[0.0]*n
        self.refractory=[0.0]*n
        self.weights=[{} for _ in range(n)]
        for i in range(n):
            for j in range(n):
                if i!=j and self.rng.random()<self.p.connection_probability:
                    self.weights[i][j]=self.rng.uniform(0.0,0.15)
        self.spikes=[]

    def step(self, external:dict[int,float]|None=None, t_ms:float=0.0):
        external=external or {}
        fired=[]
        decay=math.exp(-self.p.dt_ms/self.p.synaptic_decay_ms)
        for i in range(len(self.v)):
            self.syn[i]*=decay
            self.refractory[i]=max(0.0,self.refractory[i]-self.p.dt_ms)
            if self.refractory[i]>0: continue
            drive=external.get(i,0.0)+self.syn[i]+self.rng.gauss(0.0,self.p.noise_std)
            dv=((self.p.resting_mv-self.v[i])+drive*self.p.tau_m_ms)/self.p.tau_m_ms*self.p.dt_ms
            self.v[i]+=dv
            if self.v[i]>=self.p.threshold_mv:
                self.v[i]=self.p.reset_mv
                self.refractory[i]=self.p.refractory_ms
                fired.append(i)
        for src in fired:
            for dst,w in self.weights[src].items(): self.syn[dst]+=w
        self.spikes.extend({"t_ms":round(t_ms,6),"neuron":i} for i in fired)
        return fired

    def run(self,duration_ms:float,external_schedule:dict[int,dict[int,float]]|None=None):
        if duration_ms<=0: raise ValueError("duration_ms must be positive")
        steps=math.ceil(duration_ms/self.p.dt_ms)
        for k in range(steps):
            self.step((external_schedule or {}).get(k,{}),k*self.p.dt_ms)
        return {"duration_ms":duration_ms,"neurons":len(self.v),"spikes":len(self.spikes),"spike_events":self.spikes}

    def reset(self):
        self.v=[self.p.resting_mv]*len(self.v); self.syn=[0.0]*len(self.v); self.refractory=[0.0]*len(self.v); self.spikes=[]
