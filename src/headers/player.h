#pragma once

#include "city.h"

typedef struct Player{
	char name[50];
	int points;
	int level;
	int turns;
} Player;

void SetPlayer(Player *j);
void setPoints(Player *j, Ground city[][10]);