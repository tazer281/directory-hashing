#include <dirent.h> 
#include <stdio.h> 
#include <sys/stat.h>
#include <stdint.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>

const uint32_t FNV_OFFSET = 216613261U;
const uint32_t FNV_PRIME = 4294967291U;

uint32_t fnv(char *c) {
    uint32_t hash = FNV_OFFSET, i;
    for (i = 0; i < strlen(c); i++) {
        hash = (hash ^ (c[i])) * FNV_PRIME;
    }
    return hash;
}

int main(int argc, char *argv[]) {

    int dir1, dir2, i, filenameLength, len, res;
    uint32_t hash;
    char newChar, *filename, buffer[3], *oldFilename;
    FILE *fp, *source;
    struct stat sb, st;
    struct dirent *cur;
    DIR *pd;
    pd = opendir(argv[1]);

    while (cur = readdir(pd)) {
        if (*cur->d_name != '.') {

            oldFilename = malloc(strlen(cur->d_name) + strlen(argv[1]) + 1);
            strcpy(oldFilename, argv[1]);
            strcat(oldFilename, cur->d_name);
            stat(oldFilename, &sb);

            if (!S_ISDIR(sb.st_mode)) {
                filename = calloc(1, sizeof(char));
                hash = fnv(cur->d_name);

                dir1 = hash & 255;
                hash = hash >> 8;
                dir2 = hash & 255;

                filename = realloc(filename, strlen(argv[1]) + 8 + strlen(cur->d_name));
                strcpy(filename, argv[1]);
                sprintf(buffer, "%d", dir1);
                strcat(filename, buffer);
                strcat(filename, "/");

                if (stat(filename, &st) == -1) {
                    mkdir(filename, 0777);
                }

                sprintf(buffer, "%d", dir2);
                strcat(filename, buffer);
                strcat(filename, "/");

                if (stat(filename, &st) == -1) {
                    mkdir(filename, 0777);
                }

                strcat(filename, cur->d_name);

                rename(oldFilename, filename);

                free(filename);
                free(oldFilename);
            }
        }

    }
    return (0);
}

