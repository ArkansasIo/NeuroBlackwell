from dataclasses import dataclass, field
import math

@dataclass
class MemoryTrace:
    strength: float = 1.0
    successful_retrievals: int = 0
    last_seen_day: float = 0.0

@dataclass
class MemoryModel:
    base_tau_days: float = 2.0
    traces: dict = field(default_factory=dict)

    def retention(self, concept: str, now_day: float) -> float:
        trace = self.traces.get(concept)
        if trace is None:
            return 0.0
        tau = max(0.1, self.base_tau_days * trace.strength * (1.0 + 0.5 * trace.successful_retrievals))
        elapsed = max(0.0, now_day - trace.last_seen_day)
        return math.exp(-elapsed / tau)

    def retrieve(self, concept: str, now_day: float, correct: bool) -> float:
        before = self.retention(concept, now_day)
        trace = self.traces.setdefault(concept, MemoryTrace())
        if correct:
            trace.successful_retrievals += 1
            trace.strength = min(10.0, trace.strength + 0.5 * (1.0 - before))
        else:
            trace.strength = max(0.1, trace.strength * 0.85)
        trace.last_seen_day = now_day
        return before
