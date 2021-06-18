#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <sys/stat.h>

#include "dir.h"

FileInfo
**get_dirs(const char *indir)
{
    DIR *dir = opendir(indir);
    struct dirent *d;
    struct stat fileStat;
    int ndir = 0, i = 0;

    if (dir == NULL) {
        fprintf(stderr, "Uo0pPppS1 ^w^ get_dirs(%s) fucked it self UwU\n", indir);
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
            if (stat(d->d_name, &fileStat) < 0) {
                fprintf(stderr, "YOu\'re mothre is gaj stat failed\n");
                return NULL;
            }

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

            printf("%s %d %s\n", files[i].perms, files[i].type, files[i].name);
            i++;
        }
    }

    return NULL;
}
