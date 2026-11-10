#!/usr/bin/env python3
"""Check generated Vatican URLs against a checked-in index snapshot.

Pass --online to also check every generated fragment against the actual pages.
An optional --cache DIRECTORY avoids downloading a book more than once.
"""
import argparse
from html.parser import HTMLParser
from pathlib import Path
import subprocess
from urllib.parse import unquote, urlsplit
from urllib.request import urlopen


class Anchors(HTMLParser):
    def __init__(self):
        super().__init__()
        self.names = set()

    def handle_starttag(self, tag, attrs):
        for key, value in attrs:
            if key == 'id' or (tag == 'a' and key == 'name'):
                self.names.add(value)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('binary', type=Path)
    parser.add_argument('--online', action='store_true')
    parser.add_argument('--cache', type=Path)
    args = parser.parse_args()
    snapshot = {}
    for line in Path(__file__).with_name('fixtures').joinpath('vatican-books.tsv').read_text().splitlines():
        if not line or line.startswith('#'):
            continue
        code, filename, chapters = line.split('\t')
        snapshot[code] = (filename, int(chapters))
    pages = {}
    count = 0
    output = subprocess.check_output([str(args.binary.resolve()), '--vatican-links'], text=True)
    seen = set()
    for line in output.splitlines():
        code, chapter, url = line.split('\t')
        chapter = int(chapter)
        filename, chapters = snapshot[code]
        parsed = urlsplit(url)
        assert parsed.scheme == 'https' and parsed.netloc == 'www.vatican.va', url
        assert parsed.path == '/archive/bible/nova_vulgata/documents/' + filename, url
        fragment = unquote(parsed.fragment)
        expected = '' if chapters == 1 or chapter > chapters else str(chapter)
        if code == 'PSA':
            expected = 'PSALMUS ' + str(chapter)
        assert fragment == expected, (url, expected)
        if args.online:
            if filename not in pages:
                cache_file = args.cache / filename if args.cache else None
                if cache_file and cache_file.exists():
                    data = cache_file.read_bytes()
                else:
                    with urlopen(url.split('#')[0], timeout=30) as response:
                        data = response.read()
                    if cache_file:
                        cache_file.parent.mkdir(parents=True, exist_ok=True)
                        cache_file.write_bytes(data)
                anchors = Anchors()
                anchors.feed(data.decode('utf-8', errors='replace'))
                pages[filename] = anchors.names
            assert not fragment or fragment in pages[filename], url
        seen.add(code)
        count += 1
    assert seen == snapshot.keys(), 'Missing Vatican books'
    print(f'Checked {count} Vatican links in {len(seen)} books' + (' against HTML anchors' if args.online else ''))


if __name__ == '__main__':
    main()
