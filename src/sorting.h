#ifndef SORTING_H
#define SORTING_H

#include "dir.h"

FileInfo *sort_by_size(FileInfo *file, int filenum, int reversed);
FileInfo *sort_by_size_noreverse(FileInfo *file, int filenum);
FileInfo *sort_by_size_reverse(FileInfo *file, int filenum);

#endif // SORTING_H
