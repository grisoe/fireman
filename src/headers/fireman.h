#pragma once

#include "city.h"

typedef struct fireman{
	int dynamites;
	int x;
	int y;
} fireman;

void createFireman(fireman *b, int level, int turns);
int moveFireman(int direction, fireman *b, int level);
int dynamite(int x, int y, int level, Ground city[][10]);