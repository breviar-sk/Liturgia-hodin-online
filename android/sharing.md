# Prayer sharing and site verification

The drawer's **Share prayer** action creates an offline QR code and offers copying
or sharing its URL. The public URL is `https://breviar.sk/cgi-bin/l.cgi?...`.
`qt=pdnes` daily overviews remain relative to today. Individual daily prayers use
explicit dates, including when entered through a relative URL. Christmas seasonal
requests (`qt=plo`) carry their reference year in `r=`. The backend supplies the
resolved query to Android; sharing does not calculate dates. Prayer selection,
language, calendar, Commons and all resolved reader options travel in the query,
including font family, size, weight, palettes, day/night mode, margins and line
spacing. Device preferences and pinch zoom remain local. Generated links do not
depend on the sender's import preference.

New sharing links include `sh=1`, the sharing format version. This is metadata,
not a prayer or device setting. Both Android and web sharing always emit the
current version; Android still accepts regular CGI links without the marker.
Version-dependent migration and filtering of non-sharing links are not implemented.

**Settings → Device → Apply appearance from shared prayers** controls what a
recipient accepts. It defaults to off, importing only prayer/content settings.
With it enabled, the app also imports appearance. Settings absent from a link
retain their current values. Filtering happens before value validation and
before building the reader request; ignored visual values never reach the
renderer. The content-bit masks in `PrayerLink` correspond to
`source/liturgia.h`; update them when adding content options to words 0 or 2.

Font files and sender-specific font CSS are not shared. Font families are
resolved against the recipient's local catalog on the existing font worker.
An unavailable font leaves the current font and CSS unchanged. Pending lookups
survive recreation; canceled or superseded lookups cannot replace a newer page.

Incoming links are rendered offline by the existing backend. Only HTTP(S) links
on `breviar.sk`, with the exact path `/cgi-bin/l.cgi`, are registered. The app
validates the query and allows reader pages, including the Ordinarium (`pst&st=2`).
It does not register other hosts or all paths on the website.

The first incoming link saves the previous prayer settings and reading location.
The backup survives further shared links, settings edits, recreation and process
termination. **Restore my settings** restores that backup and returns to the old
prayer (or home after a cold start). **Keep these settings** makes the active
settings permanent. Both actions appear only during a temporary session. Back
retains its usual page-navigation behavior. Device changes, such as choosing a
new font or enabling e-ink, survive restoration in content-only sessions. If
appearance was imported during the session, Restore also restores the original
reader appearance and font CSS. The import scope is saved independently of the
Device toggle, so changing that toggle affects future links, not restoration.
Native device preferences and pinch zoom are never restored from a shared link.

## Web sharing

The CGI side menu offers **Share prayer** for reader pages and the Ordinarium.
The backend constructs the public link from the resolved selection and settings,
including settings submitted through POST. Generated query parameters start with
`qt`, `d`, `m`, `r`, `j`, omitting absent fields; the remaining parameters follow
in alphabetical order. The same ordering is used by Android sharing.

The menu requests the existing CGI selection with `share=1`; this flag is never
included in the shared link. The server generates an SVG using the vendored MIT
licensed Project Nayuki QR Code generator v1.8.0. The browser loads just the sharing
panel from that response, preserving the current page and scroll position. Without
JavaScript, the link opens the complete page with its sharing panel visible.
QR encoding runs only for sharing requests, not for ordinary reader requests.

Publish `prayer-sharing.js` and the updated `breviar.css` along with the CGI binary.
No image service, PNG library or additional server process is needed. The SVG uses
black modules on a white background with a four-module quiet zone in every theme.
The web-only C++ sources are listed in the Makefile, `urob` and Visual Studio project;
native Android/iOS builds keep their existing sharing implementations.

## Android: publish the Digital Asset Links file

1. Obtain the SHA-256 fingerprint of the **signing certificate**, not the APK
   hash. For a locally signed nightly/release APK, run the SDK tool:

   ```sh
   "$ANDROID_HOME/build-tools/36.0.0/apksigner" verify --print-certs breviar.apk
   ```

   Use `Signer #1 certificate SHA-256 digest`, formatted as uppercase hex byte
   pairs separated by colons. For a Google Play build using Play App Signing,
   obtain the **app signing certificate** SHA-256 from Play Console's App signing
   page; the upload certificate may be different. Include both fingerprints in
   the array if nightlies and Play releases use different signing certificates.

2. Create `assetlinks.json`, replacing the fingerprint placeholder:

   ```json
   [{
     "relation": ["delegate_permission/common.handle_all_urls"],
     "target": {
       "namespace": "android_app",
       "package_name": "sk.breviar.android",
       "sha256_cert_fingerprints": ["REPLACE_WITH_COLON_SEPARATED_SHA256"]
     }
   }]
   ```

   The package is `sk.breviar.android`; `sk.breviar.android.BreviarApp` is the
   Application class and must not be used here.

3. Publish at **https://breviar.sk/.well-known/assetlinks.json**. Put it under
   `.well-known/assetlinks.json` in that HTTPS virtual host's document root.
   Serve HTTP 200, `Content-Type: application/json`, with a valid public TLS
   certificate, no authentication and **no redirects**, including to `www`.
   If an association file already exists, add this statement to its array.

4. Install the matching signed build. On Android 12+ recheck and inspect:

   ```sh
   adb shell pm verify-app-links --re-verify sk.breviar.android
   adb shell pm get-app-links sk.breviar.android
   adb shell am start -W -a android.intent.action.VIEW -c android.intent.category.BROWSABLE -d 'https://breviar.sk/cgi-bin/l.cgi?qt=pdnes&p=mv&j=sk'
   ```

   Verification is asynchronous; allow time before inspecting the result. Expect
   `breviar.sk: verified`. Enable **Open supported links** in the app's Android
   settings if the user previously disabled it. To test only the app handler
   before publishing the file, append `-p sk.breviar.android` to `am start`; that
   does **not** test website verification.

## iOS: prepare the association file for the future implementation

1. Get the iOS app's actual `application-identifier` from the signed app's
   entitlements (Xcode or `codesign -d --entitlements :- /path/to/Breviar.app`).
   It has the form `APP_ID_PREFIX.BUNDLE_ID`. The prefix is often the Team ID,
   but use the actual value; neither the Android package nor a guessed Team ID
   is a substitute.

2. The repository includes `.well-known/apple-app-site-association`, with
   **no extension**, configured for the confirmed iOS app identifier:

   ```json
   {
     "applinks": {
       "details": [{
         "appIDs": ["3K775ZSA59.sk.breviar.breviar-sk"],
         "components": [{"/": "/cgi-bin/l.cgi"}]
       }]
     }
   }
   ```

3. Publish at
   **https://breviar.sk/.well-known/apple-app-site-association**, also as HTTP
   200 JSON over public HTTPS, without redirects or authentication. Merge the
   `applinks` entry with any existing services in this file. No signing of the
   JSON file or manual verification submission is required.

4. The iOS maintainers must add the **Associated Domains** capability to the
   app target, with `applinks:breviar.sk`, update provisioning as needed, and
   implement incoming HTTPS-link handling and temporary settings. This Android
   change does not implement those iOS changes. Publishing the file alone cannot
   enable Universal Links in the current iOS app.

5. Once implemented, install a newly signed iOS build and tap the HTTPS link
   from Notes or Messages. Typing it in Safari's address bar is not a Universal
   Links test. Apple's association CDN caches the file, so deployment changes
   can take time to reach devices.

Check both published files with `curl -i URL` (without `-L`, to catch redirects).
Only `breviar.sk` is used by this implementation. Supporting another hostname
later requires app declarations, validation and association files for that host.

Official references:
- https://developer.android.com/training/app-links/configure-assetlinks
- https://developer.android.com/training/app-links/verify-applinks
- https://developer.apple.com/documentation/xcode/supporting-associated-domains
