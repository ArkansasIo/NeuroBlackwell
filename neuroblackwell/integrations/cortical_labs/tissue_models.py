from dataclasses import dataclass
import math
@dataclass(frozen=True)
class LIFModel:
    tau_ms:float=20.0; rest_mv:float=-65.0; threshold_mv:float=-50.0; reset_mv:float=-68.0
    def derivative(self,v:float,input_current:float)->float:
        return ((self.rest_mv-v)+input_current*self.tau_ms)/self.tau_ms
@dataclass(frozen=True)
class SynapseModel:
    tau_ms:float=5.0
    def decay(self,dt_ms:float)->float: return math.exp(-dt_ms/self.tau_ms)
@dataclass(frozen=True)
class PlasticityModel:
    learning_rate:float=0.002
    def hebbian_delta(self,pre:float,post:float)->float: return self.learning_rate*pre*post
