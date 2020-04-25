#pragma once

#include "player.h"
#include "fireman.h"

void setGame(Player *j, Fireman *b, Ground city[][10]);
void startGame(Player *j, Fireman *b, Ground city[][10], Player js[], int *numJs);
void showMap(Ground city[][10], int nivel, int x, int y);
void showPosInfo(Ground city[][10], int y, int x, int turn, int turns, int dynamites);
int actionMenu();