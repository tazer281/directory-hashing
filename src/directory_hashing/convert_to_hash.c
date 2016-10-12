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

int main(int argc, char* argv[])
{
  
  int dir1, dir2, i, filenameLength, len, res;
  uint32_t hash;
  char *c, *tmp, newChar, *filename, ch, buffer[3];
  FILE *fp, *source;
  struct stat sb, st;
  struct dirent *cur;
  DIR* pd;
	pd = opendir(argv[1]);
  
    while (cur = readdir(pd)) {
        if (*cur->d_name != '.') {
					if (stat(cur->d_name, &sb) == 0 && !S_ISDIR(sb.st_mode)) {
					  puts(cur->d_name);

						c = calloc(1, sizeof(char));
						tmp = calloc(1, sizeof(char));
						filename = calloc(1, sizeof(char));

							c = cur->d_name;
							hash = fnv(c);
							dir1 = hash & 255;
							hash = hash >> 8;
							dir2 = hash & 255;

							filename = realloc(filename, strlen(argv[1]) + 8 + strlen(c));
							strcpy(filename, argv[1]);
							sprintf(buffer, "%d", dir1);
							strcat(filename, "/");						
							strcat(filename, buffer);

							if (stat(filename, &st) == -1) {
								mkdir(filename, 0777);
							}

							strcat(filename, "/");
							sprintf(buffer, "%d", dir2);
							strcat(filename, buffer);

							if (stat(filename, &st) == -1) {
								mkdir(filename, 0777);
							}

							strcat(filename, "/");
							strcat(filename, c);

							fp = fopen(filename, "ab+");
							fclose(fp);
    	   	}	
			}
 
	}
  	return(0);
}

