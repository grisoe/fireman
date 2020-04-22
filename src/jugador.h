#pragma once

#include "ciudad.h"

typedef struct Jugador{
	char nombre[50];
	int puntuacion;
	int nivel;
	int turnos;
} Jugador;

void prepararJugador(Jugador *j);
void setPuntuacion(Jugador *j, Terreno ciudad[][10]);