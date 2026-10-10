# Synthetic tissue model

The simulator is a research/education abstraction built around explicit membrane, synaptic, network, noise, and plasticity parameters. It supports reproducible spike-event generation and is suitable for benchmark development.

It does **not** reproduce living tissue, synaptic biochemistry, electrode physics, or CL1 hardware. Experimental parameters must be calibrated against measured data before making biological claims.

Layers: membrane dynamics → synaptic state → recurrent connectivity → external stimulation schedule → spike recording → benchmark/learning layer.
