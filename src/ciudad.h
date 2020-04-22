#pragma once

#include <ncurses.h>

typedef enum{
	FUEGO, AGUA, PASTIZAL, EDIFICIO
} Tipo_terreno;

typedef struct Terreno{
	Tipo_terreno tipo;
	bool dinamitado;
	bool enPeligro;
} Terreno;

void prepararCiudad(Terreno ciudad[][10], int nivel, int x, int y);
void setPeligro(Terreno ciudad[][10], int nivel);
void incendiar(Terreno ciudad[][10], int nivel);
int numIncendios(Terreno ciudad[][10], int nivel);
void setPeligroMult(int x, int y, int nivel, Terreno ciudad[][10]);