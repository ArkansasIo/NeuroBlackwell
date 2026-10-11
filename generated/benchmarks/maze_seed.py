"""Seeded maze coordinate generator used for reproducible benchmarks."""
import random

def sample_cells(width,height,seed=0,count=16):
    rng=random.Random(seed)
    cells=[(x,y) for y in range(height) for x in range(width)]
    rng.shuffle(cells)
    return cells[:min(count,len(cells))]
