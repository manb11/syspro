#include <stdio.h>
#include <string.h>
#include "copy.h"

int main() {
<<<<<<< HEAD
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
=======
    char sentences[5][MAXLINE]; 
    int lengths[5]; 
    int max_length = 0;

    // Input 5 
    for (int i = 0; i < 5; i++) {
        printf("Enter a sentence: ");
        if (fgets(sentences[i], MAXLINE, stdin) == NULL) {
            break;
        }
        lengths[i] = strlen(sentences[i]);
        if (lengths[i] > max_length) {
            max_length = lengths[i];
        }
>>>>>>> 5c0fb1e668774b1b35aecef8189411e7b47d6812
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

<<<<<<< HEAD
    for (i = 0; i < 5; i++) {
        printf("%s\n", line[i]);
=======
    for (int j = max_length; j > 0; j--) {
        for (int i = 0; i < 5; i++) {
            if (lengths[i] == j) {
                printf("%s", sentences[i]);
            }
        }
>>>>>>> 5c0fb1e668774b1b35aecef8189411e7b47d6812
    }

    return 0;
}

