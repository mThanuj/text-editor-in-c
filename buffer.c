#include "buffer.h"

#include <string.h>

void buffer_insert_char(EditorState* s, char ch) {
  if (s->col >= MAX_COLS - 1) return;

  int current_len = strlen(s->buffer[s->row]);
  if (s->col > current_len) {
    int pad = s->col - current_len;
    memset(s->buffer[s->row] + current_len, ' ', pad);
    s->buffer[s->row][current_len + pad] = '\0';
  }

  memmove(&s->buffer[s->row][s->col + 1], &s->buffer[s->row][s->col],
          strlen(s->buffer[s->row]) - s->col + 1);
  s->buffer[s->row][s->col] = ch;
  s->col++;
}

void buffer_delete_char(EditorState* s) {
  int current_len = strlen(s->buffer[s->row]);
  if (s->col > 0) {
    memmove(&s->buffer[s->row][s->col - 1], &s->buffer[s->row][s->col],
            current_len - s->col + 1);
    s->col--;
  }
}

void buffer_split_line(EditorState* s) {
  if (s->total_lines >= MAX_LINES) return;

  for (int i = s->total_lines; i > s->row + 1; i--) {
    strcpy(s->buffer[i], s->buffer[i - 1]);
  }
  strcpy(s->buffer[s->row + 1], &s->buffer[s->row][s->col]);
  s->buffer[s->row][s->col] = '\0';
  s->total_lines++;
  s->row++;
  s->col = 0;
}

void buffer_merge_line(EditorState* s) {
  if (s->row == 0) return;

  int prev_len = strlen(s->buffer[s->row - 1]);
  strcat(s->buffer[s->row - 1], s->buffer[s->row]);

  for (int i = s->row; i < s->total_lines - 1; i++) {
    strcpy(s->buffer[i], s->buffer[i + 1]);
  }
  s->total_lines--;
  s->row--;
  s->col = prev_len;
}
