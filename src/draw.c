#include <curses.h>
#include <math.h>

#include "dir.h"
#include "draw.h"

void
draw_dir_box(WINDOW *win, int dirnum, int rows, FileInfo *fInfo, int sel)
{
    int pages = ceil((double) dirnum / (rows - 2)), curPage = 1, pageLen = rows - 2;

    for (int i = 1; i < pages + 1; i++) {
        if (i == curPage) {
            wclear(win);
            box(win, 0, 0);

            for (int o = 0; o < pageLen && o < dirnum; o++) {
                /* mvwprintw(win, 0, 0, "%d %d %d %d %d %d", curPage, dirnum, rows, pages, sel, i); */
                if (sel >= pageLen * i) {
                    curPage = floor((double) sel / (rows - 2)) + 1;
                    /* mvwprintw(win, o + 1, 2, "SUP"); */
                    /* mvwprintw(win, 0, 30, "Hello %d", o + 1); */
                    break;
                }
                if ((sel < pageLen) ? (sel == o) : ((sel - pageLen * ((curPage > 2) ? i - 1 : 1)) == o))
                    wattron(win, A_BOLD|A_ITALIC|A_REVERSE);
                mvwprintw(win, o + 1, 2, "%s %d %d %s", fInfo[(curPage == 1) ? o : o + pageLen * ((curPage > 2) ? i - 1 : 1)].perms,
                                                        fInfo[(curPage == 1) ? o : o + pageLen * ((curPage > 2) ? i - 1 : 1)].size,
                                                        fInfo[(curPage == 1) ? o : o + pageLen * ((curPage > 2) ? i - 1 : 1)].type,
                                                        fInfo[(curPage == 1) ? o : o + pageLen * ((curPage > 2) ? i - 1 : 1)].name);
                mvwprintw(win, 0, 2, "%d", (curPage == 1) ? o : o + pageLen);
                wattroff(win, A_BOLD|A_ITALIC|A_REVERSE);
                refresh();
            }
        }
    }
}
