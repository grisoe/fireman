#pragma once

#include "player.h"
#include "fireman.h"

void setGame(Player *player, Fireman *fireman, Ground city[][10]);
void startGame(Player *player, Fireman *fireman, Ground city[][10], Player players[], int *playersCounter);
void showMap(Ground city[][10], int level, int x, int y);
void showPosInfo(Ground city[][10], int y, int x, int turn, int turns, int dynamites);
int actionMenu();

/*
js[] - players[]
*/