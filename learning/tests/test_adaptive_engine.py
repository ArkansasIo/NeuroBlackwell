from learning.src.adaptive_engine import AssessmentEngine
def test_select_and_submit():
 q=[{'id':'q1','level':'elementary','subject':'mathematics','skill':'addition','difficulty':2,'answer':3}]; e=AssessmentEngine(q); r=e.submit(e.select_next('elementary','mathematics',2),3); assert r['correct'] is True and r['accuracy']==1.0
