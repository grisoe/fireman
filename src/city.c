#include <stdlib.h>

#include "headers/city.h"

void prepararCiudad(Terreno ciudad[][10], int nivel, int x, int y){

	int r;
	int r2;

	int i;
	int k;

	//Se recorre la matriz (ciudad) para asignarle a cada terreno un tipo,
	//ponerlo como no dinamitado y sin peligro.
	for (i = 0; i < nivel; i++){
		for (k = 0; k < nivel; k++){

			ciudad[i][k].tipo = 2 + rand() % 2;
			ciudad[i][k].dinamitado = FALSE;
			ciudad[i][k].enPeligro = FALSE;

		}
	}

	//El primer fuego no debe aparecer en donde aparece el bombero.
	//Voy creando coordenadas aleatorias para el primero fuego, hasta que estas
	//no sean las mismas del bombero.
	do{

		r = rand() % nivel;
		r2 = rand() % nivel;

	} while (r == y && r2 == x);

	//Asigno el fuego a la ciudad y el tipo edificio al lugar del bombero.
	ciudad[r][r2].tipo = FUEGO;
	ciudad[y][x].tipo = EDIFICIO;

	setPeligro(ciudad, nivel);

}

//Se ponen en peligro los terrenos a los lados de un fuego.
void setPeligro(Terreno ciudad[][10], int nivel){

	int i;
	int k;

	//Con "si existe" me refiero a que la coordenada no esté fuera de la ciudad.

	//Se recorre la ciudad.
	for (i = 0; i < nivel; i++){
		for (k = 0; k < nivel; k++){

			//Si se encuentra un fuego...
			if (ciudad[i][k].tipo == FUEGO){

				//y el terreno de la izquierda existe, no es de agua ni de fuego...
				if ((i - 1 >= 0) && (ciudad[i - 1][k].tipo != AGUA) 
					&& (ciudad[i - 1][k].tipo != FUEGO)){
					//se pone en peligro.
					ciudad[i - 1][k].enPeligro = TRUE;
				}

				//y el terreno de la derecha existe, no es de agua ni de fuego...
				if ((i + 1 <= nivel - 1) && (ciudad[i + 1][k].tipo != AGUA) 
					&& (ciudad[i + 1][k].tipo != FUEGO)){
					//se pone en peligro.
					ciudad[i + 1][k].enPeligro = TRUE;
				}

				//y el terreno de abajo existe, no es de agua ni de fuego...
				if ((k + 1 <= nivel - 1) && (ciudad[i][k + 1].tipo != AGUA) 
					&& (ciudad[i][k + 1].tipo != FUEGO)){
					//se pone en peligro.
					ciudad[i][k + 1].enPeligro = TRUE;
				}

				//y el terreno de arriba existe, no es de agua ni de fuego...
				if ((k - 1 >= 0) && (ciudad[i][k - 1].tipo != AGUA) 
					&& (ciudad[i][k - 1].tipo != FUEGO)){
					//se pone en peligro.
					ciudad[i][k - 1].enPeligro = TRUE;
				}

			}

		}
	}

}

//Para incendiar los terrenos.
void incendiar(Terreno ciudad[][10], int nivel){

	int i;
	int k;

	for (i = 0; i < nivel; i++){
		for (k = 0; k < nivel; k++){

			//Si el terreno está en peligro...
			if (ciudad[i][k].enPeligro){

				//Ya no está en peligro, ¡ES EL PELIGRO!
				ciudad[i][k].enPeligro = FALSE;
				ciudad[i][k].tipo = FUEGO;

			}

		}
	}

}

int numIncendios(Terreno ciudad[][10], int nivel){

	int i;
	int k;
	int n = 0;

	for (i = 0; i < nivel; i++){
		for (k = 0; k < nivel; k++){

			if (ciudad[i][k].tipo == FUEGO){
				n++;
			}

		}
	}

	return n;
	
}

//Cuando un terreno tipo fuego se dinamita, se debe tener en cuenta que los
//terrenos a su alrededor pueden estar en peligro no solo por él, sino por otros
//fuegos vecinos, así que debe validarse eso para no quitar el peligro de un
//terreno que deba seguir estando amenazado aun dinamitando un fuego.
void setPeligroMult(int x, int y, int nivel, Terreno ciudad[][10])
{

	//Norte.
	//Si hay un terreno arriba del fuego, a este de arriba se le quita el peligro.
	if (y - 1 >= 0)
	{
		ciudad[y - 1][x].enPeligro = FALSE;
	}

	//Si hay dos terrenos arriba del fuego...
	if (y - 2 >= 0)
	{

		//y el de hasta arriba también es fuego...
		if (ciudad[y - 2][x].tipo == FUEGO)
		{

			//y el del centro no es fuego ni agua...
			if (ciudad[y - 1][x].tipo != FUEGO && ciudad[y - 1][x].tipo != AGUA)
			{
				//el del centro se pone en peligro.
				ciudad[y - 1][x].enPeligro = TRUE;
			}
		}
	}

	//Misma lógica pero en diferente dirección de aquí hasta el final de la función.

	//Sur.
	if (y + 1 <= nivel - 1)
	{
		ciudad[y + 1][x].enPeligro = FALSE;
	}

	if (y + 2 <= nivel - 1)
	{

		if (ciudad[y + 2][x].tipo == FUEGO)
		{

			if (ciudad[y + 1][x].tipo != FUEGO && ciudad[y + 1][x].tipo != AGUA)
			{
				ciudad[y + 1][x].enPeligro = TRUE;
			}
		}
	}

	//Este.
	if (x + 1 <= nivel - 1)
	{
		ciudad[y][x + 1].enPeligro = FALSE;
	}

	if (x + 2 <= nivel - 1)
	{

		if (ciudad[y][x + 2].tipo == FUEGO)
		{

			if (ciudad[y][x + 1].tipo != FUEGO && ciudad[y][x + 1].tipo != AGUA)
			{
				ciudad[y][x + 1].enPeligro = TRUE;
			}
		}
	}

	//Oeste
	if (x - 1 >= 0)
	{
		ciudad[y][x - 1].enPeligro = FALSE;
	}

	if (x - 2 >= 0)
	{

		if (ciudad[y][x - 2].tipo == FUEGO)
		{

			if (ciudad[y][x - 1].tipo != FUEGO && ciudad[y][x - 1].tipo != AGUA)
			{
				ciudad[y][x - 1].enPeligro = TRUE;
			}
		}
	}

	//Noroeste.
	if (y - 1 >= 0 && x - 1 >= 0)
	{

		if (ciudad[y - 1][x - 1].tipo == FUEGO)
		{

			if (ciudad[y - 1][x].tipo != AGUA && ciudad[y - 1][x].tipo != FUEGO)
			{
				ciudad[y - 1][x].enPeligro = TRUE;
			}

			if (ciudad[y][x - 1].tipo != AGUA && ciudad[y][x - 1].tipo != FUEGO)
			{
				ciudad[y][x - 1].enPeligro = TRUE;
			}
		}
	}

	//Noreste.
	if (y - 1 >= 0 && x + 1 <= nivel - 1)
	{

		if (ciudad[y - 1][x + 1].tipo == FUEGO)
		{

			if (ciudad[y - 1][x].tipo != AGUA && ciudad[y - 1][x].tipo != FUEGO)
			{
				ciudad[y - 1][x].enPeligro = TRUE;
			}

			if (ciudad[y][x + 1].tipo != AGUA && ciudad[y][x + 1].tipo != FUEGO)
			{
				ciudad[y][x + 1].enPeligro = TRUE;
			}
		}
	}

	//Sureste.
	if (y + 1 <= nivel - 1 && x + 1 <= nivel - 1)
	{

		if (ciudad[y + 1][x + 1].tipo == FUEGO)
		{

			if (ciudad[y + 1][x].tipo != AGUA && ciudad[y + 1][x].tipo != FUEGO)
			{
				ciudad[y + 1][x].enPeligro = TRUE;
			}

			if (ciudad[y][x + 1].tipo != AGUA && ciudad[y][x + 1].tipo != FUEGO)
			{
				ciudad[y][x + 1].enPeligro = TRUE;
			}
		}
	}

	//Suroeste.
	if (y + 1 <= nivel - 1 && x - 1 >= 0)
	{

		if (ciudad[y + 1][x - 1].tipo == FUEGO)
		{

			if (ciudad[y + 1][x].tipo != AGUA && ciudad[y + 1][x].tipo != FUEGO)
			{
				ciudad[y + 1][x].enPeligro = TRUE;
			}

			if (ciudad[y][x - 1].tipo != AGUA && ciudad[y][x - 1].tipo != FUEGO)
			{
				ciudad[y][x - 1].enPeligro = TRUE;
			}
		}
	}
}