from neuroblackwell.integrations.cortical_labs.tissue_simulator import SyntheticTissue,TissueParameters

def test_tissue_determinism():
 p=TissueParameters(neurons=12,dt_ms=1)
 a=SyntheticTissue(p,4).run(20)['spike_events']; b=SyntheticTissue(p,4).run(20)['spike_events']; assert a==b

def test_tissue_shape():
 r=SyntheticTissue(TissueParameters(neurons=8,dt_ms=1),1).run(10); assert r['neurons']==8
