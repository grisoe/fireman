#include <string.h>

#include "headers/jugador.h"

void prepararJugador(Jugador *j){

	//Tres variables que representan atributos de todo jugador.
	//Se podrían almacenar los valores ingresados por el usuario directamente
	//en los atributos del jugador, pero cero que es mejor así por cuestiones
	//de validación: ya que sean valores validados, se guardan allá.
	char nombre[50] = "";
	int nivel;
	int turnos;

	//Nombre sin validar al estilo arcade ("Anonimo" si no ingresa nombre).
	//"Anonimo", así, sin acento es por por necesidad más que por ignorancia
	//o pereza: al momento de querer hacer consultas por nombre, deberías
	//ingresarlo con acento, pero ncurses muestra basura cuando quieres hacer eso.
	//Algún día lo solucionaré.
	printw("Ingresa tu nombre: ");
	scanw("%[^\n]", nombre);

	if(strlen(nombre) == 0){
		strcpy(j->nombre, "Anonimo");
	}else{
		strcpy(j->nombre, nombre);
	}

	printw("Ingresa el nivel de dificultad (3-10): ");
	scanw("%d", &nivel);
	while(nivel < 3 || nivel > 10){

		printw("\nLos niveles de dificultad están entre 3 y 10.\n\n");

		printw("Ingresa el nivel de dificultad (3-10): ");
		scanw("%d", &nivel);

	}
	j->nivel = nivel;

	printw("Ingresa el número de turnos (5-30): ");
	scanw("%d", &turnos);
	while(turnos < 5 || turnos > 30){

		printw("\nEl número de turnos está entre 5 y 30.\n\n");

		printw("Ingresa el número de turnos (5-30): ");
		scanw("%d", &turnos);

	}
	j->turnos = turnos;

}

//Se cuentan los puntos en función de los edificios en pie y se asignan al jugador.
void setPuntuacion(Jugador *j, Terreno ciudad[][10]){

	int i;
	int k;

	j->puntuacion = 0;

	for(i = 0; i < j->nivel; i++){
		for(k = 0; k < j->nivel; k++){
			
			if(ciudad[i][k].tipo == EDIFICIO){
				(j->puntuacion)+=100;				
			}

		}
	}	

}