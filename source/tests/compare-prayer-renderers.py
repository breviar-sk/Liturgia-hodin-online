#!/usr/bin/env python3
"""Compare a saved CGI executable against a refactored one, without network access.

Run from any directory: compare-prayer-renderers.py BASELINE CANDIDATE.
Fixtures cover the marker grammar; this checks their composition in real prayers.
"""
from concurrent.futures import ThreadPoolExecutor
from difflib import unified_diff
import os
from pathlib import Path
import subprocess
import sys
from urllib.parse import urlencode

ROOT = Path(__file__).resolve().parents[2]
BASELINE, CANDIDATE = (str(Path(p).resolve()) for p in sys.argv[1:])


def compare(query):
    env = dict(os.environ, REQUEST_METHOD='GET', QUERY_STRING=query)
    outputs = [subprocess.check_output([binary], cwd=ROOT / 'source', env=env,
                                      timeout=30).decode('utf-8')
               for binary in (BASELINE, CANDIDATE)]
    if outputs[0] != outputs[1]:
        return query, ''.join(unified_diff(outputs[0].splitlines(True),
                                          outputs[1].splitlines(True)))[:6000]


queries = []
for language in ('sk', 'cz', 'czop', 'hu', 'la', 'is'):
    for day, month in ((5, 11), (5, 4), (25, 12)):
        for prayer in ('mi', 'mrch', 'mpc', 'mp', 'mna', 'mpo', 'mv', 'mk'):
            for options in ({}, {'o0': 0, 'o1': 0},
                            {'o0': 65535, 'o1': 127},
                            {'of0bf': 1, 'of0ff': 1, 'of0v': 1}):
                queries.append(urlencode(dict(qt='pdt', j=language, d=day,
                                              m=month, r=2026, p=prayer, **options)))
with ThreadPoolExecutor(max_workers=4) as pool:
    differences = [result for result in pool.map(compare, queries) if result]
for query, diff in differences[:8]:
    print(query, diff, sep='\n')
print(f'{len(queries)} prayers compared; {len(differences)} differences')
sys.exit(bool(differences))
