<?php

require_once '../game.inc';

class GameBDD {


//Attributs
	public $serv;
	public $log;
	public $mdp;
	public $nom_base;
	public $game;
	public $idconnection;

//Constructeurs-Destructerus
	function __construct($serv,$log,$mdp, $nom_base, $game){
		$this->serv=$serv;
		$this->log = $log;
		$this->mdp = $mdp;
		$this->nom_base = $nom_base;
		$this->game = $game;
	}



//Fonctions

	private function openBDD(){
		$this->idconnection=mysql_connect($this->serv, $this->log, $this->mdp)
		or die("Connection BDD Impossible");
	
		mysql_select_db($this->nom_base, $this->idconnection);
	
		$this->nom_table=$this->game->tablename;

	}

	private function closeBDD(){

		//Fermeture de la base
		mysql_close($this->idconnection);

	}


	public function saveGame(){
		

		$this->openBDD();

		$a=$this->game->title;		
		$b=$this->game->platform;		
		$c=$this->game->year;
		$d=$this->game->imagefile;	

		if ($game->tablename=='ranktable'){
			mysql_query("INSERT INTO ranktable 
			(title, platform,year,imagefile) VALUES('$a','$b',$c,'$d') ") 
			or die(mysql_error());  
		}
		elseif ($game->tablename=='filmtable'){
			mysql_query("INSERT INTO filmtable 
			(title,year,imagefile) VALUES('$a',$c,'$d') ") 
			or die(mysql_error());  
		}
		
		$this->closeBDD();
	}	
	
	public function updatePoints($points){
		
		$game=$this->game;		
		if ($game->id>=0){
			$this->openBDD();			
			mysql_query("UPDATE $game->tablename SET points = $points WHERE id =$game->id")		
			or die(mysql_error());  			
			mysql_query("UPDATE $game->tablename SET partidas = $game->partidas+1 WHERE id =$game->id")		
			or die(mysql_error());  
		
			$this->closeBDD();
		}
	}	


	public function getGameById($id){
		$game=$this->game;
		$game_return=0;
		if ($id>=0){
			$this->openBDD();		
			$Query="Select * From $game->tablename WHERE id=$id";
			$Res = mysql_query($Query, $this->idconnection);
			$elem = mysql_fetch_array($Res);
			$this->closeBDD();
			
			if ($game->tablename=='ranktable'){
				$game_return=new Game($elem[0],$elem[1], $elem[2],$elem[3],$elem[4],$elem[5],$elem[6],$elem[7],'ranktable');
			}
			elseif ($game->tablename=='filmtable'){
				$game_return=new Game($elem[0],$elem[1], '',$elem[2],$elem[3],$elem[4],$elem[5],$elem[6],'filmtable');
			}
											
		}
		return $game_return;		

	}
	
	private function getNumberOfRowsWithImage($array_consolas){
		$game=$this->game;
		$this->openBDD();		
		if ($array_consolas[0]!=''){
			$Query="SELECT COUNT(*) FROM $game->tablename WHERE imagefile!='' AND (";		
			foreach($array_consolas as $console){
				$Query=$Query . "platform='$console' OR ";			
			}		
			$Query=$Query . "id<0)";		
		}
		else{
			$Query="SELECT COUNT(*) FROM $game->tablename WHERE imagefile!=''";
		}
			
		$Res = mysql_query($Query, $this->idconnection);
		$elem = mysql_fetch_array($Res);			
		$this->closeBDD();
		return $elem[0];
	}
	
	
	public function getTwoConsecutiveGames($array_consolas){	
		
		$pos=rand(1,$this->getNumberOfRowsWithImage($array_consolas)-1);				
		$game=$this->game;		
		$this->openBDD();		
		if ($array_consolas[0]!=''){
			$Query="SELECT * FROM $game->tablename WHERE imagefile!='' AND (";		
			foreach($array_consolas as $console){
				$Query=$Query . "platform='$console' OR ";			
			}		
			$Query=$Query . "id<0) ORDER BY points ASC LIMIT $pos,2";		
		}
		else{
			$Query="SELECT * FROM $game->tablename WHERE imagefile!='' ORDER BY points ASC LIMIT $pos,2";
		}
				
		$Res = mysql_query($Query, $this->idconnection);		
		$this->closeBDD();		
		
		$game_return= array();		
		if ($game->tablename=='ranktable'){
			while ($elem = mysql_fetch_array($Res)){									
				array_push($game_return, new Game($elem[0],$elem[1], $elem[2],$elem[3],$elem[4],$elem[5],$elem[6],$elem[7],'ranktable'));
				
			}	
		}
		elseif ($game->tablename=='filmtable'){
			while ($elem = mysql_fetch_array($Res)){						
				array_push($game_return,new Game($elem[0],$elem[1], '',$elem[2],$elem[3],$elem[4],$elem[5],$elem[6],'filmtable'));
				
			}	
		}		
		
		return $game_return;
	}
	
	
	public function getSecondOne(){	
		
		$game=$this->game;
		$this->openBDD();		
		$Query="SELECT points FROM $game->tablename ORDER BY points DESC LIMIT 1,1";				
		$Res = mysql_query($Query, $this->idconnection);
		$elem = mysql_fetch_array($Res);
				
		$this->closeBDD();
		return $elem[0];
	}
	
	
	public function printGameList(){
		$this->openBDD();		
		$Query="Select title From $this->game->tablename ORDER BY title ASC";
		$Res = mysql_query($Query, $this->idconnection);
		$i=1;
		while ($elem = mysql_fetch_array($Res)){
			echo "$i: $elem[0]<br/>";
			$i++;
		}				
		$this->closeBDD();
	}
	
	
	
	public function getLastId(){
		
		$game=$this->game;
		$this->openBDD();
		
		$Query="Select max(id) From $game->tablename";				
		$Res = mysql_query($Query, $this->idconnection);
		$elem = mysql_fetch_array($Res);
				
		$this->closeBDD();
		return $elem[0];
	}

	
	
	public function report(){
	
		$game=$this->game;
		
		if ($this->game->points>=0 && $this->game->id>=0){
			$this->openBDD();						
			mysql_query("UPDATE $game->tablename SET reports = $game->reports+1 WHERE id =$game->id")		
			or die(mysql_error());  
		
			$this->closeBDD();
		}
	
	}
	
	public function partidasTotalesBDD(){
		
		$this->openBDD();
	
		$query = "SELECT SUM(partidas) FROM $this->game->tablename"; 
	 
		$result = mysql_query($query) or die(mysql_error());
		
		$this->closeBDD();
		
		$elem = mysql_fetch_array($result);
		return $elem;
	}


	

}

?>