#!/usr/bin/env python3
"""Parse every rendered Latin {r} reference; council documents are not Bible books."""
from pathlib import Path
import re
import subprocess
import sys

ROOT = Path(__file__).resolve().parents[2]
BINARY = Path(sys.argv[1]).resolve()
COUNCIL = re.compile(r'^(?:LG|DH|GS|PO|AdG|SC|DV|ChD|PC)\s*\d')
references = []
for path in sorted((ROOT / 'include_la').glob('*.htm')):
    source = path.read_text(encoding='utf-8')
    if path.name.startswith('kat-') or not ('{BEGIN:' in source or path.name.startswith('m_')):
        continue
    for match in re.finditer(r'\{r(?::([^}]*))?\}([^{}]*)\{/r\}', source):
        text = ((match[1] or '') + ' ' + match[2]).strip().replace('\n', ' ')
        line = source.count('\n', 0, match.start()) + 1
        references.append((text, f'{path.relative_to(ROOT)}:{line}'))
assert references, 'No rendered Latin references found'
output = subprocess.check_output([str(BINARY), '--parse', 'la'], text=True,
                                 input=''.join(text + '\n' for text, _ in references))
results = output.splitlines()
assert len(results) == len(references), 'Parser dropped a reference'
failures = []
for (text, location), result in zip(references, results):
    book, complete, chapter = result.split('\t')
    if COUNCIL.match(text):
        if book:
            failures.append(f'{location}: council document mapped to {book}: {text}')
    elif not book or complete != '1':
        failures.append(f'{location}: unrecognized/incomplete reference: {text}')
if failures:
    sys.exit('\n'.join(failures))
print(f'Checked all {len(references)} rendered Latin references')
