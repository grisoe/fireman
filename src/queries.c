#include <string.h>

#include "headers/queries.h"
#include "headers/files.h"

//Aquí está el loop principal de la opción Consultas.
void queries()
{

	int menu;

	do
	{

		//Se pide el tipo de consulta.
		menu = queriesMenu();

		switch (menu)
		{

		case 1:
			queryAll();
			break;

		case 2:
			queryLevel();
			break;

		case 3:
			queryPoints();
			break;

		case 4:
			queryPlayer();
			break;

		case 5: //El 5 es la opción para regresar a la pantalla enterior.
			return;

		default:

			printw("\nInvalid option.");

			getch();
			refresh();

			break;
		}

	} while (menu != 5);

	getch();
	refresh();
}

//Se pide el tipo de consulta.
int queriesMenu()
{

	int opt;

	clear();

	printw("---------------Queries Menu---------------\n\n");

	printw("[ 1 ] All games\n[ 2 ] By difficulty level\n"
		   "[ 3 ] Ordered by points\n[ 4 ] By Player\n"
		   "[ 5 ] Return\n");

	printw("\nChoose an option: ");
	scanw("%d", &opt);

	return opt;
}

void queryAll()
{

	clear();

	printw("---------------All Games---------------\n\n");

	//Se abre el archivo en modo lectura.
	FILE *fd = openRecords(0);

	//Para almacenar al objeto que se va leyendo.
	Player p;

	//Se van leyendo objetos del archivo, de uno por uno; se guarda en jug hasta
	//que se lea algo sin tamaño (pasa esto cuando ya no hay nada que leer).
	while (fread(&p, sizeof(Player), 1, fd) > 0)
	{

		printw("Player: %s\nPoints: %d\nLevel: %d\nPlayed turns: %d\n\n",
			   p.name, p.points, p.level, p.turns);
	}

	//Se cierra el archivo.
	fclose(fd);

	getch();
	refresh();
}

void queryLevel()
{

	clear();

	printw("---------------By Difficulty Level---------------\n\n");

	int level;
	//Si se encuentra por lo menos un Player con el level deseado, se vuelve FALSE.
	//Sólo se usa para mostrar o no un mensaje que diga que no hay Player con ese level.
	bool flag = TRUE;

	printw("Difficulty level (3-10): ");
	scanw("%d", &level);
	while (level < 3 || level > 10)
	{

		printw("\nDifficulty level must be between 3 and 10.\n\n");

		printw("Difficulty level (3-10): ");
		scanw("%d", &level);
	}

	//Se abre el archivo en modo lectura.
	FILE *fd = openRecords(0);

	Player p;

	while (fread(&p, sizeof(Player), 1, fd) > 0)
	{

		//Si el level del Player actual es igual al buscado por el usuario...
		if (p.level == level)
		{

			//Pues se imprime el Player, duhhh.
			printw("\nPlayer: %s\nPoints: %d\nLevel: %d\nPlayed turns: %d\n",
				   p.name, p.points, p.level, p.turns);

			//FALSE pa' mostrar un mensaje bonito al final.
			flag = FALSE;
		}
	}

	fclose(fd);

	if (flag)
	{
		printw("\nNo records for this level.");
	}

	getch();
	refresh();
}

void queryPoints(){

	clear();

	printw("---------------Ordered by Points---------------\n\n");

	FILE *fd = openRecords(2);

	//Para guardar el Player leído.
	Player p;
	Player p2;
	Player aux;	
	
	fseek(fd, 0, SEEK_END);

	int s = ftell(fd) / sizeof(Player);	

	rewind(fd);

	int i;
	int k;

	//Bubble sort porque soy n00b.
	for (i = 1; i < s; i++){
		for (k = 0; k < s - i; k++){

			fseek(fd, k * sizeof(Player), SEEK_SET);
			fread(&p, sizeof(Player), 1, fd);

			fseek(fd, (k + 1) * sizeof(Player), SEEK_SET);
			fread(&p2, sizeof(Player), 1, fd);

			if (p.points < p2.points){

				aux = p;
				p = p2;
				p2 = aux;

				fseek(fd, k * sizeof(Player), SEEK_SET);
				fwrite(&p, sizeof(Player), 1, fd);

				fseek(fd, (k + 1) * sizeof(Player), SEEK_SET);
				fwrite(&p2, sizeof(Player), 1, fd);

			}
			
		}
	}

	rewind(fd);

	//Se van leyendo objetos del archivo, de uno por uno; se guarda en jug hasta
	//que se lea algo sin tamaño (pasa esto cuando ya no hay nada que leer).
	while (fread(&p, sizeof(Player), 1, fd) > 0){

		printw("Player: %s\nPoints: %d\nLevel: %d\nPlayed turns: %d\n\n",
			p.name, p.points, p.level, p.turns);

	}

	//Se cierra el archivo.
	fclose(fd);

	getch();
	refresh();

}

//Igual que consultarlevel() pero ahora se comparan los names.
void queryPlayer()
{

	clear();

	printw("---------------By Player---------------\n\n");

	char name[50];
	bool flag = TRUE;

	printw("Name: ");
	scanw("%[^\n]", name);

	FILE *fd = openRecords(0);

	Player p;

	while (fread(&p, sizeof(Player), 1, fd) > 0)
	{

		if (strcmp(p.name, name) == 0)
		{

			printw("\nPlayer: %s\nPoints: %d\nLevel: %d\nPlayed turns: %d\n",
				   p.name, p.points, p.level, p.turns);

			flag = FALSE;
		}
	}

	fclose(fd);

	if (flag)
	{
		printw("\nNo records for this player.");
	}

	getch();
	refresh();
}