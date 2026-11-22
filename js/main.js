(function () {
  const LINKS = {
    A: ['eJOI19_xoranges', null], B: ['COCI17_hindeks', null], C: ['eJOI21_addk', null], D: ['BOI19_nautilus', null],
    E: ['JOI18_art', null], F: ['eJOI20_exam', 6983], G: ['BOI18_election', null], H: ['eJOI20_fountain', 6981],
    I: ['EGOI24_teamcoding', 9184], J: ['EGOI25_giftboxes', 13165]
  };
  const store = {
    get(k) { try { return localStorage.getItem(k); } catch (e) { return null; } },
    set(k, v) { try { localStorage.setItem(k, v); } catch (e) {} }
  };
  const probs = [...document.querySelectorAll('article.prob')];
  const plist = document.getElementById('plist');
  const grid = document.getElementById('grid');
  let nsub = 0;

  probs.forEach((p, idx) => {
    const L = p.id, name = p.dataset.name, src = p.dataset.src, tags = p.dataset.tags.split(','), pts = p.dataset.pts.split(',');
    nsub += pts.length;
    // header
    const head = document.createElement('header');
    head.className = 'phead';
    const [oj, qoj] = LINKS[L];
    head.innerHTML = `<div class="tile">${L}</div><div><h1>${name}</h1><div class="meta"><span>${src}</span>${tags.map(t => `<span class="tag">${t}</span>`).join('')}</div></div>`;
    const links = document.createElement('div');
    links.className = 'links';
    links.innerHTML = `<a href="https://oj.uz/problem/view/${oj}" target="_blank" rel="noopener">oj.uz</a>` +
      (qoj ? `<a href="https://qoj.ac/problem/${qoj}" target="_blank" rel="noopener">QOJ</a>` : '') +
      `<a href="https://vjudge.net/contest/867918#problem/${L}" target="_blank" rel="noopener">VJudge</a>` +
      `<button type="button" class="btn done-btn" aria-pressed="false">Отметить решённой</button>`;
    head.querySelector('div:last-child').appendChild(links);
    p.prepend(head);
    // prev / next
    const nav = document.createElement('nav');
    nav.className = 'pnav';
    const prev = probs[idx - 1], next = probs[idx + 1];
    nav.innerHTML = (prev ? `<a href="#${prev.id}">← ${prev.id}. ${prev.dataset.name}</a>` : '<a href="#overview">← Все задачи</a>') +
      (next ? `<a href="#${next.id}">${next.id}. ${next.dataset.name} →</a>` : '<a href="#overview">Все задачи →</a>');
    p.appendChild(nav);
    // rail item
    const li = document.createElement('li');
    li.innerHTML = `<a href="#${L}" data-l="${L}"><span class="lt">${L}</span><span class="nm">${name}<small>${src}</small></span><span class="done" hidden></span></a>`;
    li.dataset.search = (L + ' ' + name + ' ' + src + ' ' + tags.join(' ')).toLowerCase();
    plist.appendChild(li);
    // card
    const c = document.createElement('a');
    c.className = 'card';
    c.href = '#' + L;
    const bar = pts.map(x => `<i class="${x.endsWith('*') ? 'full' : ''}" style="flex:${parseInt(x) || 50}"></i>`).join('');
    c.innerHTML = `<div class="top"><span class="L">${L}</span><span class="tag">${pts.length} ${pts.length === 1 ? 'уровень' : pts.length < 5 ? 'подзадачи' : 'подзадач'}</span></div>` +
      `<div><h3>${name}</h3><div class="src">${src}</div></div><div class="bar" title="Баллы подзадач">${bar}</div>` +
      `<div class="tags">${tags.map(t => `<span class="tag">${t}</span>`).join('')}</div>`;
    grid.appendChild(c);
  });
  document.getElementById('nsub').textContent = nsub;

  // solved marks
  function refreshDone() {
    let n = 0;
    probs.forEach(p => {
      const on = store.get('done-' + p.id) === '1';
      if (on) n++;
      p.querySelector('.done-btn').setAttribute('aria-pressed', on);
      p.querySelector('.done-btn').textContent = on ? 'Решено ✓' : 'Отметить решённой';
      plist.querySelector(`[data-l="${p.id}"] .done`).hidden = !on;
    });
    document.getElementById('ndone').textContent = n;
  }
  probs.forEach(p => p.querySelector('.done-btn').addEventListener('click', () => {
    store.set('done-' + p.id, store.get('done-' + p.id) === '1' ? '0' : '1');
    refreshDone();
  }));
  refreshDone();

  // copy buttons + highlight
  document.querySelectorAll('.codebox').forEach(box => {
    const code = box.querySelector('code');
    if (window.hljs) { try { hljs.highlightElement(code); } catch (e) {} }
    const btn = box.querySelector('button');
    btn.addEventListener('click', async () => {
      try { await navigator.clipboard.writeText(code.innerText); btn.textContent = 'Скопировано'; }
      catch (e) { const r = document.createRange(); r.selectNodeContents(code); const s = getSelection(); s.removeAllRanges(); s.addRange(r); btn.textContent = 'Выделено — Ctrl+C'; }
      setTimeout(() => { btn.textContent = 'Копировать'; }, 1800);
    });
  });

  // routing
  const overview = document.getElementById('overview');
  function route() {
    const h = location.hash.slice(1);
    const target = probs.find(p => p.id === h);
    overview.hidden = !!target;
    probs.forEach(p => { p.hidden = p !== target; });
    plist.querySelectorAll('a').forEach(a => a.toggleAttribute('aria-current', !!target && a.dataset.l === h));
    plist.querySelectorAll('a').forEach(a => { if (target && a.dataset.l === h) a.setAttribute('aria-current', 'page'); });
    window.scrollTo(0, 0);
  }
  window.addEventListener('hashchange', route);
  route();

  // search
  document.getElementById('q').addEventListener('input', e => {
    const v = e.target.value.trim().toLowerCase();
    plist.querySelectorAll('li').forEach(li => { li.hidden = v && !li.dataset.search.includes(v); });
  });

  // theme
  const root = document.documentElement;
  const tbtn = document.querySelectorAll('.theme button');
  function setTheme(t) {
    if (t === 'system') root.removeAttribute('data-theme'); else root.setAttribute('data-theme', t);
    tbtn.forEach(b => b.setAttribute('aria-pressed', b.dataset.t === t));
    store.set('theme', t);
  }
  tbtn.forEach(b => b.addEventListener('click', () => setTheme(b.dataset.t)));
  setTheme(store.get('theme') || 'system');
})();
