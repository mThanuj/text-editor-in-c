#include "navigation.h"

#include <string.h>

void cursor_move_left(EditorState* s) {
  if (s->col > 0) s->col--;
}

void cursor_move_right(EditorState* s) {
  int len = strlen(s->buffer[s->row]);
  if (s->col < len) s->col++;
}

void cursor_move_up(EditorState* s) {
  if (s->row > 0) {
    s->row--;
    int len = strlen(s->buffer[s->row]);
    if (s->col > len) s->col = len;
  }
}

void cursor_move_down(EditorState* s) {
  if (s->row < s->total_lines - 1) {
    s->row++;
    int len = strlen(s->buffer[s->row]);
    if (s->col > len) s->col = len;
  }
}

void cursor_move_word_forward(EditorState* s) {
  char* line = s->buffer[s->row];
  int len = strlen(line);
  int cur_row = s->row;
  int cur_col = s->col;

  while (cur_col < len && line[cur_col] != ' ') {
    cur_col++;
  }
  while (cur_col < len && line[cur_col] == ' ') {
    cur_col++;
  }

  if (cur_col >= len) {
    if (cur_row != s->total_lines - 1) {
      s->row++;
      s->col = 0;
    }

    return;
  }

  s->row = cur_row;
  s->col = cur_col;
}
