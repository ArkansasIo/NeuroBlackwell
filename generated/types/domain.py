"""Shared typed structures for generated math and neural experiments."""
from dataclasses import dataclass, field
from typing import Any

@dataclass
class FormulaSpec:
    formula_id: str
    expression: str
    domain: str
    variables: dict[str, str] = field(default_factory=dict)
    assumptions: list[str] = field(default_factory=list)
    provenance: str | None = None

@dataclass
class ModuleResult:
    module: str
    success: bool
    values: dict[str, Any] = field(default_factory=dict)
    warnings: list[str] = field(default_factory=list)
