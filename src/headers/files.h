#pragma once

#include "player.h"

char *recordsPath();
void createRecords();
FILE* openRecords(int mode);
void writeRecords(Player *js, int numJs);