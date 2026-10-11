"""Odd/even benchmark with reproducible generated samples."""

def classify(n):
    return "even" if n % 2 == 0 else "odd"

def accuracy(values):
    return sum(classify(n)==label for n,label in values)/len(values) if values else 0.0
