Getting started
===============

This repository contains only the iOS sources, so in order to get started you
have to fetch the rest of the files from various places.

First, create a directory for the Breviar project and clone the `ios` branch
of this repository:

    mkdir Liturgia-hodin-online
    cd Liturgia-hodin-online
    git clone https://github.com/gyim/Liturgia-hodin-online.git ios -b ios

The ios/ folder will contain only the iOS sources, but with a good git history.
Clone and link the rest of the sources from here:

    git clone https://github.com/breviar-sk/Liturgia-hodin-online.git exported-sources
    ln -s exported-sources/cgi-bin exported-sources/*.css .

Fetch the texts from the breviar.sk website:

    wget -r http://breviar.sk/include -nd -P include
    wget -r http://breviar.sk/include_cz -nd -P include_cz
    wget -r http://breviar.sk/include_hu -nd -P include_hu

Finally, clone the RaptureXML submodule for iOS:

    cd ios
    git submodule update --init

