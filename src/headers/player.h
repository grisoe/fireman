#pragma once

#include "city.h"

typedef struct Player{
	char name[50];
	int points;
	int level;
	int turns;
} Player;

void setPlayer(Player *j);
void setPoints(Player *j, Ground city[][10]);