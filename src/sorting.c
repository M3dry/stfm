#include <stdlib.h>

#include "sorting.h"
#include "dir.h"

FileInfo
*sort_by_size(FileInfo *file, int filenum, int reversed)
{
    return reversed ? sort_by_size_reverse(file, filenum) : sort_by_size_noreverse(file, filenum);
}

FileInfo
*sort_by_size_noreverse(FileInfo *file, int filenum)
{
    FileInfo tmp;

    for (int i = filenum; i > 0; i--) {
        for (int o = filenum - i -1; o > 0; o--) {
            if (file[o].size > file[o-1].size) {
                tmp = file[o];
                file[o] = file[o - 1];
                file[o - 1] = tmp;
            }
        }
    }

    return file;
}

FileInfo
*sort_by_size_reverse(FileInfo *file, int filenum)
{
    FileInfo tmp;

    for (int i = 0; i < filenum; i++) {
        for (int o = 0; o < filenum - i - 1; o++) {
            if (file[o].size > file[o+1].size) {
                tmp = file[o];
                file[o] = file[o + 1];
                file[o + 1] = tmp;
            }
        }
    }

    return file;
}
