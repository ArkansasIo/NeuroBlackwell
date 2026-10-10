const BASE=window.NEUROBLACKWELL_API||'http://localhost:8000';
export async function getHealth(){return (await fetch(BASE+'/api/v1/health')).json()}
export async function runSimulation(body){return (await fetch(BASE+'/api/v1/simulations/run',{method:'POST',headers:{'content-type':'application/json'},body:JSON.stringify(body)})).json()}
export async function evaluateMath(body){return (await fetch(BASE+'/api/v1/math/evaluate',{method:'POST',headers:{'content-type':'application/json'},body:JSON.stringify(body)})).json()}
export async function generateMaze(params){return (await fetch(BASE+'/api/v1/mazes/generate?'+new URLSearchParams(params),{method:'POST'})).json()}
