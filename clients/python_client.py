import requests

class NeuroBlackwellClient:
    def __init__(self,base_url='http://localhost:8000'): self.base_url=base_url.rstrip('/')
    def health(self): return requests.get(self.base_url+'/api/v1/health',timeout=10).json()
    def equations(self): return requests.get(self.base_url+'/api/v1/equations',timeout=10).json()
    def maze(self,width=10,height=10,seed=0): return requests.post(self.base_url+'/api/v1/mazes/generate',params={'width':width,'height':height,'seed':seed},timeout=10).json()
