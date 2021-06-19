#include <stdio.h>
#include <curses.h>

#include "dir.h"

int
main(int argc, char **argv)
{
    /* initscr(); */

    /* getch(); */
    /* endwin(); */

    int dirnum = 0;
    FileInfo *fInfo = get_dirs(".", &dirnum);

    for (int i = 0; i < dirnum; i++) {
        printf("%s %d %d %s\n", fInfo[i].perms, fInfo[i].size, fInfo[i].type, fInfo[i].name);
    }

    return 0;
}












