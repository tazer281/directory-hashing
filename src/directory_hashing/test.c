#include <stdio.h>
#include <stdint.h>
#include <string.h>

int main( int argc, char * argv [] ) {
    int dir1, dir2;
    uint32_t hash;

    hash = fnv(argv[1]);
    dir1 = hash & 255;
    hash = hash >> 8;
    dir2 = hash & 255;

    printf("%d/%d/%s\n", dir1, dir2, argv[1]);
}
