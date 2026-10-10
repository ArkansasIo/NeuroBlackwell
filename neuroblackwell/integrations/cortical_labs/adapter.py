"""Thin adapter for the official Cortical Labs `cl` Python API.

The `cl-sdk` package simulates the API locally. Real hardware access requires a
configured CL1 system and its device-provided CL API runtime. No hardware action
is enabled by default. See docs/integrations/cortical-labs.md.
"""
from __future__ import annotations
from contextlib import contextmanager
from importlib import import_module
from typing import Any, Iterator
from .config import CorticalLabsConfig

class CorticalLabsUnavailable(RuntimeError):
    pass

class CorticalLabsAdapter:
    def __init__(self, config: CorticalLabsConfig | None = None, cl_module: Any | None = None):
        self.config=config or CorticalLabsConfig.from_env()
        self._cl=cl_module

    def _module(self):
        if self._cl is None:
            try: self._cl=import_module('cl')
            except ImportError as exc: raise CorticalLabsUnavailable('Install the official simulator package with `pip install cl-sdk`, or use the CL1 device runtime.') from exc
        return self._cl

    @contextmanager
    def connect(self) -> Iterator[Any]:
        if not self.config.enabled:
            raise CorticalLabsUnavailable('CL integration is disabled. Set CL_ENABLED=true after configuring the simulator or device.')
        cl=self._module()
        try:
            with cl.open() as neurons:
                yield neurons
        except Exception as exc:
            raise CorticalLabsUnavailable(f'CL connection or operation failed: {type(exc).__name__}: {exc}') from exc

    def status(self) -> dict[str, Any]:
        if not self.config.enabled:
            return {'enabled':False,'mode':self.config.mode,'connected':False,'message':'Integration disabled'}
        cl=self._module()
        try:
            is_sim=bool(cl.is_simulator()) if hasattr(cl,'is_simulator') else self.config.mode=='simulator'
            attrs=cl.get_system_attributes() if hasattr(cl,'get_system_attributes') else {}
            return {'enabled':True,'mode':'simulator' if is_sim else 'hardware','connected':True,'system':attrs}
        except Exception as exc:
            return {'enabled':True,'mode':self.config.mode,'connected':False,'error':type(exc).__name__}

    def record(self, duration_s: float, file_location: str | None = None) -> dict[str, Any]:
        if not 0 < duration_s <= 3600: raise ValueError('duration_s must be in (0, 3600]')
        import time
        with self.connect() as neurons:
            recording=neurons.record() if file_location is None else neurons.record(file_location=file_location)
            time.sleep(duration_s)
            result=recording.stop()
            return {'status':'stopped','duration_s':duration_s,'file_location':file_location,'result':str(result) if result is not None else None}

    def stimulate(self, channel: int, current_ua: float) -> dict[str, Any]:
        if not self.config.allow_stimulation:
            raise PermissionError('Stimulation is disabled. Enable CL_ALLOW_STIMULATION only after reviewing the device protocol and experiment safety plan.')
        if channel < 0: raise ValueError('channel must be a non-negative integer')
        if not 0 < abs(current_ua) <= self.config.max_current_ua:
            raise ValueError(f'current magnitude must be >0 and <= {self.config.max_current_ua} microamperes')
        with self.connect() as neurons:
            neurons.stim(channel, current_ua)
        return {'status':'submitted','channel':channel,'current_ua':current_ua}
