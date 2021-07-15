#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "headers/files.h"

char *recordsPath() {

    char cwd[150];


    if (getcwd(cwd, sizeof(cwd)) != NULL) {

        char *result = malloc(strlen("/files/playersRecords") + strlen(cwd) + 1);

        strcpy(result, cwd);
        strcat(result, "/files/playersRecords");

        return result;

    } else {
        perror("getcwd() error");
        return NULL;
    }

}

void writeRecords(Player *player, int playersCounter) {

    FILE *fd = openRecords(1);

    Player p = player[playersCounter - 1];

    fseek(fd, 0, SEEK_END);
    fwrite(&p, sizeof(Player), 1, fd);
    fclose(fd);

}

void createRecords() {

    FILE *fd = fopen(recordsPath(), "ab+");

    if (fd == NULL) {

        clear();

        endwin();
        perror("Error: can't create file");
        exit(1);

    }

    fclose(fd);

}


FILE *openRecords(int mode) {

    FILE *fd;

    if (mode == 0) {
        fd = fopen(recordsPath(), "r");
    } else if (mode == 1) {
        fd = fopen(recordsPath(), "aw");
    } else if (mode == 2) {
        fd = fopen(recordsPath(), "r+");
    }

    if (fd == NULL) {

        clear();

        endwin();
        perror("Error: can't open file");
        exit(1);

    }

    return fd;

}