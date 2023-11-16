#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <option>\n", argv[0]);
        return 1;
    }

    char *option = argv[1];


    char **ptr;
    extern char **environ;


    if (strcmp(option, "-e") == 0) 
    {
        for(ptr = environ; *ptr != 0; ptr++)
        {
            char *equalSign = strchr(*ptr, '=');

            if (equalSign != NULL)
            {
                printf("%s\n", equalSign+1);
            }
            else
            {
                printf("%s\n", *ptr);
            }
        }
    } 
    else if (strcmp(option, "-v") == 0 || strcmp(option, "--version") == 0) {
        printf("Version 1.0\n");
    } else {
        printf("Invalid option: %s\n", option);
        return 1;
    }

    return 0;
}

