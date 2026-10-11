"""Finite-difference calculus helpers."""

def central_difference(fn, x, h=1e-6):
    return (fn(x+h)-fn(x-h))/(2*h)

def second_difference(fn, x, h=1e-4):
    return (fn(x+h)-2*fn(x)+fn(x-h))/(h*h)
