#pragma once

#include "player.h"

char *rutaArchivo();
void crearArchivo();
FILE* abrirArchivo(int modo);
void escribirEnArchivo(Jugador *js, int contJs);