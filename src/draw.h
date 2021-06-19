#ifndef DRAW_H
#define DRAW_H

#include <curses.h>
#include "dir.h"

void draw_dir_box(WINDOW *win, int dirnum, int rows, FileInfo *fInfo, int sel);

#endif // DRAW_H
