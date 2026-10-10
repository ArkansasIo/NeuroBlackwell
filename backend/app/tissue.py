from fastapi import APIRouter
from pydantic import BaseModel,Field
from neuroblackwell.integrations.cortical_labs.tissue_simulator import SyntheticTissue,TissueParameters
router=APIRouter(prefix='/api/v1/tissue',tags=['synthetic-tissue'])
class TissueRequest(BaseModel):
 neurons:int=Field(128,ge=1,le=5000); duration_ms:float=Field(100,gt=0,le=100000); seed:int=0
@router.post('/simulate')
def simulate(req:TissueRequest):
 return SyntheticTissue(TissueParameters(neurons=req.neurons),req.seed).run(req.duration_ms)
