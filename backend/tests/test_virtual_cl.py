from neuroblackwell.integrations.cortical_labs.virtual_hardware import VirtualHardware

def test_virtual_hardware_recording_and_stimulation():
 with VirtualHardware(channels=8,seed=7) as hw:
  assert hw.status()['mode']=='virtual'
  spikes=hw.record(1.0,rate_hz=10)
  assert all(0<=x['channel']<8 for x in spikes)
  event=hw.stimulate(2,1.0)
  assert event['channel']==2
