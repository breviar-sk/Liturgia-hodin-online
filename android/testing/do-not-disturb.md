# Do Not Disturb

The Device setting now activates a Breviár automatic DND rule while any app
activity is visible, including settings. Leaving the app (or turning off the
screen) releases this rule. A transient pause, such as opening the notification
shade, does not release it. Other DND rules and the user's global interruption
filter are never disabled by Breviár.

The policy blocks calls (including repeat callers), messages, conversations,
reminders, events, alarms and system sounds. It suppresses notification visual
effects: banners, full-screen intents, lights, badges, ambient display, status-bar
icons and notification-list entries, where supported by Android.

Media is muted during silent reading. Breviár's TTS service temporarily allows
media while initializing/reading, then removes the allowance on pause, stop,
completion, error or destruction. The service runs in another process, so a
private content-provider call synchronizes this policy before queuing speech.
All media shares this allowance; DND cannot allow only Breviár's audio stream.
Existing stricter user DND rules can still prevent TTS playback.

Android 10+ uses a per-rule policy. Android 7-9 needs a temporarily changed shared
policy, saved before modification and restored on exit or provider reconnection.
An intervening user edit is preserved. Android 7-8 lacks the switches for hiding
status-bar icons/notification lists and controlling media independently, so it
suppresses popups and uses total silence except during TTS. Android 15+ also
disallows priority notification channels for this rule. Earlier versions may
still allow channels the user explicitly exempted from DND. System-exempt
notifications (for example emergency/system UI) remain Android's responsibility.
On Android below 7 the option is omitted, including in `old_devices`.

## Automated checks

`DoNotDisturbTest` covers API 24, 28, 29 and 35: policy contents, foreground and
settings transitions, recreation, access denial/revocation, preserving existing
DND, rule reuse/deletion, provider restart, and TTS media transitions.
`TtsWakeLockTest` also verifies that media is allowed before audio is queued and
muted again on pause, error, stop and service destruction.

## Device checks

Robolectric verifies requested policies and lifecycle handling; notification
presentation and OEM behavior still need a real-device check:

1. Grant Do Not Disturb access in Android settings, then enable the Device switch.
   Send an ordinary notification and an incoming call from another device. Check
   sound, vibration, popup, full-screen UI and notification shade. Repeat with
   Breviár settings open and after switching appearance or rotating the screen.
2. Start external media playback before entering Breviár: it should become silent.
   Start TTS: it should be audible from the first words. Pause and resume TTS, then
   stop it and let a prayer end naturally. Silent reading should mute media again.
3. Leave Breviár or turn off its DND switch: the previous system behavior should
   return. Repeat with a separate system DND schedule already active: it must stay
   active. Existing TTS playback should continue when leaving the reader.
4. Revoke DND access while reading, then return; there must be no crash. Re-grant
   access and re-enable the switch. Force-stop/reopen the app and reboot to check
   that the system-owned condition provider clears stale sessions on reconnection.
5. On Android 7-9, compare the system DND settings before and after reading,
   including a change to those settings made during the reading session.
