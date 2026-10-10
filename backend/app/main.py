from fastapi import FastAPI
from .services import health

app=FastAPI(title="NeuroBlackwell API",version="0.1.0")

@app.get('/api/v1/health')
def api_health(): return health()

@app.get('/api/v1/equations')
def equations(): return {'items':['linear','polynomial','logistic','derivative','integral','Euler','RK4','Poisson','entropy','graph_laplacian']}

@app.post('/api/v1/mazes/generate')
def maze(width:int=10,height:int=10,seed:int=0):
    from neuroblackwell.environments.maze.generator import generate
    return generate(width,height,seed)
