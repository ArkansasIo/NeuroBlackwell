"""Deterministic scalar gradient descent."""

def minimize(f, df, x0, learning_rate=0.01, steps=100):
    x=float(x0)
    for _ in range(steps):
        x -= learning_rate*df(x)
    return {"x":x,"value":f(x),"steps":steps}
