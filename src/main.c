#include <stdio.h>
#include <curses.h>
#include <stdlib.h>

#include "dir.h"

int
main(int argc, char **argv)
{
    initscr();
    noecho();
    keypad(stdscr, TRUE);

    int dirnum = 0;
    FileInfo *fInfo = get_dirs(argc > 1 ? argv[1] : ".", &dirnum);

    int sel = 0, input = 0;

    while (1) {
        for (int i = 0; i < dirnum; i++) {
            if (i == sel)
                wattron(stdscr, A_BOLD|A_ITALIC|A_REVERSE);
            mvwprintw(stdscr, i + 1, 0, "%s %d %d %s", fInfo[i].perms, fInfo[i].size, fInfo[i].type, fInfo[i].name);
            wattroff(stdscr, A_BOLD|A_ITALIC|A_REVERSE);
        }
        input = wgetch(stdscr);

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
    return 0;
}
