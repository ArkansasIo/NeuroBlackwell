const API=window.NEUROBLACKWELL_API||'http://localhost:8000';
fetch(API+'/api/v1/health').then(r=>r.json()).then(x=>document.querySelector('#app').textContent=`API: ${x.status} | Database configured: ${x.database_configured}`).catch(e=>document.querySelector('#app').textContent='API unavailable');
