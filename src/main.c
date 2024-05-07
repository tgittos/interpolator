#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_VAR_NAME 256
#define MAX_INTERPOLATED 1024

char *getenv_var(const char *var_name)
{
    char *value = getenv(var_name);
    if (value == NULL)
    {
        return ""; // or some other default value
    }
    return value;
}

char *interpolate(const char *input)
{
    char *interpolated = malloc(MAX_INTERPOLATED);
    char *p = input;
    char *q = interpolated;
    while (*p != '\0')
    {
        if (*p == '$' && *(p + 1) == '{')
        {
            p += 2; // skip ${
            char var_name[MAX_VAR_NAME];
            int i = 0;
            while (*p != '}' && i < MAX_VAR_NAME)
            {
                var_name[i] = *p;
                p++;
                i++;
            }
            var_name[i] = '\0';
            if (*p != '}')
            {
                fprintf(stderr, "Error: invalid variable syntax\n");
                exit(1);
            }
            p++; // skip }
            char *value = getenv_var(var_name);
            while (*value != '\0')
            {
                *q++ = *value++;
            }
        }
        else
        {
            *q++ = *p++;
        }
    }
    *q = '\0';
    return interpolated;
}

int main(int argc, char *argv[])
{
    FILE *input_file = stdin;
    if (argc > 1)
    {
        input_file = fopen(argv[1], "r");
        if (input_file == NULL)
        {
            fprintf(stderr, "Error: unable to open file %s\n", argv[1]);
            exit(1);
        }
    }

    char buffer[1024];
    while (fgets(buffer, 1024, input_file) != NULL)
    {
        char *interpolated = interpolate(buffer);
        printf("%s", interpolated);
        free(interpolated);
    }

    if (argc > 1)
    {
        fclose(input_file);
    }
    return 0;
}
