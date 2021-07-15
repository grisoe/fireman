#include <string.h>

#include "headers/queries.h"
#include "headers/files.h"

void queries() {

    int menu;

    do {

        menu = queriesMenu();

        switch (menu) {

            case 1:
                queryAll();
                break;

            case 2:
                queryLevel();
                break;

            case 3:
                queryPoints();
                break;

            case 4:
                queryPlayer();
                break;

            case 5:
                return;

            default:

                printw("\nInvalid option.");

                getch();
                refresh();

                break;
        }

    } while (menu != 5);

    getch();
    refresh();
}

int queriesMenu() {

    int opt;

    clear();

    printw("---------------Queries Menu---------------\n\n");

    printw("[ 1 ] All games\n[ 2 ] By difficulty level\n"
           "[ 3 ] Ordered by points\n[ 4 ] By Player\n"
           "[ 5 ] Return\n");

    printw("\nChoose an option: ");
    scanw("%d", &opt);

    return opt;
}

void queryAll() {

    clear();

    printw("---------------All Games---------------\n\n");

    FILE *fd = openRecords(0);
    Player p;

    while (fread(&p, sizeof(Player), 1, fd) > 0) {

        printw("Player: %s\nPoints: %d\nLevel: %d\nPlayed turns: %d\n\n",
               p.name, p.points, p.level, p.turns);
    }

    fclose(fd);

    getch();
    refresh();
}

void queryLevel() {

    clear();

    printw("---------------By Difficulty Level---------------\n\n");

    int level;
    bool flag = TRUE;

    printw("Difficulty level (3-10): ");
    scanw("%d", &level);
    while (level < 3 || level > 10) {

        printw("\nDifficulty level must be between 3 and 10.\n\n");

        printw("Difficulty level (3-10): ");
        scanw("%d", &level);
    }

    FILE *fd = openRecords(0);
    Player p;

    while (fread(&p, sizeof(Player), 1, fd) > 0) {

        if (p.level == level) {

            printw("\nPlayer: %s\nPoints: %d\nLevel: %d\nPlayed turns: %d\n",
                   p.name, p.points, p.level, p.turns);

            flag = FALSE;
        }
    }

    fclose(fd);

    if (flag) {
        printw("\nNo records for this level.");
    }

    getch();
    refresh();
}

void queryPoints() {

    clear();

    printw("---------------Ordered by Points---------------\n\n");

    FILE *fd = openRecords(2);

    Player p;
    Player p2;
    Player aux;

    fseek(fd, 0, SEEK_END);

    int s = ftell(fd) / sizeof(Player);

    rewind(fd);

    int i;
    int k;

    for (i = 1; i < s; i++) {
        for (k = 0; k < s - i; k++) {

            fseek(fd, k * sizeof(Player), SEEK_SET);
            fread(&p, sizeof(Player), 1, fd);

            fseek(fd, (k + 1) * sizeof(Player), SEEK_SET);
            fread(&p2, sizeof(Player), 1, fd);

            if (p.points < p2.points) {

                aux = p;
                p = p2;
                p2 = aux;

                fseek(fd, k * sizeof(Player), SEEK_SET);
                fwrite(&p, sizeof(Player), 1, fd);

                fseek(fd, (k + 1) * sizeof(Player), SEEK_SET);
                fwrite(&p2, sizeof(Player), 1, fd);

            }

        }
    }

    rewind(fd);

    while (fread(&p, sizeof(Player), 1, fd) > 0) {
        printw("Player: %s\nPoints: %d\nLevel: %d\nPlayed turns: %d\n\n",
               p.name, p.points, p.level, p.turns);
    }

    fclose(fd);

    getch();
    refresh();

}

void queryPlayer() {

    clear();

    printw("---------------By Player---------------\n\n");

    char name[50];
    bool flag = TRUE;

    printw("Name: ");
    scanw("%[^\n]", name);

    FILE *fd = openRecords(0);
    Player p;

    while (fread(&p, sizeof(Player), 1, fd) > 0) {

        if (strcmp(p.name, name) == 0) {

            printw("\nPlayer: %s\nPoints: %d\nLevel: %d\nPlayed turns: %d\n",
                   p.name, p.points, p.level, p.turns);

            flag = FALSE;
        }
    }

    fclose(fd);

    if (flag) {
        printw("\nNo records for this player.");
    }

    getch();
    refresh();
}