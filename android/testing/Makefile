ROOT := $(abspath ../..)
CLASSES := $(ROOT)/android/build/settings-test
JAVA ?= java
JAVAC ?= javac
PYTHON ?= python3
NODE ?= node

.PHONY: settings
settings:
	$(MAKE) -C $(ROOT)/source
	mkdir -p $(CLASSES)
	$(JAVAC) -d $(CLASSES) ../src/sk/breviar/android/SettingsXml.java SettingsXmlTest.java
	$(JAVA) -cp $(CLASSES) sk.breviar.android.SettingsXmlTest $(ROOT)

.PHONY: taps
taps:
	$(PYTHON) check_tap_navigation.py

.PHONY: zoom
zoom:
	$(NODE) check_zoom.js
