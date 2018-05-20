Liturgy of the Hours for iOS
____________________________


Repository available at: https://github.com/gyim/breviar-ios



That repository contains only the iOS sources, so in order to get started you have to fetch the rest of the files from various places.

First, clone that repository:

git clone https://github.com/gyim/breviar-ios.git

iOS project uses the sources of the web version as a submodule. However, that repository is not public, only some parts of it (unless you join the core team). To obtain the public sources you have to do the following:

# Fetch the public sources
cd breviar-ios
git clone https://github.com/breviar-sk/Liturgia-hodin-online.git breviar-cgi

# Fetch the text from the websites:
cd breviar-cgi
wget -r http://breviar.sk/include -nd -P include
wget -r http://breviar.sk/include_cz -nd -P include_cz
wget -r http://breviar.sk/include_hu -nd -P include_hu
Finally, clone the RaptureXML submodule for iOS:

cd ..
git submodule update --init RaptureXML

