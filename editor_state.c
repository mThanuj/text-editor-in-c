#include "editor_state.h"

#include <stdlib.h>

EditorState* create_editor_state() {
  EditorState* state = malloc(sizeof(EditorState));
  state->total_lines = 1;
  state->row = state->col = 0;
  state->mode = NORMAL_MODE;
  state->scroll_offset_row = state->scroll_offset_col = 0;

  for (int i = 0; i < MAX_LINES; i++) {
    state->buffer[i] = calloc(MAX_COLS, sizeof(char));
  }
  return state;
}

void destroy_editor_state(EditorState* state) {
  for (int i = 0; i < MAX_LINES; i++) {
    free(state->buffer[i]);
  }
  free(state);
}
