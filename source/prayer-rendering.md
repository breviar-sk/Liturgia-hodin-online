# Prayer text rendering

The rendering pipeline keeps file syntax, inline formatting, and liturgical
choices separate. It uses C++11 and the existing `Export`/`ExportChar` sink, so
CGI, Android's string output, and the other native frontends share the code.

- `template-reader`: owns the input file and reads UTF-8 characters and `{...}`
  markers. `Marker` splits a name and optional argument at the first colon.
  HTML comments remain ordinary text: many templates deliberately open a
  comment before a marker and close it after the replacement.
- `prayer-markup`: handles Bible links, footnotes, notes, verse numbers,
  conditional italics, full-text passages, catechesis/Psalm 95 links, and
  symbols/TTS pauses. Captures use owned strings. A stack keeps inline
  visibility separate from the enclosing section's visibility. Closing an
  inline marker never enables its enclosing passage; unmatched closings do
  nothing. Template/section styles retain the existing CSS and pause spacing.
- `prayer-renderer`: selects include anchors and handles conditional passages,
  crosses, alternative-psalm links, and collect conclusions. Matching anchors
  are case-insensitive, can repeat, and can overlap as aliases. They must **not**
  be treated as an ordinary nested element tree. Conditional passages are
  independent of these aliases.
- `breviar.cpp`: chooses the prayer/template and interprets liturgical template
  directives using the existing calendar and prayer records. It passes one
  `RenderState` through all selected sections. XML index export stays at this
  boundary and does not expand included HTML.

`{r:Lk}1, 46-55{/r}` now works directly in templates (including the Magnificat)
as well as in included sections. With references disabled, only `1, 46-55` is
rendered. The prefix contributes to the Bible target, not the displayed label.
Hidden canticles, disabled footnotes, and TTS option overrides still apply.

`RenderState` is local to one prayer; inline capture state is local to one
fragment. Calendar, language, options, and the output sink still belong to the
legacy backend. This refactor does not make concurrent requests safe.

## Verification

Run `make -C source test` for the existing backend tests, exact rendering
fixtures, UTF-8 reader tests, and nesting/reference regressions. Golden files
were captured before the refactor; do not regenerate them just to accept a
rendering difference.

To compare complete prayers against a saved CGI executable:

```
python3 source/tests/compare-prayer-renderers.py /path/to/baseline.cgi l.cgi
```

This compares 576 queries byte for byte, spanning six languages, eight prayer
types, ordinary time, Easter, Christmas, and normal/optional/TTS settings.
Intended differences from the pre-refactor binary are newly active template
references and fixes for hidden passages exposed by nested markers/aliases or
stale citation text emitted by an unmatched `{/r}`. Review differences explicitly;
the comparison tool intentionally does not normalize them away.

Native source lists are maintained in `Makefile`, `Android.mk`, `urob`, and the
Windows Visual Studio project. The separately maintained iOS Xcode project
must add the new source files as described in `ios/README.md`.
