#include <string.h>

#include "headers/game.h"
#include "headers/colors.h"
#include "headers/files.h"

void setGame(Player *player, Fireman *fireman, Ground city[][10]) {

    clear();

    printw("---------------Prepare Game---------------\n\n");

    setPlayer(player);
    createFireman(fireman, player->level, player->turns);
    buildCity(city, player->level, fireman->x, fireman->y);

    printw("\nGame ready!");

    getch();
    refresh();

}

void startGame(Player *player, Fireman *fireman, Ground city[][10], Player players[], int *playerCounter) {

    int turns;
    int opt;
    int flag;
    int din = fireman->dynamites;
    int firesCounter;

    for (turns = 1; turns <= player->turns; turns++) {

        if (firesCounter == 0) {
            break;
        }

        do {

            clear();

            attron(COLOR_PAIR(5));

            printw("---------------Game Initialized---------------");

            showMap(city, player->level, fireman->x, fireman->y);
            showPosInfo(city, fireman->y, fireman->x, turns, player->turns, din);

            opt = actionMenu();

            switch (opt) {

                case 1:
                case 2:
                case 3:
                case 4:
                    flag = moveFireman(opt, fireman, player->level);
                    break;

                case 5:

                    if (din > 0) {
                        flag = dynamite(fireman->x, fireman->y, player->level, city);

                        if (flag == 1) {
                            din--;
                        }

                    } else {
                        printw("\nYou don't have any dynamites.\n");
                        flag = 0;
                        getch();
                        refresh();
                    }

                    break;

                case 6:
                    flag = 1;
                    break;

            }

            firesCounter = getNumFires(city, player->level);

        } while (flag == 0);

        if (turns % 3 == 0) {
            burnDown(city, player->level);
            setDanger(city, player->level);
        }

    }

    clear();

    printw("---------------Game Initialized---------------");

    showMap(city, player->level, fireman->x, fireman->y);
    showPosInfo(city, fireman->y, fireman->x, turns, player->turns, din);

    if (firesCounter == 0) {
        printw("\nYou have extinguished all fires!\n");
        player->turns = turns - 1;
    }

    if (firesCounter > 0) {
        printw("\nIt's raining!\n");
    }

    setPoints(player, city);
    printw("\nYour points: %d\n", player->points);

    players[*playerCounter] = *player;
    (*playerCounter)++;

    writeRecords(players, *playerCounter);

    printw("\nPress 's' to continue...");
    noecho();
    while (getch() != 's');
    echo();

    refresh();

}

void showMap(Ground city[][10], int level, int x, int y) {

    char desc[5];

    int i;
    int k;

    printw("\n\nB-BUILDING, P-PASTURE, W-WATER, F-FIRE, i-Fireman, "
           "!-In Danger, *-Dynamited\n\n");

    for (i = 0; i < level; i++) {
        for (k = 0; k < level; k++) {

            if (k == x && i == y) {
                strcpy(desc, " i");
            } else {
                strcpy(desc, " ");
            }

            if (city[i][k].type == BUILDING) {

                strcat(desc, "B");
                attron(COLOR_PAIR(4));

            } else if (city[i][k].type == PASTURE) {

                strcat(desc, "P");
                attron(COLOR_PAIR(2));

            } else if (city[i][k].type == FIRE) {

                strcat(desc, "F");
                attron(COLOR_PAIR(1));

            } else if (city[i][k].type == WATER) {

                strcat(desc, "W");
                attron(COLOR_PAIR(3));

            }

            if (city[i][k].isDynamited) {
                strcat(desc, "*");
            }

            if (city[i][k].isInDanger) {
                strcat(desc, "!");
            }

            strcat(desc, "\t");

            if (desc[1] == 'i') {

                if (city[i][k].type == BUILDING) {
                    attron(COLOR_PAIR(9));
                }

                if (city[i][k].type == PASTURE) {
                    attron(COLOR_PAIR(7));
                }

                if (city[i][k].type == FIRE) {
                    attron(COLOR_PAIR(6));
                }

                if (city[i][k].type == WATER) {
                    attron(COLOR_PAIR(8));
                }

            }

            if (desc[2] == '!') {

                if (city[i][k].type == BUILDING) {
                    attron(COLOR_PAIR(13));
                }

                if (city[i][k].type == PASTURE) {
                    attron(COLOR_PAIR(11));
                }

                if (city[i][k].type == FIRE) {
                    attron(COLOR_PAIR(10));
                }

                if (city[i][k].type == WATER) {
                    attron(COLOR_PAIR(12));
                }

            }

            printw("%s", desc);
            stopColors();

        }
        printw("\n\n\n");
    }

}

void showPosInfo(Ground city[][10], int y, int x, int turn, int turns, int dynamites) {

    char type[10];

    if (city[y][x].type == FIRE) {
        strcpy(type, "FIRE");
    } else if (city[y][x].type == WATER) {
        strcpy(type, "WATER");
    } else if (city[y][x].type == PASTURE) {
        strcpy(type, "PASTURE");
    } else if (city[y][x].type == BUILDING) {
        strcpy(type, "BUILDING");
    }

    printw("Current position: %s\t", type);
    printw("Coordinates: X=%d, Y=%d\n", x, y);
    printw("Dynamited: %s\t\t\t", city[y][x].isDynamited ? "Yes" : "No");
    printw("In Danger: %s\n", city[y][x].isInDanger ? "Yes" : "No");
    printw("Dynamites: %d\t\t\t", dynamites);
    printw("Turn %d of %d\n", turn, turns);

}

int actionMenu() {

    int opt;

    int x;
    int y;

    printw("\n[ 1 ] North\n[ 2 ] South\n[ 3 ] West\n[ 4 ] East\n"
           "[ 5 ] Dynamite\n[ 6 ] Stay here\n");

    printw("\nChoose an option: ");
    scanw("%d", &opt);

    getyx(stdscr, y, x);

    while (opt <= 0 || opt > 6) {

        printw("\nInvalid option.\n");

        getch();
        move(y - 2, x);

        clrtobot();
        refresh();

        printw("\nChoose an option: ");
        scanw("%d", &opt);

    }

    return opt;

}