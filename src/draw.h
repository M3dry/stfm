#ifndef DRAW_H
#define DRAW_H

#include <curses.h>
#include "dir.h"

typedef struct dirWin {
    WINDOW *type;
    WINDOW *name;
    WINDOW *perms;
    WINDOW *size;
    WINDOW *last_mod;
} dirWin;

void draw_dir_box(WINDOW *win, dirWin dir_panes, int dirnum, int rows, FileInfo *fInfo, int sel);

#endif // DRAW_H
