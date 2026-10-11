from learning.src.scoring import expected_correctness,score_response
def test_probability_order(): assert expected_correctness(5,2)>expected_correctness(0,5)
def test_score(): assert score_response(True,2)['raw_score']==1.0
