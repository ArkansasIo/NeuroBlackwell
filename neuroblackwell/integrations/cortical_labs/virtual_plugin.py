from .virtual_hardware import VirtualHardware

def create_virtual_hardware(channels=1024,seed=0): return VirtualHardware(channels=channels,seed=seed)
