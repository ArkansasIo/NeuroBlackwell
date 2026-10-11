from learning.src.mastery import MasteryModel
def test_correct_response_increases_mastery():
 m=MasteryModel(); before=m.state('addition').mastery; m.update('addition',2,True); assert m.state('addition').mastery>before
def test_accuracy():
 m=MasteryModel(); m.update('x',2,True); m.update('x',2,False); assert m.state('x').accuracy==0.5
