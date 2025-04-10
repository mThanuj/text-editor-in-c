#include "input.h"

#include "insert_mode.h"
#include "normal_mode.h"

void handle_input(EditorState* state, int ch) {
  switch (state->mode) {
    case NORMAL_MODE:
      normal_mode_handle(state, ch);
      break;
    case INSERT_MODE:
      insert_mode_handle(state, ch);
      break;
  }
}
