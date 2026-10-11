import random
def generate_arithmetic(seed:int,level='elementary'):
    rng=random.Random(seed); a,b=rng.randint(1,99),rng.randint(1,99)
    return {'id':f'GEN-ADD-{seed}','level':level,'subject':'mathematics','domain':'arithmetic','skill':'addition','difficulty':2,'cognitive_operation':'calculation','prerequisite_skills':['counting'],'prompt':f'What is {a} + {b}?','answer':a+b,'unit':None,'provenance':'synthetic','tags':['generated','addition']}
