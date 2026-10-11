# NeuroBlackwell 3D Brain

A research visualization layer for a virtual human-brain model. Geometry and connectivity are explicitly separated from biological claims.

## Scope
- Anatomical shell and cortical-fold representation.
- Virtual neurons with 3D coordinates.
- Synaptic edges and animated spike events.
- Import boundaries for MRI, atlas, morphology, and connectomics data.
- Provenance metadata for every external dataset.

The default demo uses synthetic geometry and synthetic neurons. It is not a human MRI reconstruction.

## Data workbook
Run `python tools/generate_neuron_workbook.py` after installing `openpyxl` to generate `brain3d/data/NeuroBlackwell_Neuron_Data.xlsx` with neuron, synapse, region, and provenance worksheets.
