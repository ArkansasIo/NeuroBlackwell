"""Lightweight repository contract tests for documentation and manifests."""

import json
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]


def test_manifest_declares_project_and_scientific_limitations():
    manifest = json.loads((ROOT / "manifest.json").read_text(encoding="utf-8"))
    assert manifest["project"] == "Synthetic Human Brain Program"
    note = manifest["note"].lower()
    assert "synthetic" in note
    assert "biological measurements" in note


def test_repository_architecture_and_research_docs_exist():
    for relative in (
        "docs/ARCHITECTURE.md",
        "docs/RESEARCH_PROTOCOL.md",
        "docs/DEPLOYMENT.md",
        "docs/uml/COMPONENT_DIAGRAM.md",
        "docs/uml/SEQUENCE_DIAGRAM.md",
    ):
        path = ROOT / relative
        assert path.is_file(), f"Missing required documentation: {relative}"
        assert path.stat().st_size > 100


def test_readme_links_repository_layout_and_learning_docs():
    readme = (ROOT / "README.md").read_text(encoding="utf-8")
    assert "docs/REPOSITORY_LAYOUT.md" in readme
    assert "learning/README.md" in readme
