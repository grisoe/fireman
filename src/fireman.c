#include "headers/fireman.h"

void createFireman(Fireman *b, int level, int turns) {

    int x;
    int y;

    b->dynamites = turns - 3;

    printw("X coordinate of the fireman (0-%d): ", level - 1);
    scanw("%d", &x);
    while (x < 0 || x > level - 1) {

        printw("\nX coordinate of the fireman must be between 0 and %d."
               "\n\n", level - 1);

        printw("X coordinate of the fireman (0-%d): ", level - 1);
        scanw("%d", &x);

    }
    b->x = x;

    printw("Y coordinate of the fireman (0-%d): ", level - 1);
    scanw("%d", &y);
    while (y < 0 || y > level - 1) {

        printw("\nY coordinate of the fireman must be between 0 and %d."
               "\n\n", level - 1);

        printw("Y coordinate of the fireman (0-%d): ", level - 1);
        scanw("%d", &y);

    }
    b->y = y;

}

int moveFireman(int direction, Fireman *fireman, int level) {

    if (direction == 1) {

        if ((fireman->y) - 1 >= 0) {
            (fireman->y)--;
            return 1;
        } else {

            printw("\nYou can't run away from the city.");
            getch();
            refresh();

            return 0;

        }

    } else if (direction == 2) {

        if ((fireman->y) + 1 < level) {
            (fireman->y)++;
            return 1;
        } else {

            printw("\nYou can't run away from the city.");
            getch();
            refresh();

            return 0;

        }

    } else if (direction == 4) {

        if ((fireman->x) + 1 < level) {
            (fireman->x)++;
            return 1;
        } else {

            printw("\nYou can't run away from the city.");
            getch();
            refresh();

            return 0;

        }

    } else if (direction == 3) {

        if ((fireman->x) - 1 >= 0) {
            (fireman->x)--;
            return 1;
        } else {

            printw("\nYou can't run away from the city.");
            getch();
            refresh();

            return 0;

        }

    }

    return -1;

}

int dynamite(int x, int y, int level, Ground city[][10]) {

    if (city[y][x].isDynamited == FALSE) {

        if (city[y][x].type == FIRE) {
            setDangerMult(x, y, level, city);
        }

        city[y][x].isDynamited = TRUE;
        city[y][x].isInDanger = FALSE;
        city[y][x].type = WATER;

        return 1;

    } else {

        printw("\nAlready dynamited.\n");
        getch();
        refresh();

        return 0;

    }

}