#include "headers/fireman.h"

void createFireman(Fireman *b, int level, int turns){

	int x;
	int y;

	//Definido en el pdf.
	b->dynamites = turns - 3;

	//Al level le resto uno porque, si se elige un 10, por ejemplo, 
	//las coordenadas irán del 0 al 9.
	printw("Ingresa la coordenada X del Fireman (0-%d): ", level - 1);
	scanw("%d", &x);
	while(x < 0 || x > level - 1){

		printw("\nLa coordenada X del Fireman debe estar entre 0 y %d."
			"\n\n", level - 1);

		printw("Ingresa la coordenada X del Fireman (0-%d): ", level - 1);
		scanw("%d", &x);

	}
	b->x = x;

	printw("Ingresa la coordenada Y del Fireman (0-%d): ", level - 1);
	scanw("%d", &y);
	while(y < 0 || y > level - 1){

		printw("\nLa coordenada Y del Fireman debe estar entre 0 y %d."
			"\n\n", level - 1);

		printw("Ingresa la coordenada Y del Fireman (0-%d): ", level - 1);
		scanw("%d", &y);

	}
	b->y = y;

}


int moveFireman(int direction, Fireman *b, int level){

	if(direction == 1){ //Mover hacia arriba.

		//Pero sólo si se puede.
		if((b->y) - 1 >= 0){

			//Nueva coordenada del Fireman en esa dirección.
			(b->y)--;
			//El 1 le dice al juego que si pudiste moverte.
			return 1;

		}else{

			printw("\nNo puedes huir de la ciudad.");
			getch();
			refresh();

			//El 0 le dice al juego que no pudiste moverte.
			return 0;

		}

	}else if(direction == 2){ //Mover hacia abajo.

		if((b->y) + 1 < level){

			(b->y)++;
			return 1;

		}else{

			printw("\nNo puedes huir de la ciudad.");
			getch();
			refresh();

			return 0;

		}

	}else if(direction == 4){ //Mover hacia la derecha.

		if((b->x) + 1 < level){

			(b->x)++;
			return 1;

		}else{

			printw("\nNo puedes huir de la ciudad.");
			getch();
			refresh();

			return 0;

		}

	}else if(direction == 3){ //Mover hacia la izquierda.

		if((b->x) - 1 >= 0){

			(b->x)--;
			return 1;

		}else{

			printw("\nNo puedes huir de la ciudad.");
			getch();
			refresh();

			return 0;

		}

	}

	//Nunca se alcanza esta línea, pero GCC me regaña si no la pongo.
	//Supongo que es así porque lo de arriba puede hacerse de mejor manera,
	//pero no me awito.
	return -1;

}

//Se dinamita el terreno de cierta coordenada.
int dynamite(int x, int y, int level, Ground city[][10]){

	// void setPeligroMult(int x, int y, int level, Terreno ciudad[][10]);

	//Sólo se puede dinamitar si no fue ya dinamitado.
	if(city[y][x].isDynamited == FALSE){

		//Si se encuentra un fuego, deben considerarse los terrenos alrededor.
		if(city[y][x].type == FIRE){
			//Más información en la definición de la función.
			setDangerMult(x, y, level, city);
		}

		//Cuando un terreno se dinamita ya no está en peligro porque ahora hay agua.
		city[y][x].isDynamited = TRUE;
		city[y][x].isInDanger = FALSE;
		city[y][x].type = WATER;

		//El 1 le dice al juego que si pudiste dinamitar.
		return 1;

	}else{

		printw("\nEste terreno ya está dinamitado.\n");
		getch();
		refresh();

	   	//El 0 le dice al juego que no pudiste dinamitar.
		return 0;

	}

}