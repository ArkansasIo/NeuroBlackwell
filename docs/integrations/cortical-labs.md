# Cortical Labs integration

## Official interface

NeuroBlackwell integrates through the official Python `cl` module. Install `cl-sdk` for local development and simulation (`pip install cl-sdk`). The SDK is a simulator; it does not provide access to biological hardware by itself. Physical CL1 access requires a configured device and the vendor-provided runtime. Reference: https://docs.corticallabs.com/ and https://github.com/Cortical-Labs/cl-sdk.

## Configuration

Copy `.env.example` and configure `CL_MODE=simulator`, `CL_ENABLED=true` to test the API simulator. Default `CL_ENABLED=false` keeps the adapter inert. For a device, set `CL_MODE=hardware` only in the CL1 environment. Hardware mode requires `CL_ENABLED=true`.

Stimulation is separately disabled by default. `CL_ALLOW_STIMULATION=true` is an explicit opt-in; use only under the device's official documentation, approved protocol, and trained supervision. Adapter applies a conservative 3 µA upper bound but this is not a complete safety validation and does not replace device-side limits or experimental review.

## Endpoints

- `GET /api/v1/integrations/cortical-labs/status`
- `POST /api/v1/integrations/cortical-labs/record` with `{ "duration_s": 5, "file_location": "./recording.h5" }`
- `POST /api/v1/integrations/cortical-labs/stimulate` with `{ "channel": 1, "current_ua": 1.0 }` (403 unless stimulation is enabled)

## Scope and limitations

This adapter is an integration layer, not a neural-learning algorithm. The CL SDK simulator produces synthetic/replayed data and is not a substitute for biological experiments. Validate API details against the current vendor docs for the installed SDK version before hardware use.
