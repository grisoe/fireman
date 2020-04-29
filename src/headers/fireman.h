#pragma once

#include "city.h"

typedef struct Fireman{
	int dynamites;
	int x;
	int y;
} Fireman;

void createFireman(Fireman *fireman, int level, int turns);
int moveFireman(int direction, Fireman *fireman, int level);
int dynamite(int x, int y, int level, Ground city[][10]);

/*
b - fireman
*/