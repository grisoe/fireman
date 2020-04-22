#include <string.h>

#include "juego.h"
#include "colores.h"
#include "archivos.h"

//Sólo sirve para envolver a las otras tres funciones que preparan las cosas
//necesarias para jugar.
void prepararJuego(Jugador *j, Bombero *b, Terreno ciudad[][10]){

	clear();

	printw("---------------Preparar Juego---------------\n\n");

	prepararJugador(j);
	prepararBombero(b, j->nivel, j->turnos);
	prepararCiudad(ciudad, j->nivel, b->x, b->y);

	printw("\n¡Juego listo!");

	getch();
	refresh();

}

void iniciarJuego(Jugador *j, Bombero *b, Terreno ciudad[][10],
	Jugador js[], int *contJs){

	

	int turnos;
	//Opción elegida por el usuario.
	int opc;
	//Mientras intentes hacer cosas inválidas, esta variable se mantendrá en 0.
	//Esto es así para no perder un turno por el intento de movimiento ilegal.
	//Obviamente, cada movimiento válido pone esta bandera en 1, sacándote del
	//do-while y dantro otra vuelta en el ciclo for, que es el de los turnos.
	//Qué trucazo, ¿no?
	int band;
	int din = b->dinamitas;
	int incendios;

	//Ciclo principal del juego (cuando ya te estás moviendo y dinamitando).
	for(turnos = 1; turnos <= j->turnos; turnos++){

		//Cuando no hay incendios te sales del ciclo porque apagaste todos
		//y ya no hay nada que hacer.
		if(incendios == 0){
			break;
		}

		do{ //do-while ya mencionado.

			clear();

			attron(COLOR_PAIR(5));

			printw("---------------Juego Iniciado---------------");

			//Se actualiza el mapa y la información con cada vuelta, legal o ilegal.
			mostrarMapa(ciudad, j->nivel, b->x, b->y);
			mostrarInfoPosicion(ciudad, b->y, b->x, turnos, j->turnos, din);

			opc = menuAccion();

			switch(opc){

				//Las opciones del 1 al 4 son para moverse.
				//La dirección se pide en otra función.
				case 1:
				case 2:
				case 3:
				case 4:
					band = moverse(opc, b, j->nivel);

					break;

				//La opción 5 es para dinamitar.
				case 5:

					if(din > 0){ //Si te quedan, dinamitas.

						//Si puedo dinamitar, guardo un 1.
						band = dinamitar(b->x, b->y, j->nivel, ciudad);

						//Resta una dinamita sólo si logró dinamitar.
						if(band == 1){
							din--;
						}

					}else{
						printw("\nYa no tienes dinamitas.\n");
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
			incendios = numIncendios(ciudad, j->nivel);

		}while(band == 0);

		//Cada tercer turno se incendian los terrenos en peligro y se ponen
		//en peligro los adyacentes a estos nuevos fuegos.
		if(turnos % 3 == 0){
			incendiar(ciudad, j->nivel);
			setPeligro(ciudad, j->nivel);
		}

	}

	//De aquí y hasta el final de la función, se muestra el código ejecutado
	//al terminar un juego, independientemente de su estado.

	clear();

	printw("---------------Juego Iniciado---------------");
	
	mostrarMapa(ciudad, j->nivel, b->x, b->y);
	mostrarInfoPosicion(ciudad, b->y, b->x, turnos, j->turnos, din);
	
	//Si logras vencer al fuego se te felicita con mucho entusiasmo.
	if(incendios == 0){
		printw("\n¡Has acabado con todos los incendios!\n");
		//Los turnos tienen un offset positivo de 1, así que se lo resto aquí.
		j->turnos = turnos - 1;
	}

	//Si no acabaste con todos los incendios, se imprime un mensaje
	//diciendo que la lluvia jugó mejor que tú.
	if(incendios > 0){
		printw("\n¡Ha legado la lluvia!\n");
	}

	setPuntuacion(j, ciudad);
	printw("\nTu puntuación es: %d\n", j->puntuacion);

	//Se guarda el jugador en el arreglo y se incrementa el contador de jugadores.
	js[*contJs] = *j;
	(*contJs)++;

	//Se escribe la información del jugador en un archivo.
	escribirEnArchivo(js, *contJs);

	//No te deja salir del juego hasta que presiones la tecla "s".
	//Lo hice así para que no te salgas sin querer del juego por presionar
	//cualquier otra tecla. Uno puede querer quedarse un rato ahí viendo su puntuación.
	//noecho() es para que no muestre las teclas presionadas.
	printw("\nPresiona la tecla 's' para continuar...");
	noecho();
	while(getch() != 's');
	echo();

	refresh();

}

//Muestra la información de cabecera y el mapa coloreado del juego.
//Los parámetros "x" y "y" son las coordenadas del bombero.
void mostrarMapa(Terreno ciudad[][10], int nivel, int x, int y){

	//Para guardar los caracteres a mostrarse en cada terreno.
	char desc[5];

	int i;
	int k;

	printw("\n\nE-Edificio, P-Pastizal, A-Agua, F-Fuego, B-Bombero, "
		"!-En peligro, *-Dinamitado\n\n");

	//Se recorre la ciudad.
	for(i = 0; i < nivel; i++){
		for(k = 0; k < nivel; k++){

			//Si las coordenadas del terreno son las mismas que las del bombero
			//se concatena una B.
			if(k == x && i == y){
				strcpy(desc, " B");
			}else{
				strcpy(desc, " ");
			}

			//Se concatena la letra correspondiente al tipo de terreno
			//y se enciende el color que le corresponde.
			if(ciudad[i][k].tipo == EDIFICIO){

				strcat(desc, "E");
				attron(COLOR_PAIR(4));

			}else if(ciudad[i][k].tipo == PASTIZAL){

				strcat(desc, "P");
				attron(COLOR_PAIR(2));

			}else if(ciudad[i][k].tipo == FUEGO){

				strcat(desc, "F");
				attron(COLOR_PAIR(1));

			}else if(ciudad[i][k].tipo == AGUA){

				strcat(desc, "A");
				attron(COLOR_PAIR(3));

			}

			//Además, si el terreno ya está dinamitado, se concatena el asterisco.
			if(ciudad[i][k].dinamitado){
				strcat(desc, "*");
			}

			//Misma lógica que arriba.
			if(ciudad[i][k].enPeligro){
				strcat(desc, "!");
			}

			//Se concatena un tab al final para darle espacio al terreno
			//(por eso se ven rectangulares, con los caracteres del lado izquierdo).
			strcat(desc, "\t");

			//Los terrenos de arriba tienen las letras negras.

			//El terreno en el que se encuentra el bombero tiene letras moradas.
			if(desc[1] == 'B'){

				if(ciudad[i][k].tipo == EDIFICIO){
					attron(COLOR_PAIR(9));
				}

				if(ciudad[i][k].tipo == PASTIZAL){
					attron(COLOR_PAIR(7));
				}

				if(ciudad[i][k].tipo == FUEGO){
					attron(COLOR_PAIR(6));
				}

				if(ciudad[i][k].tipo == AGUA){
					attron(COLOR_PAIR(8));
				}

			}

			//El terreno que está en peligro tiene letras amarillas.
			if(desc[2] == '!'){

				if(ciudad[i][k].tipo == EDIFICIO){
					attron(COLOR_PAIR(13));
				}

				if(ciudad[i][k].tipo == PASTIZAL){
					attron(COLOR_PAIR(11));
				}

				if(ciudad[i][k].tipo == FUEGO){
					attron(COLOR_PAIR(10));
				}

				if(ciudad[i][k].tipo == AGUA){
					attron(COLOR_PAIR(12));
				}

			}

			//Se imprime la cadena.
			printw("%s", desc);

			//Se termina el color de este terreno.
			//Así funciona esto: prendes colores de un terreno, coloreas, apagas
			//y vuelves a empezar con el terreno siguiente.
			terminarColores();

		}
		printw("\n\n\n");
	}

}

void mostrarInfoPosicion(Terreno ciudad[][10], int y, int x, int turno,
	int turnos, int dinamitas){

	char tipo[10];

	if(ciudad[y][x].tipo == FUEGO){
		strcpy(tipo, "Fuego");
	}else if(ciudad[y][x].tipo == AGUA){
		strcpy(tipo, "Agua");
	}else if(ciudad[y][x].tipo == PASTIZAL){
		strcpy(tipo, "Pastizal");
	}else if(ciudad[y][x].tipo == EDIFICIO){
		strcpy(tipo, "Edificio");
	}

	printw("Se encuentra en: %s\t", tipo);
	printw("En coordenadas: X=%d, Y=%d\n", x, y);
	printw("Dinamitado: %s\t\t\t", ciudad[y][x].dinamitado ? "Sí" : "No");
	printw("En peligro: %s\n", ciudad[y][x].enPeligro ? "Sí" : "No");
	printw("Dinamitas: %d\t\t\t", dinamitas);
	printw("Turno %d de %d\n", turno, turnos);

}

//Se pide el movimiento deseado en el juego y se regresa al ciclo de este.
int menuAccion(){

	int opc;

	int x;
	int y;

	printw("\n[ 1 ] Norte\n[ 2 ] Sur\n[ 3 ] Oste\n[ 4 ] Este\n"
		"[ 5 ] Dinamitar\n[ 6 ] Mantenerse aquí\n");

	printw("\nElige la opción deseada: ");
	scanw("%d", &opc);

	getyx(stdscr, y, x);

	while(opc <= 0 || opc > 6){

		printw("\nOpción inválida.\n");

		getch();
		move(y - 2, x);

		clrtobot();
		refresh();

		printw("\nElige la opción deseada: ");
		scanw("%d", &opc);

	}

	return opc;

}