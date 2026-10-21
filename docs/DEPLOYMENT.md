# Local Deployment and Operations

## Prerequisites

- Docker Engine and Docker Compose plugin for the container route.
- Python 3.12 for direct API/test workflows.
- CMake 3.20+ plus C17 and C++20 compilers for the native simulation module.

## Before starting containers

The tracked `docker-compose.yml` is a local-development example. It has default placeholder credentials. Do not reuse those values in a shared environment.

Export unique local values in the shell before launching. Update Compose to interpolate them from the environment (for example, `${MYSQL_PASSWORD:?Set MYSQL_PASSWORD}` and `${MYSQL_ROOT_PASSWORD:?Set MYSQL_ROOT_PASSWORD}`). Keep the local environment file untracked and restrict its filesystem permissions. Never put secrets in committed files or logs.

Recommended deployment adjustments:

- Avoid publishing port 3306 to the host unless database access from the host is required.
- Add MySQL health checks and use a healthy dependency condition for the API.
- Use a non-root API container user when practical.
- Pin image tags and review update notices regularly.
- Use TLS at the ingress and restrict inbound API access.
- Back up the database volume and test restoration.
- Apply authentication, authorization, rate limiting, audit logging, and migrations before production exposure.

## Native build

```sh
cmake -S native -B build/native -DCMAKE_BUILD_TYPE=Release
cmake --build build/native --parallel
ctest --test-dir build/native --output-on-failure
```

## Python tests

```sh
python -m pip install -r backend/requirements.txt
PYTHONPATH=backend:. pytest -q backend/tests
```

For the learning subsystem:

```sh
python -m pip install -r learning/requirements.txt
PYTHONPATH=. pytest -q learning/tests
python learning/tools/generate_curriculum_workbook.py
```

## Health and observability

Expose a lightweight health endpoint that checks process readiness without leaking credentials or configuration. Log request IDs, elapsed time and non-sensitive error context. Avoid logging authentication headers, personal data, API keys, or complete database URLs.
