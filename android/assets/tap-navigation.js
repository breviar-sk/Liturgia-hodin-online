/* Android reading gestures. Custom actions must declare data-breviar-interactive
 * or call BreviarTaps.claim(event) synchronously, before starting their action.
 * Claiming never cancels the browser's default behavior. */
(function () {
  'use strict';
  if (window.BreviarTaps || window !== window.top) return;
  var config = {enabled: false}, gesture = null, pending = null, sequence = 0;
  var settingsJson = null;
  var claimed = new WeakSet(), lastTouch = -Infinity;
  var reserved = 'a[href],area[href],button,input,select,textarea,label,summary,' +
      'audio,video,iframe,object,embed,[contenteditable]:not([contenteditable="false"]),' +
      '[role="button"],[role="link"],[role="checkbox"],[role="switch"],[role="slider"],' +
      '[tabindex],[data-breviar-interactive],[onclick],[ondblclick],[ontouchstart],' +
      '[ontouchend],[onpointerdown],[onpointerup],[onmousedown],[onmouseup]';

  function selected() {
    var selection = window.getSelection();
    var active = document.activeElement;
    return !!(selection && !selection.isCollapsed) || !!(active &&
        (active.isContentEditable || /^(INPUT|TEXTAREA|SELECT)$/.test(active.tagName)));
  }
  function interactive(event) {
    // Follow ancestors too: a span/image inside a link belongs to the link.
    var path = event.composedPath ? event.composedPath() : [];
    if (!path.length) {
      for (var node = event.target; node; node = node.parentNode) path.push(node);
    }
    return path.some(function (node) {
      return node.nodeType === 1 && (node.matches(reserved) ||
          typeof node.onclick === 'function' || typeof node.ondblclick === 'function');
    });
  }
  function clearPending() {
    if (pending) clearTimeout(pending.timer);
    pending = null;
  }
  function cancel() {
    clearPending();
    gesture = null;
  }
  function usable() { return config.enabled && !document.hidden && !selected(); }
  function distance(a, b) {
    var x = a.x - b.x, y = a.y - b.y;
    return x * x + y * y;
  }
  function point(event, end) {
    var touch = event.changedTouches && event.changedTouches[0];
    return {x: touch ? touch.clientX : event.clientX, y: touch ? touch.clientY : event.clientY};
  }
  function third(p) {
    var viewport = window.visualViewport;
    var offset = viewport ? (config.horizontal ? viewport.offsetLeft : viewport.offsetTop) : 0;
    var size = viewport ? (config.horizontal ? viewport.width : viewport.height) :
        (config.horizontal ? window.innerWidth : window.innerHeight);
    var position = (config.horizontal ? p.x : p.y) - offset;
    return position < size / 3 ? -1 : position >= 2 * size / 3 ? 1 : 0;
  }
  function start(event) {
    if (!event.isTrusted || !config.enabled) return;
    var p = point(event);
    var previous = pending;
    clearPending();
    gesture = {
      id: ++sequence, token: config.token, start: p, end: p, startEvent: event,
      startTime: performance.now(), ended: false, clicked: false,
      blocked: !usable() || interactive(event) || (event.touches && event.touches.length !== 1),
      previous: previous && third(p) === 0 &&
          performance.now() - previous.upTime <= config.doubleTapTimeout &&
          distance(previous.end, p) <= config.doubleTapSlop * config.doubleTapSlop ? previous : null
    };
    window.tapNavigation.begin(config.token, gesture.id);
  }
  function move(event) {
    if (!gesture) return;
    if ((event.touches && event.touches.length !== 1) ||
        distance(gesture.start, point(event)) > config.touchSlop * config.touchSlop) cancel();
  }
  function end(event) {
    if (!gesture) return;
    gesture.end = point(event, true);
    gesture.endEvent = event;
    gesture.upTime = performance.now();
    gesture.ended = true;
    if ((event.touches && event.touches.length) ||
        gesture.upTime - gesture.startTime >= config.longPressTimeout ||
        distance(gesture.start, gesture.end) > config.touchSlop * config.touchSlop) cancel();
  }
  function send(g, action) {
    if (gesture !== g || g.token !== config.token || !usable()) return;
    gesture = null;
    window.tapNavigation.perform(g.token, g.id, action);
  }
  function finishClick(g, event) {
    if (gesture !== g || g.blocked || !g.bubbled || event.defaultPrevented ||
        claimed.has(event) || claimed.has(g.startEvent) || claimed.has(g.endEvent) || !usable()) return;
    var region = third(g.end);
    if (region !== 0) {
      // Outer thirds never wait for or participate in double-tap fullscreen.
      send(g, region < 0 ? 'up' : 'down');
      return;
    }
    if (!config.fullscreen || third(g.start) !== 0) return;
    if (g.previous) {
      // Both unused taps must start and end in the middle third.
      send(g, 'fullscreen');
      return;
    }
    pending = g;
    g.timer = setTimeout(function () {
      if (pending === g) pending = null;
    }, Math.max(0, config.doubleTapTimeout - (performance.now() - g.upTime)));
  }
  window.addEventListener('click', function (event) {
    var g = gesture;
    // Keyboard, accessibility and programmatic activation have no physical tap.
    if (!event.isTrusted || !g || !g.ended || g.clicked ||
        performance.now() - g.upTime > 1000 ||
        distance(g.end, point(event)) > config.touchSlop * config.touchSlop) return;
    g.clicked = true;
    g.clickEvent = event;
    g.blocked = g.blocked || interactive(event);
    // Wait for target/delegated handlers. A stopped event receives no unused result.
    setTimeout(function () { finishClick(g, event); }, 0);
  }, true);
  window.addEventListener('click', function (event) {
    if (gesture && gesture.clickEvent === event) gesture.bubbled = true;
  });
  window.addEventListener('touchstart', function (e) { lastTouch = performance.now(); start(e); }, {capture: true, passive: true});
  window.addEventListener('touchmove', move, {capture: true, passive: true});
  window.addEventListener('touchend', function (e) { lastTouch = performance.now(); end(e); }, {capture: true, passive: true});
  window.addEventListener('touchcancel', cancel, true);
  // Ignore compatibility mouse events following a touch; clicks still classify it.
  window.addEventListener('mousedown', function (e) {
    if (e.button === 0 && performance.now() - lastTouch > 1000) start(e);
  }, true);
  window.addEventListener('mousemove', function (e) {
    if (performance.now() - lastTouch > 1000 && e.buttons) move(e);
  }, true);
  window.addEventListener('mouseup', function (e) {
    if (e.button === 0 && performance.now() - lastTouch > 1000) end(e);
  }, true);
  window.addEventListener('scroll', cancel, true);
  window.addEventListener('resize', cancel);
  window.addEventListener('contextmenu', cancel, true);
  window.addEventListener('pagehide', cancel);
  window.addEventListener('blur', cancel);
  document.addEventListener('visibilitychange', cancel);
  document.addEventListener('selectionchange', function () { if (selected()) cancel(); });
  window.BreviarTaps = {
    claim: function (event) { claimed.add(event); },
    configure: function () {
      if (!window.tapNavigation) return;
      var latest = window.tapNavigation.settings();
      // Retries and late page-finished callbacks must acknowledge the current
      // session without discarding a valid first tap of a double tap.
      if (latest !== settingsJson) {
        var next = JSON.parse(latest);
        cancel();
        config = next;
        settingsJson = latest;
      }
      window.tapNavigation.ready(config.token);
    }
  };
  if (window.tapNavigation) {
    window.BreviarTaps.configure();
  }
})();
