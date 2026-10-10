from fastapi import APIRouter, HTTPException
from pydantic import BaseModel, Field
from neuroblackwell.integrations.cortical_labs import CorticalLabsAdapter, CorticalLabsConfig, CorticalLabsUnavailable
router=APIRouter(prefix='/api/v1/integrations/cortical-labs',tags=['integrations'])
def adapter(): return CorticalLabsAdapter(CorticalLabsConfig.from_env())
@router.get('/status')
def status():
 try: return adapter().status()
 except (ValueError,CorticalLabsUnavailable) as e: raise HTTPException(status_code=503,detail=str(e))
class RecordRequest(BaseModel): duration_s:float=Field(gt=0,le=3600); file_location:str|None=None
@router.post('/record')
def record(req:RecordRequest):
 try: return adapter().record(req.duration_s,req.file_location)
 except PermissionError as e: raise HTTPException(status_code=403,detail=str(e))
 except (ValueError,CorticalLabsUnavailable) as e: raise HTTPException(status_code=503,detail=str(e))
class StimRequest(BaseModel): channel:int=Field(ge=0); current_ua:float
@router.post('/stimulate')
def stimulate(req:StimRequest):
 try: return adapter().stimulate(req.channel,req.current_ua)
 except PermissionError as e: raise HTTPException(status_code=403,detail=str(e))
 except ValueError as e: raise HTTPException(status_code=422,detail=str(e))
 except CorticalLabsUnavailable as e: raise HTTPException(status_code=503,detail=str(e))
