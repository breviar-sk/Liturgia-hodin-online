echo Vytvaram index.htm...
copy zoznam.htm index.htm
echo Mazem subory "export.htm"...
del /s export.htm
echo Kopirujem CSS...
copy ..\..\breviar.sk\breviar.css .
echo Kopirujem subory do adresara "docs" pre offline verziu (marianske antifony a ordinarium)...
mkdir hu
cd hu
mkdir docs
cd docs
copy ..\..\..\..\breviar.sk\hu\docs\ord-inv.htm .
copy ..\..\..\..\breviar.sk\hu\docs\ord-k0.htm .
copy ..\..\..\..\breviar.sk\hu\docs\ord-k1.htm .
copy ..\..\..\..\breviar.sk\hu\docs\ord-k2.htm .
copy ..\..\..\..\breviar.sk\hu\docs\ord-k3.htm .
copy ..\..\..\..\breviar.sk\hu\docs\ord-k4.htm .
copy ..\..\..\..\breviar.sk\hu\docs\ord-k5.htm .
copy ..\..\..\..\breviar.sk\hu\docs\ord-k6.htm .
copy ..\..\..\..\breviar.sk\hu\docs\ord-km.htm .
copy ..\..\..\..\breviar.sk\hu\docs\ord-komp.htm .
copy ..\..\..\..\breviar.sk\hu\docs\ord-pc.htm .
copy ..\..\..\..\breviar.sk\hu\docs\ord-rch.htm .
copy ..\..\..\..\breviar.sk\hu\docs\ord-vesp.htm .
copy ..\..\..\..\breviar.sk\hu\docs\ukonkaj.htm .
cd ..
copy ..\breviar.css .
cd ..
