<?php
require_once '../game.inc';

function elo ($game1, $game2, $gana_a, $K){
      // El de puntuacion Ra se enfrenta a Rb
	  // K es una constaste a 20
	  
      $Ra=$game1->points;
	  $Rb=$game2->points;

      $Qa=pow(10,$Ra/400.0);
      $Qb=pow(10,$Rb/400.0);
  
      $Ea=$Qa/($Qa+$Qb);
      $Eb=$Qb/($Qa+$Qb);

      // nuevos valores
	  $game1->setPoints($Ra+$K*($gana_a-$Ea));
      $game2->setPoints($Rb+$K*(1-$gana_a-$Eb));  	 
      }
	  
function bubble ($game1,$game2,$gana_a){
      
	  
      $points1=$game1->points;
	  $points2=$game2->points;
	  if ($gana_a==1){
			// nuevos valores
			$game1->setPoints($points2);
			$game2->setPoints($points1);  	 
		}	  
		
	}	  

	   
	   
?>	   