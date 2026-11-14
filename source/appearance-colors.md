# Reader color palettes

Each mode has three optional overrides. An absent or empty value uses the
original stylesheet color; the default palette therefore needs no migration.

| Role | Day parameter | Night parameter | CSS custom property |
| --- | --- | --- | --- |
| Text | `ct0` | `ct1` | `--prayer-text` |
| Rubrics | `cr0` | `cr1` | `--prayer-rubric` |
| Background | `c0` | `c1` | `--prayer-background` |

The background parameters and the `-D`/`-N` CLI switches retain their previous
meaning. Values are three- or six-digit hexadecimal RGB without `#`, normalized
to six lowercase digits. Invalid values use the default. Both palettes travel
in generated links; only the active mode supplies CSS properties.

`appearance-colors.cpp` owns validation and request-local state. The two shared
stylesheets map roles to elements, including generated rubric symbols. Keep
the literal declarations and the `var()` fallback values: these preserve the
original colors when an override is unset, and retain default styling in older
renderers without custom property support. Android's `StaticHtml` supplies the
same properties for bundled HTML without duplicating those selectors. Native
menus and toolbars retain their own appearance.

`paletteMenu()` in `xml-settings.cpp` defines the controls and presets. A
`MenuGroup` with `Control="submenu"` opens a separate settings page instead of
an inline section. A `MenuItem` with `Control="preset"` contains `Set` children
with `Parameter` and `Value` attributes. Applying a preset assigns every value
in one save, including empty resets, and never switches the active day/night
mode. Presets are checked by matching their assignments against saved options;
there is no separate persistent preset identifier.

The day high-contrast preset explicitly sets black text (`000000`), dark red
rubrics (`800000`), and a white background (`ffffff`).

Android offers both high-contrast presets once to e-ink users, at reader startup
or after enabling e-ink. The `high_contrast_offered` preference records that the
dialog was displayed, regardless of the answer. Accepting loads both presets
from XML off the UI thread and applies them together without changing the
active day/night mode or other reader options. Declining keeps the colors.

Add presets to the C++ catalogue and localize their labels through the existing
settings dictionaries. Android interprets the assignments generically. The
legacy XML `Options` and supported-values sections remain unchanged.

Checks: `make -C source test-colors`, `make -C android/testing settings`, and
`make -C android/testing colors` (the latter requires Chromium), plus Android's
`ColorSettingsTest` and `StaticHtmlTest`.
