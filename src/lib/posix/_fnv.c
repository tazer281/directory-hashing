#include <string.h>
#include <stdint.h>

const uint32_t FNV_OFFSET = 216613261U;
const uint32_t FNV_PRIME = 4294967291U;

uint32_t fnv(char *c) {
    uint32_t hash = FNV_OFFSET, i;
    for (i = 0; i < strlen(c); i++) {
        hash = (hash ^ (c[i])) * FNV_PRIME;
    }
    return hash;
}