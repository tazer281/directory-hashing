#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>

char randomChar() {
    int randomIndex;
    char letters[64] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's',
                        't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L',
                        'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '0', '1', '2', '3', '4',
                        '5', '6', '7', '8', '9', '-', '_'};

    randomIndex = randomArrayInt(sizeof(letters));
    return letters[randomIndex];
}

int randomArrayInt(int max) {
    int r;
    r = rand() % max;
    return r;
}

int randomInt(int min, int max) {
    int r = 0;

    while (r < min) {
        r = rand() % max + 1;
    }
    return r;
}

int main(int argc, char *argv) {
    int dir1, dir2, i, j, filenameLength, len, res, writeAmount, k;
    unsigned int hash;
    char *c, *tmp, newChar, *filename, buffer[3], *dir;
    FILE *fp;
    struct stat st = {0};

    c = calloc(1, sizeof(char));
    tmp = calloc(1, sizeof(char));
    filename = calloc(1, sizeof(char));
    srand(time(NULL));

    i = 0;
    j = 0;
    filenameLength = 0;
    dir = "singleTest";

    if (stat(dir, &st) == -1) {
        mkdir(dir, 0777);
    }

    for (i = 0; i < 1000; i = i + 1) {
        filenameLength = randomInt(5, 20);
        for (j = 0; j < filenameLength; j = j + 1) {
            len = strlen(c);

            tmp = realloc(tmp, len + 1);
            strcpy(tmp, c);

            newChar = randomChar();

            c = realloc(c, len + 2);
            strcpy(c, tmp);
            c[len] = newChar;
            c[len + 1] = '\0';
        }

        filename = realloc(filename, strlen(c) + strlen(dir) + 1);
        strcpy(filename,dir);
        strcat(filename, "/");
        strcat(filename, c);

        fp = fopen(filename, "ab+");

        writeAmount = randomInt(1000, 10000);
        for (k = 0; k < writeAmount; k = k + 1) {
            fprintf(fp, "%c", randomChar());
        }

        fclose(fp);

        memset(c, 0, len);
        memset(tmp, 0, len);
        memset(filename, 0, strlen(filename));
    }

    free(c);
    free(tmp);
    free(filename);
}