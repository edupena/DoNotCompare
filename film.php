<html>
<head>
<title>Movies <--> DoNotCompare</title>

<script type="text/javascript">

  var _gaq = _gaq || [];
  _gaq.push(['_setAccount', 'UA-21077255-1']);
  _gaq.push(['_setDomainName', '.donotcompare.com']);
  _gaq.push(['_trackPageview']);

  (function() {
    var ga = document.createElement('script'); ga.type = 'text/javascript'; ga.async = true;
    ga.src = ('https:' == document.location.protocol ? 'https://ssl' : 'http://www') + '.google-analytics.com/ga.js';
    var s = document.getElementsByTagName('script')[0]; s.parentNode.insertBefore(ga, s);
  })();

</script>

</head>
<body bgcolor="#548DD4">

<?php
require_once 'constructors.inc';
require_once 'sort.inc';
$table='filmtable';


if (isset($_GET['report'])){
	$game1=emptyGame($table);
	$game1->getById($_GET['report']);
	$game1->report();
}
else{
	if(isset($_GET['id1']) && isset($_GET['id2']) && isset($_GET['wina'])){
		if ($_GET['wina']==0 || $_GET['wina']==1){
			if ($_GET['id1']!=$_GET['id2']){
				$game1=emptyGame($table);
				$game2=emptyGame($table);
				$game1->getById($_GET['id1']);
				$game2->getById($_GET['id2']);
				bubble($game1,$game2,$_GET['wina']);
				$game1->addPartidasTotalesLocal($table);
			}
		}
	}
}

$game_array=consecutive($table,array(''));
$game1=$game_array[0];
$game2=$game_array[1];

echo "<STYLE TYPE=\"text/css\"> 
		H1 {font-size:25; text-align: center;}
		TT {font-size:16;}
		WR {font-size:12; color:#632423;}
		FH{font-size:12;}				
		a:link { color: #000000; text-decoration: none; }
		a:visited { text-decoration: none; color: #000000; }		
	</STYLE>
	";

echo "<H1>Movie Ranking</H1><p align=center><font size='5'>Choose one</font></p>";


echo "

<br/><br/>
<table border=0 cellspacing=0 cellpadding=0 align=center
 style='border-collapse:collapse;border:none'>
 <tr>
 
		<td align=center>
				<a href='film.php?id1=$game1->id&id2=$game2->id&wina=1'>
					<img border=0 src='$game1->imagefile'/>
				</a>
		</td>

		<td width=360 align=center>
				<a href='film.php'>
					<img border=0 width=220 height=220 src='./images/reload.jpg'> 
					<br/>					
					<TT>Reload</TT>
				</a>
		</td>
		
		<td align=center>
				<a href='film.php?id1=$game1->id&id2=$game2->id&wina=0'>
					<img border=0 src='$game2->imagefile'>
				</a>
		</td>
	
 </tr>

		<td align=center>  
				<TT>$game1->title</TT>
		</td>

		<td align=center>
		
		</td>

		<td align=center>
				<TT>$game2->title</TT>
		</td>
 </tr>
 
 <tr>
		<td align=left>  
				<a href='film.php?report=$game1->id'>  
					<WR>Wrong Image</WR>
				</a>  			
		</td>

		<td align=center>
  
		</td>
		
		<td align=right>
				<a href='film.php?report=$game2->id'>  
					<WR>Wrong Image</WR>
				</a>  			
		<td>
  

 </tr>

</table>
";
?>
<br/><br/>	
<table border=0 align=center width=300>
	<tr > 
	<td align=center >
 <a href='game.php'>
<font size='3'>	Wanna rank games?</font>
</a>
	</td>
	
	<td align=center >
 <a href='http://blog.donotcompare.com'>
<font size='3'>	About these ranks</font>
</a>
	</td>
	</tr>
	
</table>	
<?php	
$total=$game1->getPartidasTotalesLocal($table);	
//$total=$game1->sincronizarPartidas();
echo "<br/><br/>
<font size='3'>Remaining fights to publish TOP 100: </font><font size='4'>";
if ((13000-$total)<=0) { echo "0! Ranking will be published ASAP! :-)"; }
else {echo 13000-$total;}
?>
</font> <a href='http://blog.donotcompare.com'><font size='2' color="#0000ff"><u>Why?</u></font></a>
<br/><br/><br/>
<a href='mailto:admin@donotcompare.com'>
<font size="2">Contact</font>
</a>
</body>
</html>