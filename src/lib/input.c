#include "../header/input.h"

#include "../header/insert_mode.h"
#include "../header/normal_mode.h"

/*
 *
 * Function name: handle_input
 * Description: Handle user input
 * Parameters: EditorState* state, int ch
 * Returns: void
 *
 */
void handle_input(EditorState* state, int ch) {
  // Handle the input
  switch (state->mode) {
    // Handle input in normal mode
    case NORMAL_MODE:
      normal_mode_handle(state, ch);
      break;
    // Handle input in insert mode
    case INSERT_MODE:
      insert_mode_handle(state, ch);
      break;
  }
}
