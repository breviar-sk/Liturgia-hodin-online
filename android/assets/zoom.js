var contentRoot = document.getElementById('contentRoot');

function getCookie(cname, default_value) {
    var name = cname + "=";
    var ca = document.cookie.split(';');
    for(var i=0; i<ca.length; i++) {
        var c = ca[i];
        while (c.charAt(0)==' ') c = c.substring(1);
        if (c.indexOf(name) == 0) return c.substring(name.length,c.length);
    }
    return default_value;
}

function syncScale() {
  if (contentRoot) contentRoot.style['font-size'] = getCookie('zoom', '100') + '%';
}

syncScale();

// Called after page load. Fonts can finish later and change the prayer height;
// notify Android only after applying zoom and completing font layout.
function prepareScrollRestore(request, zoom) {
  document.cookie = 'zoom=' + zoom;
  syncScale();
  document.documentElement.getBoundingClientRect(); // Discover fonts needed by the new layout.
  function ready() { bridge.scrollReady(request); }
  if (document.fonts && document.fonts.ready) {
    document.fonts.ready.then(ready, ready);
  } else {
    ready(); // Older WebViews still wait for Android's visual-state callback.
  }
}
