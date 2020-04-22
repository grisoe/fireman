#include <string.h>

#include "consultas.h"
#include "archivos.h"

//Aquí está el loop principal de la opción Consultas.
void consultas()
{

	int menu;

	do
	{

		//Se pide el tipo de consulta.
		menu = menuConsultas();

		switch (menu)
		{

		case 1:
			consultarTodos();
			break;

		case 2:
			consultarNivel();
			break;

		case 3:
			consultarPuntuacion();
			break;

		case 4:
			consultarJugador();
			break;

		case 5: //El 5 es la opción para regresar a la pantalla enterior.
			return;

		default:

			printw("\nOpción inválida.");

			getch();
			refresh();

			break;
		}

	} while (menu != 5);

	getch();
	refresh();
}

//Se pide el tipo de consulta.
int menuConsultas()
{

	int opc;

	clear();

	printw("---------------Menú de Consultas---------------\n\n");

	printw("[ 1 ] Todos los juegos\n[ 2 ] Por nivel de dificultad específico\n"
		   "[ 3 ] Ordenados por puntuación\n[ 4 ] Por jugador específico\n"
		   "[ 5 ] Regresar\n");

	printw("\nElige la opción deseada: ");
	scanw("%d", &opc);

	return opc;
}

void consultarTodos()
{

	clear();

	printw("---------------Todos los Juegos---------------\n\n");

	//Se abre el archivo en modo lectura.
	FILE *fd = abrirArchivo(0);

	//Para almacenar al objeto que se va leyendo.
	Jugador jug;

	//Se van leyendo objetos del archivo, de uno por uno; se guarda en jug hasta
	//que se lea algo sin tamaño (pasa esto cuando ya no hay nada que leer).
	while (fread(&jug, sizeof(Jugador), 1, fd) > 0)
	{

		printw("Jugador: %s\nPuntuación: %d\nNivel: %d\nTurnos jugados: %d\n\n",
			   jug.nombre, jug.puntuacion, jug.nivel, jug.turnos);
	}

	//Se cierra el archivo.
	fclose(fd);

	getch();
	refresh();
}

void consultarNivel()
{

	clear();

	printw("---------------Por Nivel de Dificultad Específico---------------\n\n");

	int nivel;
	//Si se encuentra por lo menos un jugador con el nivel deseado, se vuelve FALSE.
	//Sólo se usa para mostrar o no un mensaje que diga que no hay jugador con ese nivel.
	bool flag = TRUE;

	printw("Ingresa el nivel de dificultad (3-10): ");
	scanw("%d", &nivel);
	while (nivel < 3 || nivel > 10)
	{

		printw("\nLos niveles de dificultad están entre 3 y 10.\n\n");

		printw("Ingresa el nivel de dificultad (3-10): ");
		scanw("%d", &nivel);
	}

	//Se abre el archivo en modo lectura.
	FILE *fd = abrirArchivo(0);

	Jugador jug;

	while (fread(&jug, sizeof(Jugador), 1, fd) > 0)
	{

		//Si el nivel del jugador actual es igual al buscado por el usuario...
		if (jug.nivel == nivel)
		{

			//Pues se imprime el jugador, duhhh.
			printw("\nJugador: %s\nPuntuación: %d\nNivel: %d\nTurnos jugados: %d\n",
				   jug.nombre, jug.puntuacion, jug.nivel, jug.turnos);

			//FALSE pa' mostrar un mensaje bonito al final.
			flag = FALSE;
		}
	}

	fclose(fd);

	if (flag)
	{
		printw("\nNo hay registros para ese nivel específico.");
	}

	getch();
	refresh();
}

void consultarPuntuacion(){

	clear();

	printw("---------------Ordenados por Puntuación---------------\n\n");

	FILE *fd = abrirArchivo(2);

	//Para guardar el jugador leído.
	Jugador jug;
	Jugador jug2;
	Jugador aux;	
	
	fseek(fd, 0, SEEK_END);

	int s = ftell(fd) / sizeof(Jugador);	

	rewind(fd);

	int i;
	int k;

	//Bubble sort porque soy n00b.
	for (i = 1; i < s; i++){
		for (k = 0; k < s - i; k++){

			fseek(fd, k * sizeof(Jugador), SEEK_SET);
			fread(&jug, sizeof(Jugador), 1, fd);

			fseek(fd, (k + 1) * sizeof(Jugador), SEEK_SET);
			fread(&jug2, sizeof(Jugador), 1, fd);

			if (jug.puntuacion < jug2.puntuacion){

				aux = jug;
				jug = jug2;
				jug2 = aux;

				fseek(fd, k * sizeof(Jugador), SEEK_SET);
				fwrite(&jug, sizeof(Jugador), 1, fd);

				fseek(fd, (k + 1) * sizeof(Jugador), SEEK_SET);
				fwrite(&jug2, sizeof(Jugador), 1, fd);

			}
			
		}
	}

	rewind(fd);

	//Se van leyendo objetos del archivo, de uno por uno; se guarda en jug hasta
	//que se lea algo sin tamaño (pasa esto cuando ya no hay nada que leer).
	while (fread(&jug, sizeof(Jugador), 1, fd) > 0){

		printw("Jugador: %s\nPuntuación: %d\nNivel: %d\nTurnos jugados: %d\n\n",
			jug.nombre, jug.puntuacion, jug.nivel, jug.turnos);

	}

	//Se cierra el archivo.
	fclose(fd);

	getch();
	refresh();

}

//Igual que consultarNivel() pero ahora se comparan los nombres.
void consultarJugador()
{

	clear();

	printw("---------------Por Jugador Específico---------------\n\n");

	char nombre[50];
	bool flag = TRUE;

	printw("Ingresa el nombre del jugador: ");
	scanw("%[^\n]", nombre);

	FILE *fd = abrirArchivo(0);

	Jugador jug;

	while (fread(&jug, sizeof(Jugador), 1, fd) > 0)
	{

		if (strcmp(jug.nombre, nombre) == 0)
		{

			printw("\nJugador: %s\nPuntuación: %d\nNivel: %d\nTurnos jugados: %d\n",
				   jug.nombre, jug.puntuacion, jug.nivel, jug.turnos);

			flag = FALSE;
		}
	}

	fclose(fd);

	if (flag)
	{
		printw("\nNo hay registros para ese jugador específico.");
	}

	getch();
	refresh();
}