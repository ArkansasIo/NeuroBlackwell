import json
from pathlib import Path

def test_question_bank_has_all_levels():
    p=Path(__file__).parents[1]/'data'/'question_bank.json'
    questions=json.loads(p.read_text())['questions']
    levels={q['level'] for q in questions}
    assert {'kindergarten','elementary','middle_school','high_school','college','university','graduate_research'} <= levels

def test_question_ids_unique():
    questions=json.loads((Path(__file__).parents[1]/'data'/'question_bank.json').read_text())['questions']
    ids=[q['id'] for q in questions]
    assert len(ids)==len(set(ids))
