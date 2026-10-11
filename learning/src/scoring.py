from __future__ import annotations
import math

def sigmoid(x: float) -> float:
    if x >= 0:
        z=math.exp(-x); return 1/(1+z)
    z=math.exp(x); return z/(1+z)

def expected_correctness(mastery: float,difficulty: float)->float:
    return sigmoid(mastery-difficulty)

def score_response(correct: bool,difficulty: float,response_time_ms: float|None=None)->dict:
    raw=1.0 if correct else 0.0
    speed=0.0 if not response_time_ms or response_time_ms<=0 else min(0.15,10000/response_time_ms/100)
    return {'correct':correct,'difficulty':float(difficulty),'raw_score':raw,'speed_bonus':speed,'score':min(1.0,raw+speed)}
