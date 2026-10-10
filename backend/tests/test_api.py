from fastapi.testclient import TestClient
from app.main import app
client=TestClient(app)
def test_health():
 r=client.get('/api/v1/health'); assert r.status_code==200; assert r.json()['status']=='ok'
def test_math():
 r=client.post('/api/v1/math/evaluate',json={'operation':'sum','values':[1,2,3]}); assert r.json()['value']==6
def test_simulation():
 r=client.post('/api/v1/simulations/run',json={'neurons':4,'duration_ms':10,'dt_ms':1,'seed':1}); assert r.status_code==200; assert r.json()['status']=='completed'
