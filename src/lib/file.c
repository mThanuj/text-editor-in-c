#include "../header/file.h"

#include <stdio.h>

void save_file(EditorState* s) {
  if (s->filename == NULL) {
    return;
  }

  FILE* fp = fopen(s->filename, "w");
  if (fp == NULL) {
    return;
  }

  for (int i = 0; i < s->total_lines; i++) {
    fprintf(fp, "%s\n", s->buffer[i]);
  }

  fclose(fp);
  s->status_msg = "File saved";
}
