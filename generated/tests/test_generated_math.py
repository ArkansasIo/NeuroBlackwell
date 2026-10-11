import math
from generated.calculus.integral_outputs import output_suite
from generated.calculus.integration import trapezoid
from generated.algebra.polynomial import evaluate, derivative
from generated.benchmarks.maze_seed import sample_cells

def test_integral_outputs():
    out=output_suite()
    assert math.isclose(out["int_x_0_1"], 0.5)
    assert math.isclose(out["int_x2_0_1"], 1/3)
    assert math.isclose(out["int_exp_0_1"], math.e-1)
    assert math.isclose(out["int_sin_0_pi"], 2.0, abs_tol=1e-12)

def test_trapezoid():
    assert abs(trapezoid(lambda x:x*x,0,1,10000)-1/3) < 1e-7

def test_polynomial():
    assert evaluate([0,0,1],3)==9
    assert derivative([0,0,1])==[0,2]

def test_seeded_tree_samples():
    assert sample_cells(5,5,seed=77)==sample_cells(5,5,seed=77)
