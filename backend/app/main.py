from fastapi import FastAPI
from .services import health
from .routes import router
from .integrations import router as cl_router
from .tissue import router as tissue_router
from .learning import router as learning_router
from .ws import EVENTS
app=FastAPI(title='NeuroBlackwell API',version='0.4.0')
app.include_router(router)
app.include_router(cl_router)
app.include_router(tissue_router)
app.include_router(learning_router)
@app.get('/api/v1/health')
def api_health(): return health()
@app.get('/api/v1/equations')
def equations(): return {'items':['linear','polynomial','logistic','derivative','integral','Euler','RK4','Poisson','entropy','graph_laplacian']}
@app.post('/api/v1/mazes/generate')
def maze(width:int=10,height:int=10,seed:int=0):
 from neuroblackwell.environments.maze.generator import generate
 return generate(width,height,seed)
@app.get('/api/v1/ws-events')
def ws_events(): return {'events':EVENTS}
