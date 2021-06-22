#ifndef DIR_H
#define DIR_H

#include <sys/types.h>

typedef struct file {
    char *name;
    char *realpath;
    char last_mod[20];
    char perms[10];
    int type;
    unsigned int size;
} FileInfo;

FileInfo *get_dirs(const char *indir, int *dirnum);

#endif // DIR_H
