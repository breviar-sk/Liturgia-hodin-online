# Bible references and providers

`prayer-markup.cpp` reads the existing options and prayer language, then delegates
to `bible::BibleLinks`. The facade parses the target (hidden `{r:prefix}` plus
visible label) and asks a `BibleLinkProvider` for a URL. Only the renderer emits
HTML. The displayed citation and the `{r}` template syntax are unchanged.

- `bible-reference.{h,cpp}` owns book identities, per-language aliases, and parsing.
  Configuration and CGI globals do not enter this layer. Its alias maps are
  initialized once and then immutable. Unknown or conflicting aliases do not
  select a book. Whitespace, case, Unicode dashes, lists, ranges, verse suffixes,
  single-chapter books, and paired Psalm numbers are handled explicitly.
- `bible-links.{h,cpp}` owns provider classes and selection. The text provider
  preserves custom URL prefixes and does not require the parser to recognize a
  reference. Bible.com uses parsed book/chapter/verse information. Nova Vulgata
  uses a verified document table and chapter anchors. URLs are component-encoded;
  the renderer separately escapes them for HTML attributes.

The existing Bible.com switch takes precedence. Otherwise the standard Vatican
base URL selects Nova Vulgata; any other configured prefix selects the text
provider. No settings keys or frontend APIs change. The facade snapshots its
configuration, so a later request can use a different language or provider.
Android retains its diacritic removal for the text-provider Bible-app intent.
An empty provider or an unknown structured reference produces an unlinked label,
not a broken relative URL. Parsed references retain `complete` for audits; a
recognized first passage can still be linked when later syntax is unsupported.

## Numbering and precision

Nova Vulgata links to the first cited chapter. Single-chapter books have no
chapter anchor. Psalms have `PSALMUS N` anchors, with modern numbering. Latin and
Spanish prayer profiles use traditional numbering; other profiles use modern
numbering. The provider accepts this as an explicit `PsalmNumbering` argument,
independent of language. Traditional paired numbers are checked against the
split/combined Psalm mapping. Ambiguous bare Psalms 9 and 113, inconsistent pairs,
and chapters absent from the destination edition link to the book page.

Bible.com retains the written chapter/Psalm number; edition-specific verse or
Psalm renumbering is not inferred from its configurable edition ID. It links
verse lists/ranges within the first chapter. Multiple books or chapters still
link to the start of the reference. Verse-letter suffixes remain in the parsed
representation and visible label; neither provider invents subverse anchors.

To add a language, extend `Language`, `languageFromCode`, and the alias column.
Aliases are scoped to a language: do not add another language's abbreviations
unless they occur in the includes and have unambiguous meanings. To add a
provider, implement `BibleLinkProvider::link` and select it in the facade; reuse
the parser and catalogue. Keep provider-specific numbering in that provider.
The implementation supports C++11 and has no new dependencies.

## Verification

`make -C source test` includes parser/provider unit tests, exact rendering
fixtures, actual Latin canticle/Psalm URLs, and all Vatican chapter destinations
against the checked-in index snapshot. It requires no network access.

For a live check of all book pages and generated anchors:

```
python3 source/tests/vatican-links-test.py source/.test-build/bible-reference-test --online
```

The optional `--cache /tmp/vatican-pages` saves downloaded pages. The fixture
records all 73 document names and their chapter counts, verified against the
[Vatican index](https://www.vatican.va/archive/bible/nova_vulgata/documents/nova-vulgata_index_lt.html).

For include audits, the test executable accepts `--parse la` (or another language
code), reading one reference per line and reporting the book code, parse
completeness, and first chapter. `{r}` also encloses some council-document
citations; unknown references should be reviewed rather than blindly corrected.
