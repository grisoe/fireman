#include <string.h>

#include "headers/player.h"

void setPlayer(Player *j){

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
	printw("Ingresa tu name: ");
	scanw("%[^\n]", name);

	if(strlen(name) == 0){
		strcpy(j->name, "Anonimo");
	}else{
		strcpy(j->name, name);
	}

	printw("Ingresa el level de dificultad (3-10): ");
	scanw("%d", &level);
	while(level < 3 || level > 10){

		printw("\nLos leveles de dificultad están entre 3 y 10.\n\n");

		printw("Ingresa el level de dificultad (3-10): ");
		scanw("%d", &level);

	}
	j->level = level;

	printw("Ingresa el número de turns (5-30): ");
	scanw("%d", &turns);
	while(turns < 5 || turns > 30){

		printw("\nEl número de turns está entre 5 y 30.\n\n");

		printw("Ingresa el número de turns (5-30): ");
		scanw("%d", &turns);

	}
	j->turns = turns;

}

//Se cuentan los puntos en función de los edificios en pie y se asignan al Player.
void setPonints(Player *j, Ground city[][10]){

	int i;
	int k;

	j->points = 0;

	for(i = 0; i < j->level; i++){
		for(k = 0; k < j->level; k++){
			
			if(city[i][k].type == BUILDING){
				(j->points)+=100;				
			}

		}
	}	

}