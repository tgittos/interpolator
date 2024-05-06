#include "include/interpolate.h"

char **get_interpolations(char *str, int *n_matches) {
  regex_t regex;
  int reti;
  char msgbuf[100];
  size_t nmatch = 1;
  regmatch_t pmatch[nmatch];

  // Compile regular expression
  reti = regcomp(&regex, "\\$\\{[^}]*\\}", 0);
  if (reti) {
    fprintf(stderr, "Could not compile regex\n"); exit(1);
  }

  // Execute regular expression
  char **matches = NULL;
  int n = 0;
  char *s = str;
  while (1) {
    reti = regexec(&regex, s, nmatch, pmatch, 0);
    if (reti == REG_NOMATCH) {
      break;
    } else if (reti) {
      regerror(reti, &regex, msgbuf, sizeof(msgbuf));
      fprintf(stderr, "Regex match failed: %s\n", msgbuf);
      exit(1);
    }
    int len = pmatch[0].rm_eo - pmatch[0].rm_so;
    char *match = malloc(len + 1);
    strncpy(match, s + pmatch[0].rm_so, len);
    match[len] = '\0';
    matches = realloc(matches, (n + 1) * sizeof(char *));
    matches[n] = match;
    n++;
    s += pmatch[0].rm_eo;
  }

  regfree(&regex);

  *n_matches = n;
  return matches;
}

// write a c function to take an array of interpolations and return a string
// with the interpolations replaced by the values in the given dictionary
char *interpolate(char *str, char **interpolations, int n_interpolations, char **values) {
  char *result = malloc(1);
  result[0] = '\0';
  char *s = str;
  for (int i = 0; i < n_interpolations; i++) {
    char *interpolation = interpolations[i];
    char *value = NULL;
    for (int j = 0; values[j] != NULL; j += 2) {
      if (strcmp(values[j], interpolation + 2) == 0) {
        value = values[j + 1];
        break;
      }
    }
    if (value == NULL) {
      fprintf(stderr, "No value found for interpolation %s\n", interpolation);
      exit(1);
    }
    int len = interpolation - s;
    result = realloc(result, strlen(result) + len + strlen(value) + 1);
    strncat(result, s, len);
    strcat(result, value);
    s = interpolation + strlen(interpolation);
  }
  strcat(result, s);
  return result;
}

