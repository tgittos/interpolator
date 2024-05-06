#include "include/file.h"

char *read_file(char *path) {
  FILE *file = fopen(path, "r");
  if (file == NULL) {
    fprintf(stderr, "Failed to open file %s\n", path);
    exit(1);
  }
  fseek(file, 0, SEEK_END);
  long size = ftell(file);
  rewind(file);
  char *contents = malloc(size + 1);
  fread(contents, 1, size, file);
  contents[size] = '\0';
  fclose(file);
  return contents;
}

void write_file(char *path, char *contents) {
  FILE *file = fopen(path, "w");
  if (file == NULL) {
    fprintf(stderr, "Failed to open file %s\n", path);
    exit(1);
  }
  fwrite(contents, 1, strlen(contents), file);
  fclose(file);
}
