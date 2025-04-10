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
  int row = s->row;
  int col = s->col;

  while (col < len && line[col] != ' ') {
    col++;
  }
  while (col < len && line[col] == ' ') {
    col++;
  }

  if (col >= len) {
    if (row != s->total_lines - 1) {
      s->row++;
      s->col = 0;
    }

    return;
  }

  s->row = row;
  s->col = col;
}

void cursor_move_word_backward(EditorState* s) {
  char* line = s->buffer[s->row];
  int col = s->col;

  if (col == 0) {
    if (s->row == 0) {
      return;
    }
    s->row -= 1;
    int row = s->row;

    char* prev_line = s->buffer[row];
    int prev_len = strlen(prev_line);
    while (prev_len > 0 && prev_line[prev_len - 1] != ' ') {
      prev_len--;
    }
    s->col = prev_len;
  } else {
    while (col > 0 && line[col - 1] != ' ') {
      col--;
    }

    if (s->col > 0 && line[s->col - 1] == ' ') {
      while (col > 0 && line[col - 1] == ' ') {
        col--;
      }
      while (col > 0 && line[col - 1] != ' ') {
        col--;
      }
    }

    s->col = col;
  }
}
