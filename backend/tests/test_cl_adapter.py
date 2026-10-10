import pytest
from neuroblackwell.integrations.cortical_labs import CorticalLabsAdapter, CorticalLabsConfig

def test_disabled_status_is_safe():
 a=CorticalLabsAdapter(CorticalLabsConfig(mode='simulator',enabled=False))
 assert a.status()['connected'] is False

def test_stimulation_disabled_by_default():
 a=CorticalLabsAdapter(CorticalLabsConfig(mode='simulator',enabled=True,allow_stimulation=False))
 with pytest.raises(PermissionError): a.stimulate(1,1.0)

def test_current_limit_validation():
 a=CorticalLabsAdapter(CorticalLabsConfig(mode='simulator',enabled=True,allow_stimulation=True,max_current_ua=2.0))
 with pytest.raises(ValueError): a.stimulate(1,2.5)
