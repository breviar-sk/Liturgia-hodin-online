echo Vytvaram index.htm...
copy zoznam.htm index.htm
echo Mazem subory "export.htm"...
del /s export.htm
echo Kopirujem CSS...
copy ..\..\breviar.sk\breviar.css breviar.css
copy ..\..\breviar.sk\ebreviar-cz.css ebreviar-cz.css
echo Kopirujem subory do adresara "docs" pre offline verziu (marianske antifony a ordinarium)...
mkdir cz
cd cz
mkdir docs
cd docs
copy ..\..\..\..\breviar.sk\cz\docs\ord-inv.htm .
copy ..\..\..\..\breviar.sk\cz\docs\ord-k0.htm .
copy ..\..\..\..\breviar.sk\cz\docs\ord-k1.htm .
copy ..\..\..\..\breviar.sk\cz\docs\ord-k2.htm .
copy ..\..\..\..\breviar.sk\cz\docs\ord-k3.htm .
copy ..\..\..\..\breviar.sk\cz\docs\ord-k4.htm .
copy ..\..\..\..\breviar.sk\cz\docs\ord-k5.htm .
copy ..\..\..\..\breviar.sk\cz\docs\ord-k6.htm .
copy ..\..\..\..\breviar.sk\cz\docs\ord-km.htm .
copy ..\..\..\..\breviar.sk\cz\docs\ord-komp.htm .
copy ..\..\..\..\breviar.sk\cz\docs\ord-pc.htm .
copy ..\..\..\..\breviar.sk\cz\docs\ord-rch.htm .
copy ..\..\..\..\breviar.sk\cz\docs\ord-vesp.htm .
copy ..\..\..\..\breviar.sk\cz\docs\ukonkaj.htm .
cd ..
copy ..\breviar.css .
cd ..
