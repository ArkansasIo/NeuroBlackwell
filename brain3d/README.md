# NeuroBlackwell 3D Brain

A research visualization layer for the Synthetic Human Brain Program. Geometry and connectivity are explicitly separated from biological claims.

## Run the viewer

Serve the repository over HTTP (browser security blocks some local `fetch()` calls when opening an HTML file directly):

```bash
python -m http.server 8000
```

Open `http://localhost:8000/brain3d/web/`. The viewer starts with deterministic browser-generated synthetic geometry if no generated scene file is present. Use **Load scene JSON** to inspect a native snapshot or another compatible scene.

## Export a scene from the native C++ simulator

Build and run from the repository root:

```bash
cmake -S native -B native/build -DCMAKE_BUILD_TYPE=Release
cmake --build native/build --parallel
./native/build/shb_export_scene brain3d/data/native_snapshot.json
```

On Windows, run `native\\build\\Release\\shb_export_scene.exe brain3d/data/native_snapshot.json` when using a multi-configuration generator. Then use **Load scene JSON** in the viewer and select that output file.

The exporter records neuron IDs, region IDs, type, coordinates, membrane voltage, spike flags, synapse endpoints, weights, delays, simulation time, and provenance. The snapshot is a point-in-time export; it is not a live streaming bridge. The viewer's **Visual pulse** is explicitly browser-only and does not stimulate the native engine.

## Scene data contract

The JSON scene contract is documented in `schema/brain_scene.schema.json`. A scene has `version`, `coordinate_system`, `regions`, `neurons`, and `connections`. Neurons may include `region_id`, `type`, `x/y/z`, `membrane_mv`, and `spiked`; connections include `source`, `target`, `weight`, and optional `delay_ms`.

## Scientific scope

The default demo uses synthetic geometry and synthetic neurons. It is not a human MRI reconstruction, connectome, validated biological model, or clinical tool. External MRI, atlas, morphology, and connectomics data must retain source and license provenance.

## Data workbook

Run `python tools/generate_neuron_workbook.py` after installing `openpyxl` to generate `brain3d/data/NeuroBlackwell_Neuron_Data.xlsx` with neuron, synapse, region, and provenance worksheets.
