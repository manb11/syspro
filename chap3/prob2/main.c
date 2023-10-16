#include <stdio.h>
#include "copy.h" 
#include <string.h>

int main() {
    char sentences[5][MAXLINE]; 
    int lengths[5]; // 
    int max_length = 0;

    // Input 5 sentences
    for (int i = 0; i < 5; i++) {
        printf("Enter a sentence: ");
        if (fgets(sentences[i], MAXLINE, stdin) == NULL) {
            break;
        }
        lengths[i] = strlen(sentences[i]);
        if (lengths[i] > max_length) {
            max_length = lengths[i];
        }
    }


    for (int j = max_length; j > 0; j--) {
        for (int i = 0; i < 5; i++) {
            if (lengths[i] == j) {
                printf("%s", sentences[i]);
            }
        }
    }

    return 0;
}
