#pragma once

#include <ncurses.h>

typedef enum{
	FIRE, WATER, PASTURE, BUILDING
} Ground_type;

typedef struct Ground{
	Ground_type tipo;
	bool dinamitado;
	bool enPeligro;
} Ground;

/* void prepararCiudad(Ground ciudad[][10], int nivel, int x, int y);
void setPeligro(Ground ciudad[][10], int nivel);
void incendiar(Ground ciudad[][10], int nivel);
int numIncendios(Ground ciudad[][10], int nivel);
void setPeligroMult(int x, int y, int nivel, Ground ciudad[][10]); */

void buildCity(Ground city[][10], int level, int x, int y);
void setDanger(Ground city[][10], int level);
void burnDown(Ground city[][10], int level);
int getNumFires(Ground city[][10], int level);
void setDangerMult(int x, int y, int level, Ground city[][10]);