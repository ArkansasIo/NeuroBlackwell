(() => {
  "use strict";
  const canvas = document.getElementById("brain");
  const ctx = canvas.getContext("2d");
  const stats = document.getElementById("stats");
  const sceneInput = document.getElementById("sceneFile");
  const stimButton = document.getElementById("stim");
  const resetButton = document.getElementById("reset");
  const pauseButton = document.getElementById("pause");
  const regionFilter = document.getElementById("regionFilter");
  const sceneLabel = document.getElementById("sceneLabel");
  let scene = null;
  let rotation = 0;
  let animationFrame = 0;
  let paused = false;
  let localPulseUntil = 0;
  let selectedNeuron = null;
  const regionColors = ["#55c9ff", "#f3ad5b", "#be8cff", "#6de2b1", "#ff7896", "#d8e6f4"];

  function syntheticFallback() {
    const neurons = [];
    const connections = [];
    for (let i = 0; i < 260; i++) {
      const a = 2 * Math.PI * i / 260;
      const fold = 0.78 + 0.11 * Math.sin(7 * a) + 0.05 * Math.sin(13 * a);
      neurons.push({ id:i, region_id:1 + (i % 4), type:i % 8 === 0 ? "inhibitory" : "excitatory",
        x:0.82 * fold * Math.cos(a), y:0.68 * fold * Math.sin(a),
        z:0.22 * Math.sin(3 * a + i * 0.07), membrane_mv:-70, spiked:false });
    }
    for (let i = 0; i < neurons.length; i++) {
      for (const offset of [1, 7]) {
        const j = (i + offset) % neurons.length;
        connections.push({ source:i, target:j, weight:0.2 + ((i * 13 + j * 7) % 80) / 100, delay_ms:1 + offset / 2 });
      }
    }
    return { version:"1.0", dataset_id:"NB-BROWSER-FALLBACK", status:"synthetic_demo",
      coordinate_system:"normalized_brain_xyz", simulation_time_ms:0,
      regions:[1,2,3,4].map(id => ({id, name:"Synthetic region " + id})), neurons, connections,
      provenance:[{kind:"generated", description:"Browser-only synthetic fallback, not native simulation output."}] };
  }

  function normalizeScene(input) {
    if (!input || !Array.isArray(input.neurons) || !Array.isArray(input.connections)) {
      throw new Error("Scene must include neurons[] and connections[].");
    }
    const neurons = input.neurons.map((n, i) => ({
      id:Number(n.id ?? i), region_id:Number(n.region_id ?? 0), type:String(n.type ?? "excitatory"),
      x:Number(n.x ?? n.position?.x ?? n.position?.[0] ?? 0),
      y:Number(n.y ?? n.position?.y ?? n.position?.[1] ?? 0),
      z:Number(n.z ?? n.position?.z ?? n.position?.[2] ?? 0),
      membrane_mv:Number(n.membrane_mv ?? -70), spiked:Boolean(n.spiked)
    }));
    const ids = new Set(neurons.map(n => n.id));
    const connections = input.connections.filter(c => ids.has(Number(c.source)) && ids.has(Number(c.target)))
      .map(c => ({source:Number(c.source), target:Number(c.target), weight:Number(c.weight ?? 1), delay_ms:Number(c.delay_ms ?? 1)}));
    const regions = Array.isArray(input.regions) ? input.regions : [];
    return {...input, neurons, connections, regions};
  }

  function regionColor(id) {
    const index = Math.abs(Number(id) || 0) % regionColors.length;
    return regionColors[index];
  }

  function project(n, width, height) {
    const cos = Math.cos(rotation), sin = Math.sin(rotation);
    const x = n.x * cos - n.y * sin;
    const y = n.x * sin + n.y * cos;
    const depth = 1 / (1.65 + (n.z * 0.4));
    return { x:width * 0.5 + x * width * 0.37 * depth,
      y:height * 0.52 - y * height * 0.39 * depth - n.z * 25,
      depth };
  }

  function draw(now) {
    if (!canvas.isConnected) return;
    const width = canvas.width, height = canvas.height;
    ctx.clearRect(0, 0, width, height);
    const gradient = ctx.createRadialGradient(width/2, height/2, 30, width/2, height/2, height*0.75);
    gradient.addColorStop(0, "#17283a"); gradient.addColorStop(1, "#050912");
    ctx.fillStyle = gradient; ctx.fillRect(0,0,width,height);
    if (!scene) scene = syntheticFallback();

    const activeRegion = regionFilter.value;
    const visible = scene.neurons.filter(n => activeRegion === "all" || String(n.region_id) === activeRegion);
    const visibleIds = new Set(visible.map(n => n.id));
    const projected = new Map(visible.map(n => [n.id, project(n,width,height)]));
    const pulse = now < localPulseUntil;

    ctx.lineWidth = 0.8;
    for (const edge of scene.connections) {
      if (!visibleIds.has(edge.source) || !visibleIds.has(edge.target)) continue;
      const a = projected.get(edge.source), b = projected.get(edge.target);
      if (!a || !b) continue;
      const active = pulse && ((edge.source * 17 + edge.target * 3) % 11 < 3);
      ctx.strokeStyle = active ? "rgba(255,204,107,.8)" : "rgba(81,143,190,.15)";
      ctx.lineWidth = active ? 1.6 : Math.max(0.35, Math.min(1.0, Number(edge.weight) * 0.5));
      ctx.beginPath(); ctx.moveTo(a.x,a.y); ctx.lineTo(b.x,b.y); ctx.stroke();
    }
    for (const n of visible) {
      const p = projected.get(n.id);
      const active = Boolean(n.spiked) || (pulse && (n.id % 17 < 3));
      const radius = (selectedNeuron === n.id ? 5.5 : active ? 4 : 2.0) * (0.65 + p.depth * 0.45);
      ctx.beginPath(); ctx.arc(p.x,p.y,radius,0,Math.PI*2);
      ctx.fillStyle = active ? "#fff0a8" : n.type === "inhibitory" ? "#ff7896" : regionColor(n.region_id);
      ctx.shadowBlur = active ? 14 : 3;
      ctx.shadowColor = ctx.fillStyle; ctx.fill(); ctx.shadowBlur = 0;
      if (selectedNeuron === n.id) {
        ctx.strokeStyle = "#ffffff"; ctx.lineWidth = 1.5; ctx.stroke();
      }
    }
    ctx.fillStyle = "rgba(220,231,243,.75)";
    ctx.font = "12px system-ui";
    ctx.fillText("SYNTHETIC DATA · rotate view · select a neuron", 18, 24);
    if (!paused) rotation += 0.0018;
    if (!paused) animationFrame = requestAnimationFrame(draw);
    updateStats(visible.length);
  }

  function updateStats(visibleCount) {
    if (!scene) return;
    const active = scene.neurons.filter(n => n.spiked).length;
    const selected = scene.neurons.find(n => n.id === selectedNeuron);
    const base = scene.dataset_id + " · " + visibleCount + "/" + scene.neurons.length +
      " neurons · " + scene.connections.length + " connections · " + active +
      " spike flags · " + Number(scene.simulation_time_ms ?? 0).toFixed(2) + " ms · " + scene.status;
    stats.textContent = selected
      ? base + " · selected neuron " + selected.id + " / region " + selected.region_id +
        " / " + selected.type + " / Vm " + selected.membrane_mv.toFixed(2) + " mV / degree " +
        scene.connections.filter(e => e.source === selected.id || e.target === selected.id).length
      : base;
    sceneLabel.textContent = scene.status === "synthetic_native_simulation"
      ? "Loaded native C++ simulation snapshot" : "Synthetic visualization data";
  }

  function renderOnce() {
    if (animationFrame) cancelAnimationFrame(animationFrame);
    animationFrame = requestAnimationFrame(draw);
  }

  async function loadDefault() {
    for (const path of ["../data/generated_demo_brain.json", "../data/demo_brain.json"]) {
      try {
        const response = await fetch(path);
        if (!response.ok) continue;
        const parsed = await response.json();
        if (Array.isArray(parsed.neurons) && parsed.neurons.length) {
          scene = normalizeScene(parsed); populateRegions(); renderOnce(); return;
        }
      } catch (_) { /* static-file fallback below */ }
    }
    scene = normalizeScene(syntheticFallback()); populateRegions(); renderOnce();
  }

  function populateRegions() {
    const previous = regionFilter.value;
    regionFilter.innerHTML = '<option value="all">All regions</option>';
    const regions = new Map();
    for (const n of scene.neurons) {
      if (!regions.has(String(n.region_id))) regions.set(String(n.region_id), null);
    }
    for (const r of scene.regions) regions.set(String(r.id), r.name);
    for (const [id, name] of regions) {
      const option = document.createElement("option");
      option.value = id; option.textContent = name || ("Region " + id); regionFilter.appendChild(option);
    }
    regionFilter.value = [...regionFilter.options].some(o => o.value === previous) ? previous : "all";
  }

  sceneInput.addEventListener("change", async event => {
    const file = event.target.files && event.target.files[0];
    if (!file) return;
    try {
      scene = normalizeScene(JSON.parse(await file.text()));
      populateRegions(); renderOnce();
    } catch (error) {
      stats.textContent = "Could not load scene: " + error.message;
    }
  });
  stimButton.addEventListener("click", () => {
    localPulseUntil = performance.now() + 1800;
    stats.textContent = "Browser visual pulse only — this button does not stimulate the native C++ engine.";
    renderOnce();
  });
  resetButton.addEventListener("click", () => {
    rotation = 0; selectedNeuron = null; localPulseUntil = 0; renderOnce();
  });
  pauseButton.addEventListener("click", () => {
    paused = !paused; pauseButton.textContent = paused ? "Resume rotation" : "Pause rotation";
    if (!paused) renderOnce();
  });
  regionFilter.addEventListener("change", renderOnce);
  canvas.addEventListener("click", event => {
    const rect = canvas.getBoundingClientRect();
    const x = (event.clientX - rect.left) * canvas.width / rect.width;
    const y = (event.clientY - rect.top) * canvas.height / rect.height;
    let nearest = null, nearestD = 15 * (canvas.width / rect.width);
    for (const n of scene.neurons) {
      const p = project(n,canvas.width,canvas.height);
      const d = Math.hypot(p.x-x,p.y-y);
      if (d < nearestD) { nearest = n; nearestD = d; }
    }
    selectedNeuron = nearest ? nearest.id : null;
    if (nearest) {
      const edgeCount = scene.connections.filter(e => e.source === nearest.id || e.target === nearest.id).length;
      stats.textContent = "Neuron " + nearest.id + " · region " + nearest.region_id + " · " +
        nearest.type + " · Vm " + nearest.membrane_mv.toFixed(2) + " mV · degree " + edgeCount;
    }
    renderOnce();
  });

  loadDefault();
})();