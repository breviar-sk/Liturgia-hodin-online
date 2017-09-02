echo Vytvaram index.htm...
copy zoznam.htm index.htm
echo Mazem subory "export.htm"...
del /s export.htm
echo Kopirujem CSS...
copy ..\..\breviar.sk\breviar.css breviar.css
echo Kopirujem subory do adresara "docs" pre offline verziu (marianske antifony a ordinarium)...
mkdir czop
cd czop
mkdir docs
cd docs
copy ..\..\..\..\breviar.sk\czop\docs\ord-inv.htm .
copy ..\..\..\..\breviar.sk\czop\docs\ord-k0.htm .
copy ..\..\..\..\breviar.sk\czop\docs\ord-k1.htm .
copy ..\..\..\..\breviar.sk\czop\docs\ord-k2.htm .
copy ..\..\..\..\breviar.sk\czop\docs\ord-k3.htm .
copy ..\..\..\..\breviar.sk\czop\docs\ord-k4.htm .
copy ..\..\..\..\breviar.sk\czop\docs\ord-k5.htm .
copy ..\..\..\..\breviar.sk\czop\docs\ord-k6.htm .
copy ..\..\..\..\breviar.sk\czop\docs\ord-km.htm .
copy ..\..\..\..\breviar.sk\czop\docs\ord-komp.htm .
copy ..\..\..\..\breviar.sk\czop\docs\ord-pc.htm .
copy ..\..\..\..\breviar.sk\czop\docs\ord-rch.htm .
copy ..\..\..\..\breviar.sk\czop\docs\ord-vesp.htm .
copy ..\..\..\..\breviar.sk\czop\docs\ukonkaj.htm .
cd ..
copy ..\breviar.css .
cd ..
