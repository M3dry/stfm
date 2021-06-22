#include <curses.h>
#include <math.h>

#include "dir.h"
#include "draw.h"

void
draw_dir_box(WINDOW *win, dirWin dir_panes, int dirnum, int rows, FileInfo *fInfo, int sel)
{
    int pages = ceil((double) dirnum / (rows - 2)), curPage = 1, pageLen = rows - 2;

    for (int i = 1; i < pages + 1; i++) {
        if (i == curPage) {
            wclear(win);
            box(win, 0, 0);
            wrefresh(win);

            for (int o = 0; o < pageLen && o < dirnum; o++) {
                if (sel >= pageLen * i) {
                    curPage = floor((double) sel / (rows - 2)) + 1;
                    break;
                }

                if ((sel < pageLen) ? (sel == o) : ((sel - pageLen * ((curPage > 2) ? i - 1 : 1)) == o)) {
                    wattron(dir_panes.type, A_BOLD|A_ITALIC|A_REVERSE);
                    wattron(dir_panes.name, A_BOLD|A_ITALIC|A_REVERSE);
                    wattron(dir_panes.perms, A_BOLD|A_ITALIC|A_REVERSE);
                    wattron(dir_panes.size, A_BOLD|A_ITALIC|A_REVERSE);
                    wattron(dir_panes.last_mod, A_BOLD|A_ITALIC|A_REVERSE);
                }

                if (((curPage == 1) ? o : o + pageLen * ((curPage > 2) ? i - 1 : 1)) < dirnum) {
                    mvwprintw(dir_panes.type, o, 0, "%d", fInfo[(curPage == 1) ? o : o + pageLen * ((curPage > 2) ? i - 1 : 1)].type);
                    mvwprintw(dir_panes.name, o, 0, "%s", fInfo[(curPage == 1) ? o : o + pageLen * ((curPage > 2) ? i - 1 : 1)].name);
                    mvwprintw(dir_panes.perms, o, 0, "%s", fInfo[(curPage == 1) ? o : o + pageLen * ((curPage > 2) ? i - 1 : 1)].perms);
                    mvwprintw(dir_panes.last_mod, o, 0, "%s", fInfo[(curPage == 1) ? o : o + pageLen * ((curPage > 2) ? i - 1 : 1)].last_mod);
                    if(fInfo[(curPage == 1) ? o : o + pageLen * ((curPage > 2) ? i - 1 : 1)].size > 0){
                        mvwprintw(dir_panes.size, o, 0, "%d", fInfo[(curPage == 1) ? o : o + pageLen * ((curPage > 2) ? i - 1 : 1)].size);
                    }
                    wrefresh(dir_panes.type);
                    wrefresh(dir_panes.name);
                    wrefresh(dir_panes.perms);
                    wrefresh(dir_panes.size);
                    wrefresh(dir_panes.last_mod);
                    refresh();
                }

                wattroff(dir_panes.type, A_BOLD|A_ITALIC|A_REVERSE);
                wattroff(dir_panes.name, A_BOLD|A_ITALIC|A_REVERSE);
                wattroff(dir_panes.perms, A_BOLD|A_ITALIC|A_REVERSE);
                wattroff(dir_panes.size, A_BOLD|A_ITALIC|A_REVERSE);
                wattroff(dir_panes.last_mod, A_BOLD|A_ITALIC|A_REVERSE);
                refresh();
            }
        }
    }
}
