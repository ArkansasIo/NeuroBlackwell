# Full-stack architecture

The Python API is the boundary between the frontend, experiment clients, simulation/math engines, and MySQL. WebSocket events provide live simulation progress. The frontend never accesses MySQL directly.

For production, replace example passwords, add authentication/authorization, TLS, migrations, validation, rate limiting, audit logging, and secret management.
