"""Generated integral outputs and quadrature utilities."""
import math

def integrate_power(power, a=0.0, b=1.0):
    return (b**(power+1)-a**(power+1))/(power+1)

def integrate_exp(a=0.0,b=1.0):
    return math.exp(b)-math.exp(a)

def integrate_sine(a=0.0,b=math.pi):
    return -math.cos(b)+math.cos(a)

def output_suite():
    return {"int_x_0_1": integrate_power(1), "int_x2_0_1": integrate_power(2), "int_exp_0_1": integrate_exp(), "int_sin_0_pi": integrate_sine()}
