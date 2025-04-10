#include "../header/buffer.h"

#include <string.h>

/*
 *
 * Function name: buffer_insert_char
 * Description: Insert a character into the buffer
 * Parameters: EditorState* s, char ch
 * Returns: void
 *
 */
void buffer_insert_char(EditorState* s, char ch) {
  // If the cursor is at the end of the line, return
  if (s->col >= MAX_COLS - 1) {
    return;
  }

  // Check if the cursor is at the end of the current line
  int current_len = strlen(s->buffer[s->row]);

  // If the cursor is at the end of the current line, add padding
  if (s->col > current_len) {
    int pad = s->col - current_len;

    // Add padding to the current line by filling it with spaces
    memset(s->buffer[s->row] + current_len, ' ', pad);

    // Add the string terminator to the end of the line
    s->buffer[s->row][current_len + pad] = '\0';
  }

  // Shift the characters after the cursor to the right
  memmove(&s->buffer[s->row][s->col + 1], &s->buffer[s->row][s->col],
          strlen(s->buffer[s->row]) - s->col + 1);

  // Insert the new character
  s->buffer[s->row][s->col] = ch;

  // Move the cursor to the right
  s->col++;
}

/*
 *
 * Function name: buffer_delete_char
 * Description: Delete a character from the buffer
 * Parameters: EditorState* s
 * Returns: void
 *
 */
void buffer_delete_char(EditorState* s) {
  int current_len = strlen(s->buffer[s->row]);

  // Shift the characters after the cursor to the left
  if (s->col > 0) {
    memmove(&s->buffer[s->row][s->col - 1], &s->buffer[s->row][s->col],
            current_len - s->col + 1);

    // Move the cursor to the left
    s->col--;
  }
}

/*
 *
 * Function name: buffer_split_line
 * Description: Split the current line into two lines
 * Parameters: EditorState* s
 * Returns: void
 *
 */
void buffer_split_line(EditorState* s) {
  // If the cursor is at the end of the page, return
  if (s->total_lines >= MAX_LINES) {
    return;
  }

  // Shift the characters after the cursor to the next line
  for (int i = s->total_lines; i > s->row + 1; i--) {
    strcpy(s->buffer[i], s->buffer[i - 1]);
  }

  // Split the line
  strcpy(s->buffer[s->row + 1], &s->buffer[s->row][s->col]);

  // Add the string terminator to the end of the line
  s->buffer[s->row][s->col] = '\0';

  // Increment the total lines used
  s->total_lines++;

  // Move the cursor to the next line
  s->row++;

  // Move the cursor to the start of the next line
  s->col = 0;
}

/*
 *
 * Function name: buffer_merge_line
 * Description: Merge the current line with the previous line
 * Parameters: EditorState* s
 * Returns: void
 *
 */
void buffer_merge_line(EditorState* s) {
  // If the cursor is at the top of the page, return
  if (s->row == 0) {
    return;
  }

  int prev_len = strlen(s->buffer[s->row - 1]);

  // Merge the lines
  strcat(s->buffer[s->row - 1], s->buffer[s->row]);

  // Shift the characters after the cursor to the previous line
  for (int i = s->row; i < s->total_lines - 1; i++) {
    strcpy(s->buffer[i], s->buffer[i + 1]);
  }

  // Decrement the total lines used
  s->total_lines--;

  // Move the cursor to the previous line
  s->row--;

  // Move the cursor to the end of the previous line
  s->col = prev_len;
}
