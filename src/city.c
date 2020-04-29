#include <stdlib.h>

#include "headers/city.h"

void buildCity(Ground city[][10], int level, int x, int y){

	int ran;
	int ran2;

	int i;
	int k;

	//Se recorre la matriz (city) para asignarle a cada Ground un type,
	//ponerlo como no dinamitado y sin peligro.
	for (i = 0; i < level; i++){
		for (k = 0; k < level; k++){

			city[i][k].type = 2 + rand() % 2;
			city[i][k].isDynamited = FALSE;
			city[i][k].isInDanger = FALSE;

		}
	}

	//El primer FIRE no debe aparecer en donde aparece el bombero.
	//Voy creando coordenadas aleatorias para el primero FIRE, hasta que estas
	//no sean las mismas del bombero.
	do{

		ran = rand() % level;
		ran2 = rand() % level;

	} while (ran == y && ran2 == x);

	//Asigno el FIRE a la city y el type BUILDING al lugar del bombero.
	city[ran][ran2].type = FIRE;
	city[y][x].type = BUILDING;

	setDanger(city, level);

}

//Se ponen en peligro los Grounds a los lados de un FIRE.
void setDanger(Ground city[][10], int level){

	int i;
	int k;

	//Con "si existe" me refiero a que la coordenada no esté fuera de la city.

	//Se recorre la city.
	for (i = 0; i < level; i++){
		for (k = 0; k < level; k++){

			//Si se encuentra un FIRE...
			if (city[i][k].type == FIRE){

				//y el Ground de la izquierda existe, no es de WATER ni de FIRE...
				if ((i - 1 >= 0) && (city[i - 1][k].type != WATER) 
					&& (city[i - 1][k].type != FIRE)){
					//se pone en peligro.
					city[i - 1][k].isInDanger = TRUE;
				}

				//y el Ground de la derecha existe, no es de WATER ni de FIRE...
				if ((i + 1 <= level - 1) && (city[i + 1][k].type != WATER) 
					&& (city[i + 1][k].type != FIRE)){
					//se pone en peligro.
					city[i + 1][k].isInDanger = TRUE;
				}

				//y el Ground de abajo existe, no es de WATER ni de FIRE...
				if ((k + 1 <= level - 1) && (city[i][k + 1].type != WATER) 
					&& (city[i][k + 1].type != FIRE)){
					//se pone en peligro.
					city[i][k + 1].isInDanger = TRUE;
				}

				//y el Ground de arriba existe, no es de WATER ni de FIRE...
				if ((k - 1 >= 0) && (city[i][k - 1].type != WATER) 
					&& (city[i][k - 1].type != FIRE)){
					//se pone en peligro.
					city[i][k - 1].isInDanger = TRUE;
				}

			}

		}
	}

}

//Para incendiar los Grounds.
void burnDown(Ground city[][10], int level){

	int i;
	int k;

	for (i = 0; i < level; i++){
		for (k = 0; k < level; k++){

			//Si el Ground está en peligro...
			if (city[i][k].isInDanger){

				//Ya no está en peligro, ¡ES EL PELIGRO!
				city[i][k].isInDanger = FALSE;
				city[i][k].type = FIRE;

			}

		}
	}

}

int getNumFires(Ground city[][10], int level){

	int i;
	int k;
	int n = 0;

	for (i = 0; i < level; i++){
		for (k = 0; k < level; k++){

			if (city[i][k].type == FIRE){
				n++;
			}

		}
	}

	return n;
	
}

//Cuando un Ground type FIRE se dinamita, se debe tener en cuenta que los
//Grounds a su alrededor pueden estar en peligro no solo por él, sino por otros
//FIREs vecinos, así que debe validarse eso para no quitar el peligro de un
//Ground que deba seguir estando amenazado aun dinamitando un FIRE.
void setDangerMult(int x, int y, int level, Ground city[][10]){

	//Norte.
	//Si hay un Ground arriba del FIRE, a este de arriba se le quita el peligro.
	if (y - 1 >= 0)
	{
		city[y - 1][x].isInDanger = FALSE;
	}

	//Si hay dos Grounds arriba del FIRE...
	if (y - 2 >= 0)
	{

		//y el de hasta arriba también es FIRE...
		if (city[y - 2][x].type == FIRE)
		{

			//y el del centro no es FIRE ni WATER...
			if (city[y - 1][x].type != FIRE && city[y - 1][x].type != WATER)
			{
				//el del centro se pone en peligro.
				city[y - 1][x].isInDanger = TRUE;
			}
		}
	}

	//Misma lógica pero en diferente dirección de aquí hasta el final de la función.

	//Sur.
	if (y + 1 <= level - 1)
	{
		city[y + 1][x].isInDanger = FALSE;
	}

	if (y + 2 <= level - 1)
	{

		if (city[y + 2][x].type == FIRE)
		{

			if (city[y + 1][x].type != FIRE && city[y + 1][x].type != WATER)
			{
				city[y + 1][x].isInDanger = TRUE;
			}
		}
	}

	//Este.
	if (x + 1 <= level - 1)
	{
		city[y][x + 1].isInDanger = FALSE;
	}

	if (x + 2 <= level - 1)
	{

		if (city[y][x + 2].type == FIRE)
		{

			if (city[y][x + 1].type != FIRE && city[y][x + 1].type != WATER)
			{
				city[y][x + 1].isInDanger = TRUE;
			}
		}
	}

	//Oeste
	if (x - 1 >= 0)
	{
		city[y][x - 1].isInDanger = FALSE;
	}

	if (x - 2 >= 0)
	{

		if (city[y][x - 2].type == FIRE)
		{

			if (city[y][x - 1].type != FIRE && city[y][x - 1].type != WATER)
			{
				city[y][x - 1].isInDanger = TRUE;
			}
		}
	}

	//Noroeste.
	if (y - 1 >= 0 && x - 1 >= 0)
	{

		if (city[y - 1][x - 1].type == FIRE)
		{

			if (city[y - 1][x].type != WATER && city[y - 1][x].type != FIRE)
			{
				city[y - 1][x].isInDanger = TRUE;
			}

			if (city[y][x - 1].type != WATER && city[y][x - 1].type != FIRE)
			{
				city[y][x - 1].isInDanger = TRUE;
			}
		}
	}

	//Noreste.
	if (y - 1 >= 0 && x + 1 <= level - 1)
	{

		if (city[y - 1][x + 1].type == FIRE)
		{

			if (city[y - 1][x].type != WATER && city[y - 1][x].type != FIRE)
			{
				city[y - 1][x].isInDanger = TRUE;
			}

			if (city[y][x + 1].type != WATER && city[y][x + 1].type != FIRE)
			{
				city[y][x + 1].isInDanger = TRUE;
			}
		}
	}

	//Sureste.
	if (y + 1 <= level - 1 && x + 1 <= level - 1)
	{

		if (city[y + 1][x + 1].type == FIRE)
		{

			if (city[y + 1][x].type != WATER && city[y + 1][x].type != FIRE)
			{
				city[y + 1][x].isInDanger = TRUE;
			}

			if (city[y][x + 1].type != WATER && city[y][x + 1].type != FIRE)
			{
				city[y][x + 1].isInDanger = TRUE;
			}
		}
	}

	//Suroeste.
	if (y + 1 <= level - 1 && x - 1 >= 0)
	{

		if (city[y + 1][x - 1].type == FIRE)
		{

			if (city[y + 1][x].type != WATER && city[y + 1][x].type != FIRE)
			{
				city[y + 1][x].isInDanger = TRUE;
			}

			if (city[y][x - 1].type != WATER && city[y][x - 1].type != FIRE)
			{
				city[y][x - 1].isInDanger = TRUE;
			}
		}
	}
}