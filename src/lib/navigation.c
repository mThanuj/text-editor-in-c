#include "../header/navigation.h"

#include <string.h>

/*
 *
 * Function name: cursor_move_left
 * Description: Move the cursor left
 * Parameters: EditorState* s
 * Returns: void
 *
 */
void cursor_move_left(EditorState* s) {
  if (s->col > 0) {
    s->col--;
  }
}

/*
 *
 * Function name: cursor_move_right
 * Description: Move the cursor right
 * Parameters: EditorState* s
 * Returns: void
 *
 */
void cursor_move_right(EditorState* s) {
  int len = strlen(s->buffer[s->row]);
  if (s->col < len) {
    s->col++;
  }
}

/*
 *
 * Function name: cursor_move_up
 * Description: Move the cursor up
 * Parameters: EditorState* s
 * Returns: void
 *
 */
void cursor_move_up(EditorState* s) {
  if (s->row > 0) {
    s->row--;
    int len = strlen(s->buffer[s->row]);

    // If the cursor is past the end of the line, move it to the end
    if (s->col > len) {
      s->col = len;
    }
  }
}

/*
 *
 * Function name: cursor_move_down
 * Description: Move the cursor down
 * Parameters: EditorState* s
 * Returns: void
 *
 */
void cursor_move_down(EditorState* s) {
  if (s->row < s->total_lines - 1) {
    s->row++;
    int len = strlen(s->buffer[s->row]);

    // If the cursor is past the end of the line, move it to the end
    if (s->col > len) {
      s->col = len;
    }
  }
}

/*
 *
 * Function name: cursor_move_word_forward
 * Description: Move the cursor forward a word
 * Parameters: EditorState* s
 * Returns: void
 *
 */
void cursor_move_word_forward(EditorState* s) {
  char* line = s->buffer[s->row];
  int len = strlen(line);
  int row = s->row;
  int col = s->col;

  // Skip all the characters from the current position to the next space
  while (col < len && line[col] != ' ') {
    col++;
  }

  // Skip all the spaces from the next position to the next word
  while (col < len && line[col] == ' ') {
    col++;
  }

  if (col >= len) {
    // If the cursor is past the end of the line, move it to the next line
    if (row != s->total_lines - 1) {
      s->row++;
      s->col = 0;
    }

    return;
  }

  // Move the cursor to the next word
  s->row = row;
  s->col = col;
}

/*
 *
 * Function name: cursor_move_word_backward
 * Description: Move the cursor backward a word
 * Parameters: EditorState* s
 * Returns: void
 *
 */
void cursor_move_word_backward(EditorState* s) {
  char* line = s->buffer[s->row];
  int col = s->col;

  // If the cursor is at the beginning of the line, move it to the previous line
  if (col == 0) {
    // If the cursor is at the top of the page, return
    if (s->row == 0) {
      return;
    }
    s->row -= 1;
    int row = s->row;

    char* prev_line = s->buffer[row];
    int prev_len = strlen(prev_line);

    // Skip all the spaces from the end of the line to the previous word
    while (prev_len > 0 && prev_line[prev_len - 1] != ' ') {
      prev_len--;
    }

    // Move the cursor to the previous word
    s->col = prev_len;
  } else {
    // Skip all the characters from the current position to the previous space
    while (col > 0 && line[col - 1] != ' ') {
      col--;
    }

    if (s->col > 0 && line[s->col - 1] == ' ') {
      // Skip all the spaces from the previous position to the previous word
      while (col > 0 && line[col - 1] == ' ') {
        col--;
      }

      // Skip all the characters from the previous position to the previous
      // space
      while (col > 0 && line[col - 1] != ' ') {
        col--;
      }
    }

    // Move the cursor to the previous word
    s->col = col;
  }
}
