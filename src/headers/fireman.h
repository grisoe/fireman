#pragma once

#include "city.h"

typedef struct Bombero{
	int dinamitas;
	int x;
	int y;
} Bombero;

void prepararBombero(Bombero *b, int nivel, int turnos);
int moverse(int direccion, Bombero *b, int nivel);
int dinamitar(int x, int y, int nivel, Terreno ciudad[][10]);