#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int line_number = 1;
    int print_line_numbers = 0;

    if (argc < 2) {
        printf("Usage: %s [-n] file1 file2 ...\n", argv[0]);
        return 1;
    }

    int arg_index = 1;

    if (argc > 2 && strcmp(argv[1], "-n") == 0) {
        print_line_numbers = 1;
        arg_index = 2;
    }

    for (; arg_index < argc; arg_index++) {
        FILE *fp = fopen(argv[arg_index], "r");
        if (fp == NULL) {
            fprintf(stderr, "Error opening file: %s\n", argv[arg_index]);
            continue;
        }

        char line[1024];
        while (fgets(line, sizeof(line), fp) != NULL) {
            if (print_line_numbers) {
                printf("%d ", line_number);
            }
            printf("%s", line);
            line_number++;
        }

        fclose(fp);
    }

    return 0;
}

