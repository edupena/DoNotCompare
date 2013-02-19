<?php

require_once '../game.inc';

function emptyGame($tablename){
	return new Game(0,'0','0',0,'0',0,0,0,$tablename);
}

function random($tablename,$exception_id){	
	$game=emptyGame($tablename);
	$max=$game->getLastId();
	if ($max>1){
		do{
			$id=rand(1,$max);
			$game->getById($id);
		}while($game->id=='' || $game->id==$exception_id || $game->imagefile=='');
	}
	return $game;
}

//----------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------
function consecutive($tablename,$array_consolas){
	
	$game=emptyGame($tablename);
	$resul=$game->getTwoConsecutiveGames($array_consolas);
	
	return $resul;
}



?>