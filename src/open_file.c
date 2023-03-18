#include "open_file.h"


FILE* open_file(char *file_name, char *mode, size_t *sz) {
  FILE *f = fopen(file_name, mode);
  if (!f) {
    goto open_file_error;
  }

  if (sz) {
    fseek(f, 0, SEEK_END);
    *sz = ftell(f);
    fseek(f, 0, SEEK_SET);
  }

  return f;

  open_file_error:
  fprintf(stderr, "Open file error: '%s'\n", file_name);
  exit(2);

}


