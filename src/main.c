#include <stdio.h>
#include <curses.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <locale.h>

#include "dir.h"
#include "sorting.h"
#include "draw.h"

int
main(int argc, char **argv)
{
    setlocale(LC_ALL, "");
    initscr();
    noecho();
    keypad(stdscr, TRUE);

    int dirnum = 0;
    FileInfo *fInfo = get_dirs(argc > 1 ? argv[1] : ".", &dirnum);
    fInfo = sort_by_size(fInfo, dirnum, 0);

    int input = 0, row = getmaxy(stdscr), col = getmaxx(stdscr), sel = 0;

    /* WINDOW *dirs = newwin(row, col / 1.15, 0, 1); */
    WINDOW *dirs = newwin(row, col / 3.6 + 41, 0, 1);
    dirWin dir_panes;
    dir_panes.type = newwin(row - 2, 2, 1, 3);
    dir_panes.name = newwin(row - 2, col / 3.6, 1, 6);
    dir_panes.perms = newwin(row - 2, 12, 1, col / 3.6);
    dir_panes.size = newwin(row - 2, 10, 1, 11 + col / 3.6);
    dir_panes.last_mod = newwin(row - 2, 20, 1, 21 + col / 3.6);
    box(dirs, 0, 0);
    refresh();
    wrefresh(dirs);

    while (1) {
        draw_dir_box(dirs, dir_panes, dirnum, row, fInfo, sel);

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
            case 'l':
                if (fInfo[sel].type == DT_DIR) {
                    chdir(fInfo[sel].realpath);
                    fInfo = get_dirs(".", &dirnum);
                    fInfo = sort_by_size(fInfo, dirnum, 0);
                    sel = 0;
                }
                break;
            case 'h':
                chdir("..");
                fInfo = get_dirs(".", &dirnum);
                fInfo = sort_by_size(fInfo, dirnum, 0);
                sel = 0;
                break;
            default:
                break;
        }
        if (input == 10)
            break;
    }

    endwin();
    fprintf(stdout, "%s\n", fInfo[sel].realpath);

    free(fInfo);
    return 0;
}
