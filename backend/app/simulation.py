import random

def run_simulation(req):
    rng=random.Random(req.seed)
    steps=max(1,int(req.duration_ms/req.dt_ms))
    spikes=[]
    for step in range(steps):
        for neuron in range(req.neurons):
            if rng.random()<0.001:
                spikes.append({'t_ms':round(step*req.dt_ms,6),'neuron':neuron})
    return {'status':'completed','neurons':req.neurons,'duration_ms':req.duration_ms,'dt_ms':req.dt_ms,'spikes':spikes,'spike_count':len(spikes)}
