"""Numerical integration helpers."""

def trapezoid(fn, a, b, n=1000):
    step=(b-a)/n
    total=0.5*(fn(a)+fn(b))
    for i in range(1,n):
        total += fn(a+i*step)
    return total*step
