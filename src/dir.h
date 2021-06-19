#ifndef DIR_H
#define DIR_H

typedef struct file {
    char *name;
    char *realpath;
    char perms[10];
    int type;
    unsigned int size;
} FileInfo;

FileInfo *get_dirs(const char *indir, int *dirnum);

#endif // DIR_H
