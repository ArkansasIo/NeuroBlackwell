# UML — Experiment Sequence

```mermaid
sequenceDiagram
  actor User
  participant UI as Frontend
  participant API as Python API
  participant Sim as Simulation module
  participant DB as MySQL
  User->>UI: Configure experiment
  UI->>API: Submit validated request
  API->>API: Validate schema and limits
  API->>DB: Create experiment record
  API-->>UI: experiment_id and accepted status
  API->>Sim: Run bounded simulation
  loop Progress updates
    Sim-->>API: Progress / status
    API-->>UI: WebSocket event
  end
  Sim-->>API: Synthetic results
  API->>DB: Persist result metadata
  API-->>UI: Completed status and result reference
  UI->>UI: Render labeled synthetic result
```

## Failure paths

- Invalid input: return a stable client error and do not start work.
- Work limit exceeded: terminate the job safely and record a bounded failure status.
- Simulation error: record a sanitized failure reason and mark the experiment failed.
- Persistence error: do not report durable completion; surface a retryable error if appropriate.
- Client disconnect: simulation state should remain server-owned if the job is designed to continue.
