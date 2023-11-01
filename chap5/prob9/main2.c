#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file name>\n", argv[0]);
        exit(1);
    }

    FILE *file = fopen(argv[1], "r");

    if (file == NULL) {
        fprintf(stderr, "Error opening file\n");
        return 2;
    }

    char **lines = NULL;
    int line_count = 0;
    char line[256];

    while (fgets(line, sizeof(line), file) != NULL) {
        line_count++;
        lines = (char **)realloc(lines, line_count * sizeof(char *));
        lines[line_count - 1] = strdup(line);
    }

    fclose(file);

    for (int i = line_count - 1; i >= 0; i--) {
        printf("%s", lines[i]);
        free(lines[i]);
    }

    free(lines);

    return 0;
}

