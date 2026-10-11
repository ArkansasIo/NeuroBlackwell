from fastapi import APIRouter, HTTPException
from learning.api import create_engine

router=APIRouter(prefix='/api/v1/learning',tags=['learning'])

@router.get('/next')
def next_question(level:str='elementary',subject:str|None=None,difficulty:float|None=None):
    try:
        return create_engine().select_next(level,subject,difficulty)
    except LookupError as exc:
        raise HTTPException(status_code=404,detail=str(exc))

@router.get('/levels')
def levels():
    return {'levels':['kindergarten','elementary','middle_school','high_school','college','university','graduate_research']}
