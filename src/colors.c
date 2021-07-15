#include <ncurses.h>

#include "headers/colors.h"

void startColors() {

    start_color();

    init_pair(1, COLOR_BLACK, COLOR_RED);
    init_pair(2, COLOR_BLACK, COLOR_GREEN);
    init_pair(3, COLOR_BLACK, COLOR_CYAN);
    init_pair(4, COLOR_BLACK, COLOR_WHITE);
    init_pair(5, COLOR_WHITE, COLOR_BLACK);

    init_pair(6, COLOR_MAGENTA, COLOR_RED);
    init_pair(7, COLOR_MAGENTA, COLOR_GREEN);
    init_pair(8, COLOR_MAGENTA, COLOR_CYAN);
    init_pair(9, COLOR_MAGENTA, COLOR_WHITE);

    init_pair(10, COLOR_YELLOW, COLOR_RED);
    init_pair(11, COLOR_YELLOW, COLOR_GREEN);
    init_pair(12, COLOR_YELLOW, COLOR_CYAN);
    init_pair(13, COLOR_YELLOW, COLOR_WHITE);

}

void stopColors() {

    int i;

    for (i = 1; i <= 13; i++) {
        attroff(COLOR_PAIR(i));
    }

}