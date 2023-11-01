#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    FILE *file;
    char **lines = NULL;
    int line_count = 0;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file name>\n", argv[0]);
        exit(1);
    }

    if ((file = fopen(argv[1], "r")) == NULL) {
        fprintf(stderr, "Error opening file\n");
        return 2;
    }

    char line[256];
    while (fgets(line, sizeof(line), file) != NULL) {
        line_count++;
        lines = (char **)realloc(lines, line_count * sizeof(char *));
        lines[line_count - 1] = strdup(line);
    }

    fclose(file);

    printf("Enter line numbers or range (* for all lines): ");
    char input[256];
    scanf("%s", input);

    if (input[0] == '*') {
        for (int i = 0; i < line_count; i++) {
            printf("%s", lines[i]);
            free(lines[i]);
            lines[i] = NULL; // Set the pointer to NULL after freeing
        }
    } else {
        char *token = strtok(input, ",");
        while (token != NULL) {
            int start_line, end_line;
            if (sscanf(token, "%d-%d", &start_line, &end_line) == 2) {
                for (int i = start_line - 1; i <= end_line - 1; i++) {
                    if (i >= 0 && i < line_count) {
                        printf("%s", lines[i]);
                        free(lines[i]);
                        lines[i] = NULL; // Set the pointer to NULL after freeing
                    }
                }
            } else {
                int target_line = atoi(token);
                if (target_line >= 1 && target_line <= line_count) {
                    printf("%s", lines[target_line - 1]);
                    free(lines[target_line - 1]);
                    lines[target_line - 1] = NULL; // Set the pointer to NULL after freeing
                }
            }
            token = strtok(NULL, ",");
        }
    }

    free(lines); // Free the array of pointers

    return 0;
}

