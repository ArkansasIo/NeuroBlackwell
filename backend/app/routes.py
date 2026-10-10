from fastapi import APIRouter
from .schemas import SimulationRequest,MathRequest,ExperimentCreate
from .simulation import run_simulation

router=APIRouter(prefix='/api/v1')
@router.post('/simulations/run')
def run(req:SimulationRequest): return run_simulation(req)
@router.post('/math/evaluate')
def math_eval(req:MathRequest):
    import math
    if req.operation=='sum': return {'value':sum(req.values)}
    if req.operation=='mean': return {'value':sum(req.values)/len(req.values) if req.values else 0}
    if req.operation=='entropy':
        s=sum(req.values); p=[x/s for x in req.values if x>0] if s else []
        return {'value':-sum(x*math.log2(x) for x in p)}
    return {'error':'unsupported operation'}
@router.post('/experiments')
def create_experiment(req:ExperimentCreate): return {'id':None,'name':req.name,'task':req.task,'parameters':req.parameters}
