from pydantic import BaseModel, Field
from typing import Any

class SimulationRequest(BaseModel):
    neurons:int=Field(64,ge=1,le=100000)
    duration_ms:float=Field(1000,gt=0,le=3600000)
    dt_ms:float=Field(1,gt=0)
    seed:int=0

class MathRequest(BaseModel):
    operation:str
    values:list[float]=[]

class ExperimentCreate(BaseModel):
    name:str
    task:str
    parameters:dict[str,Any]={}
