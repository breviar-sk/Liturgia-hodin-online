<?php
header("Last-Modified:".gmdate("D, d M Y H:i:s")." GMT");
?>

<html>
<head>
	<meta http-equiv="Content-Type" content="text/html; charset=utf-8">
	<meta name="Author" content="Juraj Videky">
	<link rel="stylesheet" type="text/css" href="../../breviar.css">
	<title>Zoznam súborov v adresári</title>
</head>
<body>

<!-- podľa zoznamu pre include -->

<h2>Zoznam súborov v adresári <tt>source</tt></h2>

<?
/**
 * Change the path to your folder.
 *
 * This must be the full path from the root of your
 * web space. If you're not sure what it is, ask your host.
 *
 * Name this file index.php and place in the directory.
 *
 * Source: http://www.totallyphp.co.uk/scripts/directory_lister.htm
 */

// doplnil JUV/2008-10-23
// zmena JUV/2009-02-02
// clearstatcache();

// Define the full path to your folder from root
$path = "/data/www/www.breviar.sk/public_html/source/";

// Open the folder
$dir_handle = @opendir($path) or die("Nemôžem otvoriť adresár $path");

//this is a function I wrote to sort out the contents of the directory date wise for display.
$content_array = array();

//Load Directory Into Array
$i=0;
while ($file = readdir($dir_handle))
if ($file != "." && $file != ".." && $file != "index.php" && $file != "prvall" && $file != "skopci" && !fnmatch("*.cgi", $file) && !fnmatch("*.gz", $file) && (fnmatch("*.h", $file) || fnmatch("*.c", $file) || fnmatch("*.cpp", $file) || $file == "urob" || fnmatch("[Mm]akefile", $file)))
{
	$content_array[$i][0] = $file;
	$content_array[$i][1] = date ("Y-m-d H:i:s", filemtime($path."/".$file)); // JUV/2008-10-23, namiesto filemtime môže byť aj filectime
	$i++;
}
//close the directory handle
closedir($dir_handle);

//these lines sort the contents of the directory by the date
foreach($content_array as $res)
	$sortAux[] = $res[1];
array_multisort($sortAux, SORT_DESC, $content_array); 

//print
echo "\n<table>";
echo "\n<tr><th>Súbor</th><th>Posledná zmena</th></tr>";
foreach($content_array as $res)
	echo "\n<tr><td><a href=\"".$res[0]."\">$res[0]</a></td><td>".$res[1]."</td></tr>";
	// $res[0].">".$res[1];

echo "\n</table>";

?>

<br>
<hr>
<center><font size=-1>Last modified: 
<? 
// doplnil JUV/2008-10-23
echo date ("Y-m-d H:i:s", filemtime($_SERVER['SCRIPT_FILENAME']));
?>

<br>© 1999-2016 <a href="mailto:videky@breviar.sk">Juraj Vidéky</a></font></center>

</body>
</html>
