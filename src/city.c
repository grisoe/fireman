#include <stdlib.h>

#include "headers/city.h"

void buildCity(Ground city[][10], int level, int x, int y) {

    int ran;
    int ran2;

    int i;
    int k;

    for (i = 0; i < level; i++) {
        for (k = 0; k < level; k++) {

            city[i][k].type = 2 + rand() % 2;
            city[i][k].isDynamited = FALSE;
            city[i][k].isInDanger = FALSE;

        }
    }

    do {

        ran = rand() % level;
        ran2 = rand() % level;

    } while (ran == y && ran2 == x);

    city[ran][ran2].type = FIRE;
    city[y][x].type = BUILDING;

    setDanger(city, level);

}

void setDanger(Ground city[][10], int level) {

    int i;
    int k;

    for (i = 0; i < level; i++) {
        for (k = 0; k < level; k++) {

            if (city[i][k].type == FIRE) {

                if ((i - 1 >= 0) && (city[i - 1][k].type != WATER)
                    && (city[i - 1][k].type != FIRE)) {
                    city[i - 1][k].isInDanger = TRUE;
                }

                if ((i + 1 <= level - 1) && (city[i + 1][k].type != WATER)
                    && (city[i + 1][k].type != FIRE)) {
                    city[i + 1][k].isInDanger = TRUE;
                }

                if ((k + 1 <= level - 1) && (city[i][k + 1].type != WATER)
                    && (city[i][k + 1].type != FIRE)) {
                    city[i][k + 1].isInDanger = TRUE;
                }

                if ((k - 1 >= 0) && (city[i][k - 1].type != WATER)
                    && (city[i][k - 1].type != FIRE)) {
                    city[i][k - 1].isInDanger = TRUE;
                }

            }

        }
    }

}

void burnDown(Ground city[][10], int level) {

    int i;
    int k;

    for (i = 0; i < level; i++) {
        for (k = 0; k < level; k++) {

            if (city[i][k].isInDanger) {
                city[i][k].isInDanger = FALSE;
                city[i][k].type = FIRE;
            }

        }
    }

}

int getNumFires(Ground city[][10], int level) {

    int i;
    int k;
    int n = 0;

    for (i = 0; i < level; i++) {
        for (k = 0; k < level; k++) {

            if (city[i][k].type == FIRE) {
                n++;
            }

        }
    }

    return n;

}

void setDangerMult(int x, int y, int level, Ground city[][10]) {

    if (y - 1 >= 0) {
        city[y - 1][x].isInDanger = FALSE;
    }

    if (y - 2 >= 0) {

        if (city[y - 2][x].type == FIRE) {

            if (city[y - 1][x].type != FIRE && city[y - 1][x].type != WATER) {
                city[y - 1][x].isInDanger = TRUE;
            }

        }
    }

    if (y + 1 <= level - 1) {
        city[y + 1][x].isInDanger = FALSE;
    }

    if (y + 2 <= level - 1) {

        if (city[y + 2][x].type == FIRE) {

            if (city[y + 1][x].type != FIRE && city[y + 1][x].type != WATER) {
                city[y + 1][x].isInDanger = TRUE;
            }

        }
    }

    if (x + 1 <= level - 1) {
        city[y][x + 1].isInDanger = FALSE;
    }

    if (x + 2 <= level - 1) {

        if (city[y][x + 2].type == FIRE) {

            if (city[y][x + 1].type != FIRE && city[y][x + 1].type != WATER) {
                city[y][x + 1].isInDanger = TRUE;
            }

        }
    }

    if (x - 1 >= 0) {
        city[y][x - 1].isInDanger = FALSE;
    }

    if (x - 2 >= 0) {

        if (city[y][x - 2].type == FIRE) {

            if (city[y][x - 1].type != FIRE && city[y][x - 1].type != WATER) {
                city[y][x - 1].isInDanger = TRUE;
            }

        }
    }

    if (y - 1 >= 0 && x - 1 >= 0) {

        if (city[y - 1][x - 1].type == FIRE) {

            if (city[y - 1][x].type != WATER && city[y - 1][x].type != FIRE) {
                city[y - 1][x].isInDanger = TRUE;
            }

            if (city[y][x - 1].type != WATER && city[y][x - 1].type != FIRE) {
                city[y][x - 1].isInDanger = TRUE;
            }
        }
    }

    if (y - 1 >= 0 && x + 1 <= level - 1) {

        if (city[y - 1][x + 1].type == FIRE) {

            if (city[y - 1][x].type != WATER && city[y - 1][x].type != FIRE) {
                city[y - 1][x].isInDanger = TRUE;
            }

            if (city[y][x + 1].type != WATER && city[y][x + 1].type != FIRE) {
                city[y][x + 1].isInDanger = TRUE;
            }

        }
    }

    if (y + 1 <= level - 1 && x + 1 <= level - 1) {

        if (city[y + 1][x + 1].type == FIRE) {

            if (city[y + 1][x].type != WATER && city[y + 1][x].type != FIRE) {
                city[y + 1][x].isInDanger = TRUE;
            }

            if (city[y][x + 1].type != WATER && city[y][x + 1].type != FIRE) {
                city[y][x + 1].isInDanger = TRUE;
            }

        }
    }

    if (y + 1 <= level - 1 && x - 1 >= 0) {

        if (city[y + 1][x - 1].type == FIRE) {

            if (city[y + 1][x].type != WATER && city[y + 1][x].type != FIRE) {
                city[y + 1][x].isInDanger = TRUE;
            }

            if (city[y][x - 1].type != WATER && city[y][x - 1].type != FIRE) {
                city[y][x - 1].isInDanger = TRUE;
            }

        }
    }
}