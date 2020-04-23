#include <ncurses.h>

#include "headers/colores.h"

//Se crean los colores a usar en el juego.
void iniciarColores(){

	//Función de ncurses para decirle que vamos a usar colores.
	start_color();

	//Función de ncurses para crear y nombrar un par de colores:
	//El primer número es con el que identificamos al par,
	//sigue el color de los caracteres y el último es el del fondo.
	init_pair(1, COLOR_BLACK, COLOR_RED);
    init_pair(2, COLOR_BLACK, COLOR_GREEN);
    init_pair(3, COLOR_BLACK, COLOR_CYAN);
    init_pair(4, COLOR_BLACK, COLOR_WHITE);
    init_pair(5, COLOR_WHITE, COLOR_BLACK);

    init_pair(6, COLOR_MAGENTA, COLOR_RED);
    init_pair(7, COLOR_MAGENTA, COLOR_GREEN);
    init_pair(8, COLOR_MAGENTA, COLOR_CYAN);
    init_pair(9, COLOR_MAGENTA, COLOR_WHITE);

    init_pair(10, COLOR_YELLOW, COLOR_RED);
    init_pair(11, COLOR_YELLOW, COLOR_GREEN);
    init_pair(12, COLOR_YELLOW, COLOR_CYAN);
    init_pair(13, COLOR_YELLOW, COLOR_WHITE);

}

//Se apagan los atributos de los 13 colores.
void terminarColores(){

	int i;

	for(i = 1; i <= 13; i++){
		attroff(COLOR_PAIR(i));
	}

}