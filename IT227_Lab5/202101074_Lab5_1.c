#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>
#include <libgen.h>
#include <errno.h>

void cat(const char *file)
{
    FILE *p;
    char ch;

    if ((p = fopen(file, "r")) == NULL)
    {
        if (errno == ENOENT)
        {
            fprintf(stderr, "%s path or file does not exist", file);
            return;
        }
        else
        {
            fprintf(stderr, "%s cannot be opened in read mode", file);
            return;
        }
    }
    while (1)
    {
        ch = fgetc(p);
        if (ch == EOF)
        {
            break;
        }
        printf("%c", ch);
    }
    fclose(p);
}

void ls(const char *directory)
{
    DIR *dir_ptr;
    struct dirent *direntp;
    dir_ptr = opendir(directory);

    if (dir_ptr == NULL)
    {
        fprintf(stderr, "Cannot open directory!\n");
        exit(1);
    }

    while ((direntp = readdir(dir_ptr)) != NULL)
    {
        printf("%s\n", direntp->d_name);
    }
    return;
}

void mv(char *src, const char *dest)
{
    struct stat st;
    stat(dest, &st);
    if (S_ISREG(st.st_mode))
    {
        // printf("%s is regular file\n", argv[1]);
        rename(src, dest);
    }
    else if (S_ISDIR(st.st_mode))
    {
        // printf("%s is a directory\n", argv[1]);
        char newp[500];
        sprintf(newp, "%s/%s", dest, basename(src));
        rename(src, newp);
    }
}

int main(int argc, char const *argv[])
{

    int choice = 0;
    printf("Enter:\n1 - to use cat function.\n2 - to use ls function.\n3 - to use mv function.\n4 - to exit\n");
    scanf("%d", &choice);
    fflush(stdin);

    switch (choice)
    {

    case 1:
    { // cat command
        if (argc != 2)
        {
            printf("Not enough arguments were passed to run this function.\n");
            fprintf(stdout, "Usage: Q1.out file/dir_path \n");
            exit(1);
        }
        cat(argv[1]);
        break;
    }

    case 2:
    { // ls command
        if (argc != 2)
        {
            printf("Not enough arguments were passed to run this function.\n");
            fprintf(stdout, "Usage: Q1.out file/dir_path \n");
            exit(1);
        }
        ls(argv[1]);
        break;
    }

    case 3:
    { // mv command
        if (argc != 3)
        {
            printf("Not enough arguments were passed to run this function.\n");
            fprintf(stdout, "Usage: Q1.out source_path destination_path \n");
            exit(1);
        }
        mv(argv[1], argv[2]);
        break;
    }

    case 4:
    { // exit command
        printf("You have successfully exited the programme.\n");
        exit(0);
        break;
    }

    default:
        printf("Please select a valid choice!\n\n Run the program again\n");
        exit(1);
    }

    return 0;
}
