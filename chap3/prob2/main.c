#include <stdio.h>
#include <string.h>
#include "copy.h"

int main() {
    char line[5][MAXLINE];
    char temp[MAXLINE]; 

    int i = 0;
    while (i < 5) {
        if (fgets(line[i], sizeof(line[i]), stdin) == NULL) {
            return 1;
        }
        size_t len = strlen(line[i]);
        if (len > 0 && line[i][len - 1] == '\n') {
            line[i][len - 1] = '\0';
        }
        i++;
    }

    for (i = 0; i < 5; i++) {
        for (int j = i + 1; j < 5; j++) {
            if (strlen(line[i]) < strlen(line[j])) {
                strcpy(temp, line[i]);
                strcpy(line[i], line[j]);
                strcpy(line[j], temp);
            }
        }
    }

    for (i = 0; i < 5; i++) {
        printf("%s\n", line[i]);
    }

    return 0;
}

