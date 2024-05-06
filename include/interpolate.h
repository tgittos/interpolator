#include <sys/types.h>
#include <stdio.h>
#include <regex.h>

char **get_interpolations(char *str, int *n_matches);

char *interpolate(char *str, char **interpolations, int n_interpolations, char **values);
