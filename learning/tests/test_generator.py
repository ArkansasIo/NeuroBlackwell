from learning.src.question_generator import generate_arithmetic

def test_generator_is_deterministic():
    assert generate_arithmetic(42)==generate_arithmetic(42)

def test_generated_answer_is_correct():
    q=generate_arithmetic(7)
    a,b=[int(x) for x in q['prompt'].replace('What is ','').replace('?','').split(' + ')]
    assert q['answer']==a+b
