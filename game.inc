<?php

require_once './gameBDD.inc';

class Game {

//Attributs
	public $id;
	public $title;
	public $platform;
	public $year;
	public $imagefile;
	public $points;
	public $partidas;
	public $reports;
	public $tablename;

//Constructeurs-Destructerus
	function __construct($id,$title,$platform,$year,$imagefile,$points,$partidas,$reports,$tablename){		
		$this->id = $id;
		$this->title = $title;
		$this->platform = $platform;
		$this->year = $year;
		$this->points = $points;
		$this->imagefile = $imagefile;
		$this->partidas = $partidas;
		$this->reports = $reports;
		$this->tablename = $tablename;
	//	$this->gameBDD = new GameBDD("localhost","root",
	//							"", "rankbdd",$this);
		$this->gameBDD = new GameBDD("DATABASE_URL","DATABASE_USERNAME",
								"DATABASE_PASS", "donotcom_rankbdd",$this);
	}


	function __tostring(){
		
		$data="
			Game</br>
			<li>id:  $this->id</li>
			<li>title:  $this->title</li>
			<li>platform:  $this->platform</li>
			<li>year:  $this->year</li>
			<li>points:  $this->points</li>
			<li>partidas:  $this->partidas</li>
			<li>imagefile:  <img src='$this->imagefile'/></li>
			";

		return $data;

	}

	public function saveBDD(){
		$this->gameBDD->saveGame();
	}	

	public function getById($id){
		$gametemp=$this->gameBDD->getGameById($id);
		$this->id = $gametemp->id;
		$this->title = $gametemp->title;
		$this->platform = $gametemp->platform;
		$this->year = $gametemp->year;
		$this->imagefile = $gametemp->imagefile;
		$this->partidas = $gametemp->partidas;
		$this->points = $gametemp->points;
		$this->reports = $gametemp->reports;
		$this->tablename=$gametemp->tablename;
	}
	
	public function getLastId(){
		return $gametemp=$this->gameBDD->getLastId();
	}
	
	public function getSecondOne(){
		return $gametemp=$this->gameBDD->getSecondOne();
	}
	
	public function getTwoConsecutiveGames($array_consolas){		
		do{
			$gametemp=$this->gameBDD->getTwoConsecutiveGames($array_consolas);
		}while(sizeof($gametemp)==1);
		return $gametemp;
	}
	
	public function setPoints($pts){	
		$this->gameBDD->updatePoints($pts);
	}

	public function printGameList(){
		$this->gameBDD->printGameList();
	}
	
	public function report(){	
		$this->gameBDD->report();
	}
	
	
	public function getPartidasTotalesBDD(){
		$lis=$this->gameBDD->partidasTotalesBDD();
		return $lis[0];
	}
	
	public function getPartidasTotalesLocal($table){
		$partidas = fopen("partidas_$table.txt",'r');
		$act = fscanf($partidas,'%d');
		fclose($partidas);		
		return $act[0];
	}
	
	public function addPartidasTotalesLocal($table){
		$act=$this->getPartidasTotalesLocal($table);
		$partidas=fopen("partidas_$table.txt",'w');
		fwrite($partidas,$act+1);
		fclose($partidas);
	}
	
	public function sincronizarPartidas($table){
		$real=$this->getPartidasTotalesBDD();
		$partidas=fopen("partidas_$table.txt",'w');
		fwrite($partidas,$real/2);
		fclose($partidas);
		return $real;
	}
}

?>
