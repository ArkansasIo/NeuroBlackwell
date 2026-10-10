import {getHealth} from './api.js';
export async function mountDashboard(el){try{const h=await getHealth();el.textContent=`NeuroBlackwell API: ${h.status} | Database configured: ${h.database_configured}`}catch(e){el.textContent='API unavailable'}}
