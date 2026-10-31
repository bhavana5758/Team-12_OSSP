(() => {
  const $ = s => document.querySelector(s);
  const $$ = s => [...document.querySelectorAll(s)];
  const pSel = $('#p-count'), rSel = $('#r-count');
  let lastState = null, lastDeadlocked = [];
  const int = v => Math.max(0, Math.floor(Number(v) || 0));
  function makeMatrix(el, rows, cols, prefix, values) {
    if (!el) return;
    let html = '<table class="matrix"><thead><tr><th></th>' + Array.from({length:cols},(_,j)=>`<th>R${j}</th>`).join('') + '</tr></thead><tbody>';
    for(let i=0;i<rows;i++){
      html += `<tr><th>P${i}</th>` + Array.from({length:cols},(_,j)=>`<td><input type="number" min="0" step="1" value="${values?.[i]?.[j] ?? 0}" aria-label="${prefix} P${i} R${j}" data-matrix="${prefix}" data-row="${i}" data-col="${j}"></td>`).join('') + '</tr>';
    }
    el.innerHTML = html + '</tbody></table>';
  }
  function getMatrix(prefix, rows, cols) {
    return Array.from({length:rows},(_,i)=>Array.from({length:cols},(_,j)=>int($(`[data-matrix="${prefix}"][data-row="${i}"][data-col="${j}"]`)?.value)));
  }
  function getAvailable(cols) {
    return Array.from({length:cols},(_,j)=>int($(`[data-avail="${j}"]`)?.value));
  }
  function drawAvailable(cols, values) {
    const el=$('#available-fields'); if(!el) return;
    el.innerHTML=Array.from({length:cols},(_,j)=>`<input style="min-width:0;width:55px" type="number" min="0" step="1" value="${values?.[j]??0}" aria-label="Available R${j}" data-avail="${j}">`).join('');
  }
  function dims(){return {p:int(pSel?.value||4),r:int(rSel?.value||3)}}
  function renderInputs(a,q,v){const {p,r}=dims();drawAvailable(r,v);makeMatrix($('#allocation-matrix'),p,r,'alloc',a);makeMatrix($('#request-matrix'),p,r,'req',q);lastState=null;lastDeadlocked=[];const result=$('#sim-result');if(result)result.innerHTML='<h3>Ready to analyze</h3><p class="muted">Run detection to see the completion sequence and blocked processes.</p>';const target=$('#recovery-target');if(target)target.innerHTML='<option value="">Run detection first</option>';}
  function example(){if(!pSel||!rSel)return;pSel.value='4';rSel.value='3';renderInputs([[1,0,0],[0,1,0],[0,0,1],[0,0,0]],[[0,1,0],[0,0,1],[1,0,0],[0,0,0]],[0,0,0]);}
  function blank(){if(!pSel||!rSel)return;const {p,r}=dims();renderInputs(Array.from({length:p},()=>Array(r).fill(0)),Array.from({length:p},()=>Array(r).fill(0)),Array(r).fill(0));}
  function detect(){
    if(!pSel)return;
    const {p,r}=dims(), allocation=getMatrix('alloc',p,r), request=getMatrix('req',p,r), available=getAvailable(r);
    let work=[...available], finish=allocation.map(row=>row.every(x=>x===0)), sequence=[], progress=true;
    while(progress){progress=false;for(let i=0;i<p;i++){if(finish[i])continue;if(request[i].every((x,j)=>x<=work[j])){work=work.map((x,j)=>x+allocation[i][j]);finish[i]=true;sequence.push(i);progress=true;}}}
    const deadlocked=finish.map((f,i)=>f?null:i).filter(i=>i!==null);
    lastState={p,r,allocation,request,available,work,finish,sequence};lastDeadlocked=deadlocked;
    const result=$('#sim-result');
    result.className='result '+(deadlocked.length?'bad':'good');
    result.innerHTML=`<h3>${deadlocked.length?'⚠ Deadlock candidates detected':'✓ No deadlock detected'}</h3>
      <p>${deadlocked.length?`Processes remaining unfinished: ${deadlocked.map(i=>`P${i}`).join(', ')}.`:'All processes can finish under the supplied resource state.'}</p>
      <p><strong>Completion sequence:</strong> ${sequence.length?sequence.map(i=>`P${i}`).join(' → '):'None'}</p>
      <p><strong>Work remaining:</strong> [${work.join(', ')}]</p>
      <p><strong>Available initially:</strong> [${available.join(', ')}]</p>
      <div>${deadlocked.length?deadlocked.map(i=>`<span class="pill red">P${i} unfinished</span>`).join(''):'<span class="pill green">System can complete</span>'}</div>
      <p class="small">Note: processes with zero allocation are treated as finishable initially, as specified by the classic detection method.</p>`;
    const target=$('#recovery-target');
    if(target){target.innerHTML=deadlocked.length?deadlocked.map(i=>`<option value="${i}">P${i}</option>`).join(''):'<option value="">No deadlocked process</option>';}
  }
  function recover(){
    if(!lastState||!lastDeadlocked.length){alert('Run detection first and ensure at least one process is reported unfinished.');return;}
    const target=$('#recovery-target'), idx=Number(target?.value);
    if(!Number.isInteger(idx)||!lastDeadlocked.includes(idx)){alert('Select a process from the detected deadlocked set.');return;}
    const {p,r,allocation,request,available}=lastState;
    const newAlloc=allocation.map(row=>[...row]), newReq=request.map(row=>[...row]), newAvail=[...available];
    for(let j=0;j<r;j++){newAvail[j]+=newAlloc[idx][j];newAlloc[idx][j]=0;newReq[idx][j]=0;}
    renderInputs(newAlloc,newReq,newAvail);
    const result=$('#sim-result');
    result.className='result good';
    result.innerHTML=`<h3>Recovery applied: P${idx} terminated</h3><p>Its allocated resources were returned to the available vector. Run detection again to verify whether the remaining processes can finish.</p><p><strong>Updated available vector:</strong> [${newAvail.join(', ')}]</p><button class="btn primary" id="rerun-after-recovery">Run detection again →</button>`;
    $('#rerun-after-recovery')?.addEventListener('click',detect);
  }
  if(pSel&&rSel){pSel.addEventListener('change',blank);rSel.addEventListener('change',blank);$('#load-example')?.addEventListener('click',example);$('#reset-sim')?.addEventListener('click',blank);$('#run-detection')?.addEventListener('click',detect);$('#recover-process')?.addEventListener('click',recover);example();}
  $('#toggle-graph-labels')?.addEventListener('click',()=>{const e=$('#edge-labels');if(e)e.style.display=e.style.display==='none'?'':'none';});
  $('#feedback-form')?.addEventListener('submit',e=>{e.preventDefault();$('#feedback-status').textContent='Thanks — feedback validated locally. No data was sent to a server.';e.target.reset();});
})();
