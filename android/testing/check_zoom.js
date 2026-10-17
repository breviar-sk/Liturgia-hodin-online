// Exercise the shipped zoom/font-readiness script with controlled font loading.
const assert = require('node:assert/strict');
const fs = require('node:fs');
const vm = require('node:vm');
const script = fs.readFileSync(require('node:path').join(__dirname, '../assets/zoom.js'), 'utf8');

function page(fonts, hasRoot = true) {
  const root = {style: {}};
  const calls = [];
  let layouts = 0;
  const document = {
    cookie: 'zoom=110', fonts,
    getElementById: () => hasRoot ? root : null,
    documentElement: {getBoundingClientRect() { ++layouts; }}
  };
  const context = vm.createContext({document, bridge: {scrollReady: id => calls.push(id)}});
  vm.runInContext(script, context);
  return {root, calls, context, document, layouts: () => layouts};
}

async function run() {
  let complete;
  const fonts = {ready: new Promise(resolve => { complete = resolve; })};
  const slow = page(fonts);
  assert.equal(slow.root.style['font-size'], '110%');
  slow.context.prepareScrollRestore(7, 135);
  assert.equal(slow.root.style['font-size'], '135%');
  assert.equal(slow.document.cookie, 'zoom=135');
  assert.equal(slow.layouts(), 1);
  await new Promise(resolve => setImmediate(resolve));
  assert.deepEqual(slow.calls, [], 'Must wait for fonts, not just for the script to return');
  complete();
  await Promise.resolve();
  assert.deepEqual(slow.calls, [7]);

  const cached = page({ready: Promise.resolve()});
  cached.context.prepareScrollRestore(8, 100);
  await Promise.resolve();
  assert.deepEqual(cached.calls, [8], 'Already loaded fonts need no timer or animation frame');

  for (const fonts of [undefined, {}]) {
    const legacy = page(fonts);
    legacy.context.prepareScrollRestore(9, 150);
    assert.deepEqual(legacy.calls, [9], 'Missing font API falls back to native visual readiness');
  }

  const failed = page({ready: Promise.reject(new Error('font unavailable'))});
  failed.context.prepareScrollRestore(10, 90);
  await Promise.resolve();
  assert.deepEqual(failed.calls, [10], 'An unusual rejected font promise must not lose the restore');

  const empty = page(undefined, false);
  empty.context.prepareScrollRestore(11, 100);
  assert.deepEqual(empty.calls, [11]);
  console.log('PASS: zoom, delayed/cached/failed fonts, missing font API and missing content root');
}

run().catch(error => { console.error(error); process.exitCode = 1; });
