from pathlib import Path
import json
from .src.adaptive_engine import AssessmentEngine
ROOT=Path(__file__).resolve().parent
def load_questions(): return json.loads((ROOT/'data/question_bank.json').read_text())['questions']
def create_engine(): return AssessmentEngine(load_questions())
