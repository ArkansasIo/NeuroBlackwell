# Human Brain Neurons and Tissue: Research Brief

**Prepared:** 2026-10-10. This is a research summary, not a complete human-brain model.

## Findings

1. Human brain cell identity spans molecular signatures, anatomy, location, connectivity, and physiological function. The NIH BRAIN Initiative Cell Atlas Network is developing reference atlases with an emphasis on human brain cells and their organization.
2. Neurons operate in circuits. A 2024 *Nature Neuroscience* study modeled co-dependent excitatory and inhibitory plasticity, suggesting inhibitory plasticity can gate excitatory plasticity and neighboring excitatory interactions influence long-term potentiation.
3. Synapses are molecularly diverse; a single scalar synaptic weight is a useful computational simplification, not a full biological description.
4. Astrocytes, microglia, oligodendrocytes, and vascular cells are important context. A neuron-only simulation should explicitly document these omissions.
5. Brain datasets combine different modalities, including single-cell RNA sequencing, spatial transcriptomics, electrophysiology, imaging, and anatomical metadata. Units, sampling biases, and provenance must be preserved.

## Suggested NeuroBlackwell model layers

- Single-cell dynamics: membrane voltage, threshold, reset, refractory interval, input current, spikes.
- Synapses: excitatory/inhibitory sign, delays, conductance/current, decay, plasticity state.
- Plasticity: documented STDP baseline; optional co-dependent excitatory/inhibitory model.
- Network topology: cell classes, connection probabilities, recurrent loops, excitation/inhibition balance.
- Tissue context: optional astrocyte modulation, myelination/conduction delay, electrode observation models.
- Learning tasks: temporal classification, sensory encoding, maze navigation, reward-driven learning.
- Validation: compare output distributions against traceable published/open data; do not validate by visual plausibility alone.

## Recommended outputs

Firing rate (Hz), inter-spike intervals (ms), coefficient of variation, membrane voltage (mV), conductance (nS) or current (pA), excitation/inhibition counts, population correlations, plasticity weight changes, task performance, runtime, memory, seed, configuration, source, and uncertainty.

## Limitations

LIF is a reduced model; it does not reproduce all ion channels, dendrites, gene expression, glial interactions, or human neuron diversity. Synthetic parameter values are software test values, not experimental human data. Do not infer cognition or consciousness from small benchmark success.

## Sources

- NIH BRAIN Initiative Cell Atlas Network: https://www.nih.gov/brain/research/tools-technologies-brain-cells-circuits/brain-initiative-cell-atlas-network
- NIH BRAIN Initiative Cell Census Network: https://www.nih.gov/brain/research/tools-technologies-brain-cells-circuits/brain-initiative-cell-census-network
- Agnes & Vogels, *Nature Neuroscience* (2024), co-dependent excitatory/inhibitory plasticity: https://www.nature.com/articles/s41593-024-01597-4
- van Oostrum & Schuman, *Nature Reviews Neuroscience* (2025), molecular diversity of synapses: https://www.nature.com/articles/s41583-024-00888-w
- Allen Human Brain Atlas: https://human.brain-map.org/
- Allen Institute for Brain Science: https://brain-map.org/

Check source terms and cite the original data when importing numerical parameters.