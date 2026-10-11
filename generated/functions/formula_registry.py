"""Minimal registry for formulas, functions, and their provenance."""
from dataclasses import asdict
from generated.types.domain import FormulaSpec

_REGISTRY: dict[str, FormulaSpec] = {}

def register(spec: FormulaSpec) -> None:
    if not spec.formula_id or not spec.expression.strip():
        raise ValueError("formula_id and expression are required")
    _REGISTRY[spec.formula_id] = spec

def get(formula_id: str) -> FormulaSpec:
    return _REGISTRY[formula_id]

def list_formulas() -> list[dict]:
    return [asdict(_REGISTRY[key]) for key in sorted(_REGISTRY)]
