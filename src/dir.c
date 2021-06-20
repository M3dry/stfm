#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <sys/stat.h>
#include <unistd.h>

#include "dir.h"

FileInfo
*get_dirs(const char *indir, int *dirnum)
{
    DIR *dir = opendir(indir);
    struct dirent *d;
    struct stat fileStat;
    char *real = NULL;
    int ndir = 0, i = 0, tmp = 0;

    if (dir == NULL) {
        fprintf(stderr, "get_dirs(\"%s\") no directory found\n", indir);
        return NULL;
    }

    while ((d = readdir(dir)) != NULL) {
        if (strcmp(d->d_name, "..") && strcmp(d->d_name, "."))
            ndir++;
    }

    FileInfo *files = malloc(ndir * sizeof(FileInfo));
    dir = opendir(indir);

    while ((d = readdir(dir)) != NULL) {
        if (strcmp(d->d_name, "..") && strcmp(d->d_name, ".")) {
            // files[i].name = malloc(NAME_MAX * sizeof(char)); // IDK if this is needed but it works without it
            files[i].name = d->d_name;
            switch (d->d_type) {
                case DT_REG:
                    files[i].type = DT_REG;  break;
                case DT_DIR:
                    files[i].type = DT_DIR;  break;
                case DT_LNK:
                    files[i].type = DT_LNK;  break;
                case DT_FIFO:
                    files[i].type = DT_FIFO; break;
                case DT_SOCK:
                    files[i].type = DT_SOCK; break;
                case DT_BLK:
                    files[i].type = DT_BLK;  break;
                case DT_CHR:
                    files[i].type = DT_CHR;  break;
                default:
                    files[i].type = DT_UNKNOWN;
            }

            if (indir[strlen(indir) - 1] != '/') tmp = 1;

            real = malloc(sizeof(char) * (strlen(indir) + strlen(files[i].name) + tmp));

            for (int o = 0; o < (strlen(indir) + strlen(files[i].name)); o++) {
                real[o] = '\0';
            }

            for (int o = 0; o < strlen(indir); o++) {
                real[o] = indir[o];
            }

            if (tmp) real[strlen(indir)] = '/';

            for (int o = 0; o < strlen(files[i].name); o++) {
                real[o + strlen(indir) + tmp] = files[i].name[o];
                real[o + strlen(indir) + 1 + tmp] = '\0';
            }

            files[i].realpath = realpath(real, NULL);

            free(real);

            chdir(indir);

            stat(d->d_name, &fileStat);

            files[i].perms[0] = (S_ISDIR(fileStat.st_mode))  ? 'd' : '-';
            files[i].perms[1] = (fileStat.st_mode & S_IRUSR) ? 'r' : '-';
            files[i].perms[2] = (fileStat.st_mode & S_IWUSR) ? 'w' : '-';
            files[i].perms[3] = (fileStat.st_mode & S_IXUSR) ? 'x' : '-';
            files[i].perms[4] = (fileStat.st_mode & S_IRGRP) ? 'r' : '-';
            files[i].perms[5] = (fileStat.st_mode & S_IWGRP) ? 'w' : '-';
            files[i].perms[6] = (fileStat.st_mode & S_IXGRP) ? 'x' : '-';
            files[i].perms[7] = (fileStat.st_mode & S_IROTH) ? 'r' : '-';
            files[i].perms[8] = (fileStat.st_mode & S_IWOTH) ? 'w' : '-';
            files[i].perms[9] = (fileStat.st_mode & S_IXOTH) ? 'x' : '-';
            files[i].size = (files[i].type != DT_DIR) ? fileStat.st_size : 0;

            i++;
        }
    }

    if (dirnum != NULL)
        *dirnum = i;

    return files;
}
