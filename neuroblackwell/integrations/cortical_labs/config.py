from dataclasses import dataclass
import os

@dataclass(frozen=True)
class CorticalLabsConfig:
    mode: str = 'simulator'
    enabled: bool = False
    allow_stimulation: bool = False
    max_current_ua: float = 3.0

    @classmethod
    def from_env(cls):
        mode=os.getenv('CL_MODE','simulator').strip().lower()
        if mode not in {'simulator','hardware'}:
            raise ValueError('CL_MODE must be simulator or hardware')
        enabled=os.getenv('CL_ENABLED','false').lower() in {'1','true','yes'}
        allow=os.getenv('CL_ALLOW_STIMULATION','false').lower() in {'1','true','yes'}
        limit=float(os.getenv('CL_MAX_CURRENT_UA','3.0'))
        if not 0 < limit <= 3.0:
            raise ValueError('CL_MAX_CURRENT_UA must be > 0 and <= 3.0')
        if mode == 'hardware' and not enabled:
            raise ValueError('Hardware mode requires CL_ENABLED=true')
        return cls(mode,enabled,allow,limit)
