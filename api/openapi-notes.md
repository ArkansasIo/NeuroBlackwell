# API contract

Base path: `/api/v1`

- GET `/health`
- GET `/equations`
- POST `/mazes/generate`
- POST `/simulations/run` (planned)
- POST `/simulations/batch` (planned)
- GET `/experiments`
- GET `/experiments/{id}`
- GET `/datasets`

WebSocket events: `simulation.started`, `simulation.progress`, `spike`, `simulation.completed`, `simulation.error`.
