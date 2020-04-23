#pragma once

#include "player.h"
#include "fireman.h"

void prepararJuego(Jugador *j, Bombero *b, Terreno ciudad[][10]);
void iniciarJuego(Jugador *j, Bombero *b, Terreno ciudad[][10], Jugador js[], int *contJs);
void mostrarMapa(Terreno ciudad[][10], int nivel, int x, int y);
void mostrarInfoPosicion(Terreno ciudad[][10], int y, int x, int turno, int turnos, int dinamitas);
int menuAccion();