#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dir.h"

void
get_dirs(const char *indir)
{
    DIR *dir = opendir(indir);
    struct dirent *d;
    int ndir = 0;

    if (dir == NULL) {
        fprintf(stderr, "Uo0pPppS1 ^w^ get_dirs(%s) fucked it self UwU", indir);
        return ;
    }

    while ((d = readdir(dir)) != NULL) {
        if (strcmp(d->d_name, "..") && strcmp(d->d_name, "."))
            switch (d->d_type) {
                case DT_DIR:
                    printf("%s/ %d\n", d->d_name, ndir++);
                    break;
                default:
                    printf("%s %d\n", d->d_name, ndir++);
            }
    }

    return ;
}
