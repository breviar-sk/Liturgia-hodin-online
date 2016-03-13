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
  contentRoot.style['font-size'] = getCookie('zoom', '100') + '%';
}

syncScale();
