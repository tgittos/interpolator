#include <file.h>
#include <interpolate.h>

int main(int argc, char **argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <file>\n", argv[0]);
    exit(1);
  }

  // open the file and read its contents
  char *path = argv[1];
  char *contents = read_file

  // fetch all interpolations from the contents
  char *interpolations = get_interpolations(contents, &n_interpolations);

  // loop through the interpolates and get their values from the environment
  // and store them in a dictionary
  char **values = NULL;
  for (int i = 0; i < n_interpolations; i++) {
    char *interpolation = interpolations[i];
    char *value = getenv(interpolation + 2);
    if (value == NULL) {
      fprintf(stderr, "Environment variable %s not set\n", interpolation + 2);
      exit(1);
    }
    values = realloc(values, (i + 2) * sizeof(char *));
    values[i] = interpolation;
    values[i + 1] = value;
  }

  // interpolate in the values from the environment dictionary
  char *result = interpolate(contents, interpolations, n_interpolations, values);

  // output the result to stdout
  write_file(stdout, result);

  return 0;
}
