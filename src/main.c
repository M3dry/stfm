#include <stdio.h>
#include <curses.h>
#include <stdlib.h>

#include "dir.h"
#include "sorting.h"
#include "draw.h"

int
main(int argc, char **argv)
{
    initscr();
    noecho();
    keypad(stdscr, TRUE);

    int dirnum = 0;
    FileInfo *fInfo = get_dirs(argc > 1 ? argv[1] : ".", &dirnum);
    fInfo = sort_by_size(fInfo, dirnum, 0);

    int input = 0, row = getmaxy(stdscr), col = getmaxx(stdscr), sel = 0;

    WINDOW *dirs = newwin(row, col / 2, 0, 1);
    box(dirs, 0, 0);
    refresh();
    wrefresh(dirs);

    while (1) {

        draw_dir_box(dirs, dirnum, row, fInfo, sel);

        input = wgetch(dirs);
        switch (input) {
            case 'j':
                sel++;
                if (sel == dirnum) sel = 0;
                break;
            case 'k':
                sel--;
                if (sel == -1) sel = dirnum - 1;
                break;
            default:
                break;
        }
        if (input == 10)
            break;
    }

    endwin();
    printf("%s\n", fInfo[sel].realpath);

    free(fInfo);
    return 0;
}
