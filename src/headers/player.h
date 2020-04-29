#pragma once

#include "city.h"

typedef struct Player{
	char name[50];
	int points;
	int level;
	int turns;
} Player;

void setPlayer(Player *player);
void setPoints(Player *player, Ground city[][10]);