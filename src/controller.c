#include "headers/controller.h"

int main(){

	//Se explica en su definición.
	createRecords();

	Fireman b;
	Player j;

	//De 10x10 porque es lo máximo que puede medir la city.
	Ground city[10][10];

	//Este arreglo es para guardar a todos los Playeres de una sola ejecución
	//del programa. 100 posiciones por si es algún traumado (como los que juegan Solitario).
	Player js[100];
	//Contador de los Playeres almacenados en el arreglo.
	int numJs = 0;

	//Nos dice si ya se preparó un juego o no.
	//bool no es un tipo de dato nativo de C, está definido en ncurses,
	//al igual que sus posibles valores (TRUE y FALSE).
	bool isReady = FALSE;

	//Para almacenar la opción del menú principal.
	int menu;

	//Se le da a srand el del sistema en segundos para que inicie la generación de
	//números aleatorios.
	//En Linux, ejecutar los comandos "man 2 time" y "man srand" para leer más.
	srand(time(NULL));

	initscr();

	//Explicada en su definición.
	startColors();

	//No recuerdo para que es esta línea; la comento y todo funciona igual.
	//Tal vez fue para resolver un problema específico de cierta terminal.
	//UPDATE: creo que es para hacer scroll automático a la pantalla cuando
	//esta se llena de información.
	scrollok(stdscr, TRUE);

	FILE *fd;

	//Es el ciclo principal del programa.
	do{

		//attron() es una función de ncurses para iniciar atributos de la ventana.
		//COLOR_PAIR() es el atributo que inicia colores, su argumento es el número de un
		//par de estos. En la definición de iniciarColores() explico este número.
		attron(COLOR_PAIR(5));

		menu = mainMenu();

		switch(menu){

			case 1: //Preparar juego.

				if(isReady){
					printw("\nYa hay un juego listo para jugarse.");
					getch();
					refresh();
				}else{
					//Preparar un juego se divide en la preparación del Player,
					//del bombero y de la city.
					setGame(&j, &b, city);
					//Ya se preparó.
					isReady = TRUE;
				}

				break;

			case 2: //Iniciar juego.

				if(isReady){
					//Para iniciar el juego se necesita de un Player, un bombero,
					//una city, el arreglo de Playeres (para guardar al que va a jugar),
					//y el contador de Playeres en el arreglo (para incrementarlo).
					startGame(&j, &b, city, js, &numJs);
					//Ya se jugó, por lo tanto no hay juego isReady.
					isReady = FALSE;
				}else{
					printw("\nPrimero tienes que preparar un juego.");
					getch();
					refresh();
				}

				break;

			case 3: //Consultas.

				fd = openRecords(0);

				fseek(fd, 0, SEEK_END);

				if(ftell(fd) / sizeof(Player) == 0){

					printw("\nNo hay registro alguno.");

					fclose(fd);

					getch();
					refresh();

				}else{

					fclose(fd);

					//El par de colores 5 es fondo negro con letras blancas.
					//Se hace así para una mejor lectura de puntuación.		
					attron(COLOR_PAIR(5));
					queries();

				}

				break;

			case 4:
				printw("\nSaliendo...");
				break;

			default:

				printw("\nOpción inválida. Intente nuevamente...");
				getch();
				refresh();

				break;

		}

	}while(menu != 4);

	getch();
	refresh();

	endwin();

}

//Para pedir y regresar la opción deseada del menú principal.
int mainMenu(){

	clear();

	printw("---------------Menu Principal---------------\n\n");

	int opc;

	printw("[ 1 ] Preparar Juego\n[ 2 ] Iniciar Juego\n"
		"[ 3 ] Consultas\n[ 4 ] Salir\n");

	printw("\nElige la opción deseada: ");
	scanw("%d", &opc);

	return opc;

}