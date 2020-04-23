#include "headers/bombero.h"

void prepararBombero(Bombero *b, int nivel, int turnos){

	int x;
	int y;

	//Definido en el pdf.
	b->dinamitas = turnos - 3;

	//Al nivel le resto uno porque, si se elige un 10, por ejemplo, 
	//las coordenadas irán del 0 al 9.
	printw("Ingresa la coordenada X del bombero (0-%d): ", nivel - 1);
	scanw("%d", &x);
	while(x < 0 || x > nivel - 1){

		printw("\nLa coordenada X del bombero debe estar entre 0 y %d."
			"\n\n", nivel - 1);

		printw("Ingresa la coordenada X del bombero (0-%d): ", nivel - 1);
		scanw("%d", &x);

	}
	b->x = x;

	printw("Ingresa la coordenada Y del bombero (0-%d): ", nivel - 1);
	scanw("%d", &y);
	while(y < 0 || y > nivel - 1){

		printw("\nLa coordenada Y del bombero debe estar entre 0 y %d."
			"\n\n", nivel - 1);

		printw("Ingresa la coordenada Y del bombero (0-%d): ", nivel - 1);
		scanw("%d", &y);

	}
	b->y = y;

}


int moverse(int direccion, Bombero *b, int nivel){

	if(direccion == 1){ //Mover hacia arriba.

		//Pero sólo si se puede.
		if((b->y) - 1 >= 0){

			//Nueva coordenada del bombero en esa dirección.
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

	}else if(direccion == 2){ //Mover hacia abajo.

		if((b->y) + 1 < nivel){

			(b->y)++;
			return 1;

		}else{

			printw("\nNo puedes huir de la ciudad.");
			getch();
			refresh();

			return 0;

		}

	}else if(direccion == 4){ //Mover hacia la derecha.

		if((b->x) + 1 < nivel){

			(b->x)++;
			return 1;

		}else{

			printw("\nNo puedes huir de la ciudad.");
			getch();
			refresh();

			return 0;

		}

	}else if(direccion == 3){ //Mover hacia la izquierda.

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
int dinamitar(int x, int y, int nivel, Terreno ciudad[][10]){

	// void setPeligroMult(int x, int y, int nivel, Terreno ciudad[][10]);

	//Sólo se puede dinamitar si no fue ya dinamitado.
	if(ciudad[y][x].dinamitado == FALSE){

		//Si se encuentra un fuego, deben considerarse los terrenos alrededor.
		if(ciudad[y][x].tipo == FUEGO){
			//Más información en la definición de la función.
			setPeligroMult(x, y, nivel, ciudad);
		}

		//Cuando un terreno se dinamita ya no está en peligro porque ahora hay agua.
		ciudad[y][x].dinamitado = TRUE;
		ciudad[y][x].enPeligro = FALSE;
		ciudad[y][x].tipo = AGUA;

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