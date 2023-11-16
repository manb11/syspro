#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <option>\n", argv[0]);
        return 1;
    }

    char *option = argv[1];

    if (strcmp(option, "-e") == 0) {
        if (argc < 3) {
            char **ptr;
            extern char **environ;

            for (ptr = environ; *ptr != 0; ptr++) {
                char *equalSign = strchr(*ptr, '=');

                if (equalSign != NULL) {
                    printf("%s\n", equalSign + 1);
                } else {
                    printf("%s\n", *ptr);
                }
            }
        } else {
            char *envname = argv[2];
            char *envvalue = getenv(envname);

            if (envvalue != NULL) {
                printf(envname);
                printf(" = ");
                printf("%s\n", envvalue);
            } else {
                printf("not found : %s\n", envname);
                return 1;
            }
        }
    } 
    else if (strcmp(option, "-u") == 0) 
    {
        printf("My Realistic User ID : %d(%s) \n", getuid(), getpwuid(getuid())->pw_name);
        printf("My Valid User ID : %d(%s) \n", geteuid(), getpwuid(geteuid())->pw_name);

    } 
    else if (strcmp(option, "-g") == 0)
    {
        printf("My Realistic Group ID : %d(%s) \n", getgid(), getgrgid(getgid()) -> gr_name);
        printf("My Valid Group ID : %d(%s) \n", getegid(), getgrgid(getegid()) -> gr_name);
    }
    else if (strcmp(option, "-i") == 0)
    {
        printf("My Process Number : [%d] \n", getpid());
    }
    else if (strcmp(option, "-p") == 0)
    {
        printf("My Parent Process Number : [%d] \n", getppid());
    }
    return 0;
}

