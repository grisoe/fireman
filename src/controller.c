#include "headers/controller.h"

int main() {

    createRecords();

    Fireman fireman;
    Player player;
    Ground city[10][10];
    Player js[100];

    int playersCounter = 0;
    bool isReady = FALSE;
    int menu;

    srand(time(NULL));

    initscr();
    startColors();
    scrollok(stdscr, TRUE);

    FILE *fd;

    do {

        attron(COLOR_PAIR(5));

        menu = mainMenu();

        switch (menu) {

            case 1:

                if (isReady) {
                    printw("\nThere's a game ready to be played!");
                    getch();
                    refresh();
                } else {
                    setGame(&player, &fireman, city);
                    isReady = TRUE;
                }

                break;

            case 2:

                if (isReady) {
                    startGame(&player, &fireman, city, js, &playersCounter);
                    isReady = FALSE;
                } else {
                    printw("\nFirst, you have to prepare a game.");
                    getch();
                    refresh();
                }

                break;

            case 3:

                fd = openRecords(0);

                fseek(fd, 0, SEEK_END);

                if (ftell(fd) / sizeof(Player) == 0) {

                    printw("\nNo records yet.");
                    fclose(fd);

                    getch();
                    refresh();

                } else {

                    fclose(fd);
                    attron(COLOR_PAIR(5));
                    queries();

                }

                break;

            case 4:
                printw("\nExiting...");
                break;

            default:

                printw("\nInvalid option. Try again...");
                getch();
                refresh();

                break;

        }

    } while (menu != 4);

    getch();
    refresh();

    endwin();

}

int mainMenu() {

    clear();

    printw("---------------Main Menu---------------\n\n");

    int opt;

    printw("[ 1 ] Prepare Game\n[ 2 ] Start Game\n"
           "[ 3 ] Queries\n[ 4 ] Exit\n");

    printw("\nChoose an option: ");
    scanw("%d", &opt);

    return opt;

}