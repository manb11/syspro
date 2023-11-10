#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <grp.h>
#include <pwd.h>
#include <dirent.h>


void printStat(char *, char *, struct stat *);
void printFileInfo(char *dir, char *file, int option);

int main(int argc, char **argv)
{
    DIR *dp;
    char *dir;
    struct stat st;
    struct dirent *d;
    char path[BUFSIZ + 1];
    int option = 0;

    // Parse command line options
    if (argc > 1)
    {
        for (int i = 1; i < argc; ++i)
        {
            if (strcmp(argv[i], "-i") == 0)
            {
                option |= 1; // Set the first bit
            }
            else if (strcmp(argv[i], "-p") == 0)
            {
                option |= 2; // Set the second bit
            }
            else if (strcmp(argv[i], "-Q") == 0)
            {
                option |= 4; // Set the third bit
            }
        }
    }

    if (argc <= 1)
    {
        dir = ".";
    }
    else
    {
        dir = argv[argc - 1];
    }

    if ((dp = opendir(dir)) == NULL)
    {
        perror(dir);
        exit(EXIT_FAILURE);
    }

    while ((d = readdir(dp)) != NULL)
    {
        sprintf(path, "%s/%s", dir, d -> d_name);
        if (lstat(path, &st) < 0)
        {
            perror(path);
        }
        else
        {
            printFileInfo(dir, d -> d_name, option);
        }
    }

    closedir(dp);
    exit(EXIT_SUCCESS);
}

void printFileInfo(char *dir, char *file, int option)
{
    struct stat st;
    char path[BUFSIZ + 1];
    sprintf(path, "%s/%s", dir, file);

    if (lstat(path, &st) < 0)
    {
        perror(path);
    }
    else
    {
        switch (option)
        {
        case 1:
            // Handle -i option
            printf("%lu ", st.st_ino);
            break;
        case 2:
            // Handle -p option
            printf("%s%c ", file, (S_ISDIR(st.st_mode) ? '/' : ' '));
            break;
        case 4:
            // Handle -Q option
            printf("\"%s\" ", file);
            break;
        default:
            // Default behavior without any option
            printStat(path, file, &st);
            break;
        }
    }

void printStat(char *pathname, char *file, struct stat *st)
{
    printf("%5d ", st -> st_blocks);
    printf("%c%s ", type(st -> st_mode), perm(st -> st_mode));
    printf("%3d ", st -> st_nlink);
    printf("%s %s ", getpwuid(st -> st_uid)->pw_name, getgrgid(st -> st_gid)->gr_name);
    printf("%9d ", st -> st_size);
    printf("%.12s ", ctime(&st -> st_mtime) + 4);
    printf("%s\n", file);
}

}

// The rest of the code remains unchanged

