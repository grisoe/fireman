#include <string.h>

#include "headers/game.h"
#include "headers/colors.h"
#include "headers/files.h"

//Sólo sirve para envolver a las otras tres funciones que preparan las cosas
//necesarias para jugar.
void setGame(Player *j, Fireman *b, Ground city[][10]){

	clear();

	printw("---------------Prepare Game---------------\n\n");

	setPlayer(j);
	createFireman(b, j->level, j->turns);
	buildCity(city, j->level, b->x, b->y);

	printw("\nGame ready!");

	getch();
	refresh();

}

void startGame(Player *j, Fireman *b, Ground city[][10], Player js[], int *numJs){

	

	int turns;
	//Opción elegida por el usuario.
	int opc;
	//Mientras intentes hacer cosas inválidas, esta variable se mantendrá en 0.
	//Esto es así para no perder un turno por el intento de movimiento ilegal.
	//Obviamente, cada movimiento válido pone esta bandera en 1, sacándote del
	//do-while y dantro otra vuelta en el ciclo for, que es el de los turns.
	//Qué trucazo, ¿no?
	int band;
	int din = b->dynamites;
	int incendios;

	//Ciclo principal del juego (cuando ya te estás moviendo y dinamitando).
	for(turns = 1; turns <= j->turns; turns++){

		//Cuando no hay incendios te sales del ciclo porque apagaste todos
		//y ya no hay nada que hacer.
		if(incendios == 0){
			break;
		}

		do{ //do-while ya mencionado.

			clear();

			attron(COLOR_PAIR(5));

			printw("---------------Game Initialized---------------");

			//Se actualiza el mapa y la información con cada vuelta, legal o ilegal.
			showMap(city, j->level, b->x, b->y);
			showPosInfo(city, b->y, b->x, turns, j->turns, din);

			opc = actionMenu();

			switch(opc){

				//Las opciones del 1 al 4 son para moverse.
				//La dirección se pide en otra función.
				case 1:
				case 2:
				case 3:
				case 4:
					band = moveFireman(opc, b, j->level);

					break;

				//La opción 5 es para dinamitar.
				case 5:

					if(din > 0){ //Si te quedan, dynamites.

						//Si puedo dinamitar, guardo un 1.
						band = dynamite(b->x, b->y, j->level, city);

						//Resta una dinamita sólo si logró dinamitar.
						if(band == 1){
							din--;
						}

					}else{
						printw("\nYou don't have any dynamites.\n");
						band = 0;
						getch();
						refresh();
					}

					break;

				case 6: //Opción para no hacer nada.
					band = 1;
					break;

			}

			//Se actualiza el número de incendios.
			incendios = getNumFires(city, j->level);

		}while(band == 0);

		//Cada tercer turno se incendian los Grounds en peligro y se ponen
		//en peligro los adyacentes a estos nuevos FIREs.
		if(turns % 3 == 0){
			burnDown(city, j->level);
			setDanger(city, j->level);
		}

	}

	//De aquí y hasta el final de la función, se muestra el código ejecutado
	//al terminar un juego, independientemente de su estado.

	clear();

	printw("---------------Game Initialized---------------");
	
	showMap(city, j->level, b->x, b->y);
	showPosInfo(city, b->y, b->x, turns, j->turns, din);
	
	//Si logras vencer al FIRE se te felicita con mucho entusiasmo.
	if(incendios == 0){
		printw("\nYou have extinguished all fires!\n");
		//Los turns tienen un offset positivo de 1, así que se lo resto aquí.
		j->turns = turns - 1;
	}

	//Si no acabaste con todos los incendios, se imprime un mensaje
	//diciendo que la lluvia jugó mejor que tú.
	if(incendios > 0){
		printw("\nIt's raining!\n");
	}

	setPoints(j, city);
	printw("\nYour points: %d\n", j->points);

	//Se guarda el Player en el arreglo y se incrementa el contador de Playeres.
	js[*numJs] = *j;
	(*numJs)++;

	//Se escribe la información del Player en un archivo.
	writeRecords(js, *numJs);

	//No te deja salir del juego hasta que presiones la tecla "s".
	//Lo hice así para que no te salgas sin querer del juego por presionar
	//cualquier otra tecla. Uno puede querer quedarse un rato ahí viendo su puntuación.
	//noecho() es para que no muestre las teclas presionadas.
	printw("\nPress 's' to continue...");
	noecho();
	while(getch() != 's');
	echo();

	refresh();

}

//Muestra la información de cabecera y el mapa coloreado del juego.
//Los parámetros "x" y "y" son las coordenadas del Fireman.
void showMap(Ground city[][10], int level, int x, int y){

	//Para guardar los caracteres a mostrarse en cada Ground.
	char desc[5];

	int i;
	int k;

	printw("\n\nB-BUILDING, P-PASTURE, W-WATER, F-FIRE, i-Fireman, "
		"!-In Danger, *-Dynamited\n\n");

	//Se recorre la city.
	for(i = 0; i < level; i++){
		for(k = 0; k < level; k++){

			//Si las coordenadas del Ground son las mismas que las del Fireman
			//se concatena una B.
			if(k == x && i == y){
				strcpy(desc, " i");
			}else{
				strcpy(desc, " ");
			}

			//Se concatena la letra correspondiente al type de Ground
			//y se enciende el color que le corresponde.
			if(city[i][k].type == BUILDING){

				strcat(desc, "B");
				attron(COLOR_PAIR(4));

			}else if(city[i][k].type == PASTURE){

				strcat(desc, "P");
				attron(COLOR_PAIR(2));

			}else if(city[i][k].type == FIRE){

				strcat(desc, "F");
				attron(COLOR_PAIR(1));

			}else if(city[i][k].type == WATER){

				strcat(desc, "W");
				attron(COLOR_PAIR(3));

			}

			//Además, si el Ground ya está dinamitado, se concatena el asterisco.
			if(city[i][k].isDynamited){
				strcat(desc, "*");
			}

			//Misma lógica que arriba.
			if(city[i][k].isInDanger){
				strcat(desc, "!");
			}

			//Se concatena un tab al final para darle espacio al Ground
			//(por eso se ven rectangulares, con los caracteres del lado izquierdo).
			strcat(desc, "\t");

			//Los Grounds de arriba tienen las letras negras.

			//El Ground en el que se encuentra el Fireman tiene letras moradas.
			if(desc[1] == 'i'){

				if(city[i][k].type == BUILDING){
					attron(COLOR_PAIR(9));
				}

				if(city[i][k].type == PASTURE){
					attron(COLOR_PAIR(7));
				}

				if(city[i][k].type == FIRE){
					attron(COLOR_PAIR(6));
				}

				if(city[i][k].type == WATER){
					attron(COLOR_PAIR(8));
				}

			}

			//El Ground que está en peligro tiene letras amarillas.
			if(desc[2] == '!'){

				if(city[i][k].type == BUILDING){
					attron(COLOR_PAIR(13));
				}

				if(city[i][k].type == PASTURE){
					attron(COLOR_PAIR(11));
				}

				if(city[i][k].type == FIRE){
					attron(COLOR_PAIR(10));
				}

				if(city[i][k].type == WATER){
					attron(COLOR_PAIR(12));
				}

			}

			//Se imprime la cadena.
			printw("%s", desc);

			//Se termina el color de este Ground.
			//Así funciona esto: prendes colores de un Ground, coloreas, apagas
			//y vuelves a empezar con el Ground siguiente.
			stopColors();

		}
		printw("\n\n\n");
	}

}

void showPosInfo(Ground city[][10], int y, int x, int turn, int turns, int dynamites){

	char type[10];

	if(city[y][x].type == FIRE){
		strcpy(type, "FIRE");
	}else if(city[y][x].type == WATER){
		strcpy(type, "WATER");
	}else if(city[y][x].type == PASTURE){
		strcpy(type, "PASTURE");
	}else if(city[y][x].type == BUILDING){
		strcpy(type, "BUILDING");
	}

	printw("Current position: %s\t", type);
	printw("Coordinates: X=%d, Y=%d\n", x, y);
	printw("Dynamited: %s\t\t\t", city[y][x].isDynamited ? "Yes" : "No");
	printw("In Danger: %s\n", city[y][x].isInDanger ? "Yes" : "No");
	printw("Dynamites: %d\t\t\t", dynamites);
	printw("Turn %d of %d\n", turn, turns);

}

//Se pide el movimiento deseado en el juego y se regresa al ciclo de este.
int actionMenu(){

	int opc;

	int x;
	int y;

	printw("\n[ 1 ] North\n[ 2 ] South\n[ 3 ] West\n[ 4 ] East\n"
		"[ 5 ] Dynamite\n[ 6 ] Stay here\n");

	printw("\nChoose an option: ");
	scanw("%d", &opc);

	getyx(stdscr, y, x);

	while(opc <= 0 || opc > 6){

		printw("\nInvalid option.\n");

		getch();
		move(y - 2, x);

		clrtobot();
		refresh();

		printw("\nChoose an option: ");
		scanw("%d", &opc);

	}

	return opc;

}