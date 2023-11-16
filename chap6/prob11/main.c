#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <grp.h>
#include <pwd.h>
#include <string.h>
#include <dirent.h>

char type(mode_t);
char *perm(mode_t);
void printStat(char*, char*, struct stat*, int, char**);

int main(int argc, char **argv)
{
    DIR *dp;
    char *dir;
    struct stat st;
    struct dirent *d;
    char path[BUFSIZ + 1];
    if (argc == 1)
        dir = ".";
    else
        dir = argv[1];

    if ((dp = opendir(dir)) == NULL) // 디렉터리 열기
        perror(dir);

    while ((d = readdir(dp)) != NULL)
    {
        sprintf(path, "%s/%s", dir, d->d_name); // 파일 경로 생성
        if (lstat(path, &st) < 0)                  // 파일 정보 읽기
            perror(path);
        else
            printStat(path, d->d_name, &st, argc, argv); // 파일 정보 출력
    }

    closedir(dp);
    exit(0);
}

void printStat(char *pathname, char *file, struct stat *st, int argc, char **argv)
{
    // 옵션에 따라 출력
    if (argc > 1 && strcmp(argv[1], "-i") == 0)
        printf("%5ld ", (long)st->st_ino); // inode 번호 출력

    if (argc > 1 && strcmp(argv[1], "-p") == 0)
        printf("%s%s ", type(st->st_mode) == 'd' ? "/" : "", file); // 파일의 상대경로 출력, 디렉터리에는 슬래시 추가
    else if (argc > 1 && strcmp(argv[1], "-Q") == 0)
        printf("\"%s\" ", realpath(pathname, NULL)); // 파일의 절대경로 출력, 디렉터리에는 따옴표 추가
    else
        printf("%s ", pathname); // 기본적으로는 파일 경로 출력

    printf("%c%s ", type(st->st_mode), perm(st->st_mode));
    printf("%3ld ", (long)st->st_nlink);
    printf("%s %s ", getpwuid(st->st_uid)->pw_name,
           getgrgid(st->st_gid)->gr_name);
    printf("%9ld ", (long)st->st_size);
    printf("%.12s ", ctime(&st->st_mtime) + 4);
    printf("%s\n", file);
}

char type(mode_t mode)
{
    if (S_ISREG(mode))
        return ('-');
    if (S_ISDIR(mode))
        return ('d');
    if (S_ISCHR(mode))
        return ('c');
    if (S_ISBLK(mode))
        return ('b');
    if (S_ISLNK(mode))
        return ('l');
    if (S_ISFIFO(mode))
        return ('p');
    if (S_ISSOCK(mode))
        return ('s');
}

char *perm(mode_t mode)
{
    static char perms[10];
    strcpy(perms, "---------");

    for (int i = 0; i < 3; i++)
    {
        if (mode & (S_IRUSR >> i * 3))
            perms[i * 3] = 'r';
        if (mode & (S_IWUSR >> i * 3))
            perms[i * 3 + 1] = 'w';
        if (mode & (S_IXUSR >> i * 3))
            perms[i * 3 + 2] = 'x';
    }
    return (perms);
}

