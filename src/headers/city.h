#pragma once

#include <ncurses.h>

typedef enum {
    FIRE, WATER, PASTURE, BUILDING
} Ground_type;

typedef struct Ground {
    Ground_type type;
    bool isDynamited;
    bool isInDanger;
} Ground;

void buildCity(Ground city[][10], int level, int x, int y);

void setDanger(Ground city[][10], int level);

void burnDown(Ground city[][10], int level);

int getNumFires(Ground city[][10], int level);

void setDangerMult(int x, int y, int level, Ground city[][10]);