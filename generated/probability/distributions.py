"""Small probability primitives for experiments."""
import math

def bernoulli_pmf(k,p):
    if k not in (0,1):
        return 0.0
    return p if k else 1-p

def poisson_pmf(k,lam):
    if k < 0:
        return 0.0
    return math.exp(-lam)*lam**k/math.factorial(k)
