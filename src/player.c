#include <string.h>

#include "headers/player.h"

void setPlayer(Player *player){

	//Tres variables que representan atributos de todo Player.
	//Se podrían almacenar los valores ingresados por el usuario directamente
	//en los atributos del Player, pero cero que es mejor así por cuestiones
	//de validación: ya que sean valores validados, se guardan allá.
	char name[50] = "";
	int level;
	int turns;

	//name sin validar al estilo arcade ("Anonimo" si no ingresa name).
	//"Anonimo", así, sin acento es por por necesidad más que por ignorancia
	//o pereza: al momento de querer hacer consultas por name, deberías
	//ingresarlo con acento, pero ncurses muestra basura cuando quieres hacer eso.
	//Algún día lo solucionaré.
	printw("Name: ");
	scanw("%[^\n]", name);

	if(strlen(name) == 0){
		strcpy(player->name, "Anonymous");
	}else{
		strcpy(player->name, name);
	}

	printw("Difficulty level (3-10): ");
	scanw("%d", &level);
	while(level < 3 || level > 10){

		printw("\nDefficulty level between 3 and 10.\n\n");

		printw("Difficulty level (3-10): ");
		scanw("%d", &level);

	}
	player->level = level;

	printw("Number of turns (5-30): ");
	scanw("%d", &turns);
	while(turns < 5 || turns > 30){

		printw("\nTurns must be between 5 and 30.\n\n");

		printw("Number of turns (5-30): ");
		scanw("%d", &turns);

	}
	player->turns = turns;

}

//Se cuentan los puntos en función de los edificios en pie y se asignan al Player.
void setPoints(Player *player, Ground city[][10]){

	int i;
	int k;

	player->points = 0;

	for(i = 0; i < player->level; i++){
		for(k = 0; k < player->level; k++){
			
			if(city[i][k].type == BUILDING){
				(player->points)+=100;				
			}

		}
	}	

}