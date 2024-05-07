#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define DELIMITER_SIZE 3 // ${}

int main(int argc, char **argv) {
    FILE *input;
    char buffer[1024];
    char *token;
    char *label;
    char *value;
    size_t delimiter_size = DELIMITER_SIZE;

    if (argc == 1) {
        // No command line argument, read from stdin
        input = stdin;
    } else if (argc == 2) {
        // One command line argument, read from file
        input = fopen(argv[1], "r");
        if (input == NULL) {
            perror("Error opening file");
            return 1;
        }
    } else {
        fprintf(stderr, "Usage: %s [file]\n", argv[0]);
        return 1;
    }

    while (fgets(buffer, sizeof(buffer), input)!= NULL) {
        token = strtok(buffer, " \t\n");
        while (token!= NULL) {
            if (strncmp(token, "${", delimiter_size) == 0 && strlen(token) > delimiter_size) {
                label = token + delimiter_size;
                value = getenv(label);
                if (value!= NULL) {
                    printf("%s", value);
                } else {
                    printf("%s", token);
                }
            } else {
                printf("%s", token);
            }
            token = strtok(NULL, " \t\n");
            printf(" ");
        }
        printf("\n");
    }

    if (argc == 2) {
        fclose(input);
    }

    return 0;
}
