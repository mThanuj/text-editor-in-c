#include "../header/editor_state.h"

#include <stdio.h>
#include <stdlib.h>

/*
 *
 * Function name: create_editor_state
 * Description: Create a new editor state
 * Parameters: char*
 * Returns: EditorState*
 *
 */
EditorState* create_editor_state(const char* filename) {
  // Create the editor state
  EditorState* state = malloc(sizeof(EditorState));
  state->total_lines = 1;
  state->row = state->col = 0;
  state->mode = NORMAL_MODE;
  state->scroll_offset_row = state->scroll_offset_col = 0;
  state->filename = filename;

  // Initialize the buffer
  for (int i = 0; i < MAX_LINES; i++) {
    state->buffer[i] = calloc(MAX_COLS, sizeof(char));
  }

  if (filename != NULL) {
    FILE* fp = fopen(filename, "r");
    // If the file exists
    if (fp != NULL) {
      // Read the file
      int row = 0, col = 0;
      char ch;
      while ((ch = fgetc(fp)) != EOF && row < MAX_LINES) {
        if (ch == '\n') {
          state->buffer[row][col] = '\0';
          row++;
          col = 0;
        } else if (col < MAX_COLS - 1) {
          state->buffer[row][col++] = ch;
        }
      }
      state->total_lines = row + 1;
      fclose(fp);
    }
  }

  return state;
}

/*
 *
 * Function name: destroy_editor_state
 * Description: Destroy the editor state
 * Parameters: EditorState* state
 * Returns: void
 *
 */
void destroy_editor_state(EditorState* state) {
  // Free the buffer
  for (int i = 0; i < MAX_LINES; i++) {
    free(state->buffer[i]);
  }

  // Free the editor state
  free(state);
}
