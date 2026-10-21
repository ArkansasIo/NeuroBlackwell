# UML — Component Diagram

The Mermaid graph below is a readable component view. It is intentionally implementation-oriented and does not imply clinical or biological equivalence.

```mermaid
flowchart LR
  subgraph Clients
    Web[Web UI / 3D viewer]
    Exp[Experiment client]
    CLI[Command-line tools]
  end
  subgraph Service
    REST[REST API]
    WS[WebSocket events]
    Auth[Authentication and authorization - production requirement]
  end
  subgraph Engine
    Py[Python orchestration]
    Sim[Native C/C++ simulator]
    Math[Math and experiment modules]
    Bench[Learning benchmark]
  end
  subgraph Storage
    SQL[(MySQL)]
    Artifacts[JSON scene and reports]
  end
  Web --> REST
  Web <--> WS
  Exp --> REST
  CLI --> REST
  REST --> Auth
  REST --> Py
  WS --> Py
  Py --> Sim
  Py --> Math
  Py --> Bench
  Py --> SQL
  Sim --> Artifacts
  Artifacts --> Web
```

## Key interfaces

- REST: validated request/response payloads; version endpoints when compatibility changes.
- WebSocket: typed event names, experiment ID, sequence/timestamp, and an explicit terminal state.
- C ABI: stable data types, explicit ownership/lifetime rules, and error/status codes.
- Scene JSON: a schema version, synthetic status label, neuron and connection arrays, and required per-record fields.
- Persistence: repositories/services own SQL access; clients never access the database directly.
