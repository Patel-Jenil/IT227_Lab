#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>
#include <libgen.h>

// as argv[2] provide the path for the hardlink that you want to create and in argv[3] provide path for softlink
int main(int argc, char *argv[])
{

    int x = link(argv[1], argv[2]);
    if (x == 0)
    {
        printf("Success! Hard Link created.\n");
    }
    else
    {
        printf("Failure! Hard Link NOT created.\n");
    }

    int y = symlink(argv[1], argv[3]);
    if (y == 0)
    {
        printf("Success! Soft Link created.\n");
    }
    else
    {
        printf("Failure! Soft Link NOT created.\n");
    }
    return 0;
}
