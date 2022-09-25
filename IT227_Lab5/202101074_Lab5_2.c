#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>
#include <libgen.h>
#include <errno.h>
#include <string.h>

#define RESET "\033[0m"
#define B_GREEN "\033[1m\033[32m"

void cat(char *file)
{

	FILE *p;
	if ((p = fopen(file, "r")) == NULL)
	{
		if (errno == ENOENT)
		{
			fprintf(stderr, "%s path or file DOES NOT EXIST", file);
			return;
		}
		else
		{
			fprintf(stderr, "%s cannot be opened in read mode", file);
			return;
		}
	}

	char ch;
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

void ls(char *dir_add)
{
	DIR *dir_ptr;
	struct dirent *direntp;
	dir_ptr = opendir(dir_add);
	if (dir_ptr == NULL)
	{
		fprintf(stderr, "Cannot open directory!!!\n");
		exit(1);
	}

	while ((direntp = readdir(dir_ptr)) != NULL)
	{
		printf("%s\n", direntp->d_name);
	}
	return;
}

void mv(char *src, char *dst)
{
	struct stat st;
	stat(dst, &st);
	if (S_ISREG(st.st_mode))
	{
		// printf("%s is regular file\n", argv[1]);
		rename(src, dst);
	}
	else if (S_ISDIR(st.st_mode))
	{
		// printf("%s is a directory\n", argv[1]);
		char newp[500];
		sprintf(newp, "%s/%s", dst, basename(src));
		rename(src, newp);
	}
}

int main(int argc, char const *argv[])
{
	char cmd[50];
	do
	{
		char host[25];
		char user[25];
		char p1[50];
		char p2[50];

		gethostname(host, 25);
		getlogin_r(user, sizeof(user));
		printf(B_GREEN "myshell@%s@%s$", user, host);
		printf(RESET " ");

		scanf("%s", cmd);
		fflush(stdin);

		if (!strcmp(cmd, "cat"))
		{
			scanf("%s", p1);
			cat(p1);
		}

		else if (!strcmp(cmd, "mv"))
		{
			scanf("%s", p1);
			scanf("%s", p2);
			mv(p1, p2);
		}

		else if (!strcmp(cmd, "ls"))
		{
			scanf("%s", p1);
			ls(p1);
		}

		else
		{
			printf("%s command not found.\n", cmd);
		}

	} while (strcmp(cmd, "exit"));

	return 0;
}
