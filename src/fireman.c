#include "headers/fireman.h"

void createFireman(Fireman *b, int level, int turns){

	int x;
	int y;

	//Definido en el pdf.
	b->dynamites = turns - 3;

	//Al level le resto uno porque, si se elige un 10, por ejemplo, 
	//las coordenadas irán del 0 al 9.
	printw("X coordinate of the fireman (0-%d): ", level - 1);
	scanw("%d", &x);
	while(x < 0 || x > level - 1){

		printw("\nX coordinate of the fireman must be between 0 and %d."
			"\n\n", level - 1);

		printw("X coordinate of the fireman (0-%d): ", level - 1);
		scanw("%d", &x);

	}
	b->x = x;

	printw("Y coordinate of the fireman (0-%d): ", level - 1);
	scanw("%d", &y);
	while(y < 0 || y > level - 1){

		printw("\nY coordinate of the fireman must be between 0 and %d."
			"\n\n", level - 1);

		printw("Y coordinate of the fireman (0-%d): ", level - 1);
		scanw("%d", &y);

	}
	b->y = y;

}


int moveFireman(int direction, Fireman *fireman, int level){

	if(direction == 1){ //Mover hacia arriba.

		//Pero sólo si se puede.
		if((fireman->y) - 1 >= 0){

			//Nueva coordenada del Fireman en esa dirección.
			(fireman->y)--;
			//El 1 le dice al juego que si pudiste moverte.
			return 1;

		}else{

			printw("\nYou can't run away from the city.");
			getch();
			refresh();

			//El 0 le dice al juego que no pudiste moverte.
			return 0;

		}

	}else if(direction == 2){ //Mover hacia abajo.

		if((fireman->y) + 1 < level){

			(fireman->y)++;
			return 1;

		}else{

			printw("\nYou can't run away from the city.");
			getch();
			refresh();

			return 0;

		}

	}else if(direction == 4){ //Mover hacia la derecha.

		if((fireman->x) + 1 < level){

			(fireman->x)++;
			return 1;

		}else{

			printw("\nYou can't run away from the city.");
			getch();
			refresh();

			return 0;

		}

	}else if(direction == 3){ //Mover hacia la izquierda.

		if((fireman->x) - 1 >= 0){

			(fireman->x)--;
			return 1;

		}else{

			printw("\nYou can't run away from the city.");
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

		printw("\nAlready dynamited.\n");
		getch();
		refresh();

	   	//El 0 le dice al juego que no pudiste dinamitar.
		return 0;

	}

}