"""Plugin registration hook for NeuroBlackwell's integration registry."""
from .adapter import CorticalLabsAdapter

def register(registry):
    registry.register('cortical_labs', lambda config=None: CorticalLabsAdapter(config=config))
