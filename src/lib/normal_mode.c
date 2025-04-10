#include "../header/normal_mode.h"

#include "../header/display.h"
#include "../header/file.h"
#include "../header/navigation.h"

/*
 *
 * Function name: normal_mode_handle
 * Description: Handle user input in normal mode
 * Parameters: EditorState* s, int ch
 * Returns: void
 *
 */
void normal_mode_handle(EditorState* s, int ch) {
  switch (ch) {
    case 'i':
      // Switch to insert mode
      s->mode = INSERT_MODE;
      s->status_msg = NULL;
      break;
    case 'h':
      // Move the cursor left
      cursor_move_left(s);
      break;
    case 'l':
      // Move the cursor right
      cursor_move_right(s);
      break;
    case 'j':
      // Move the cursor down
      cursor_move_down(s);
      break;
    case 'k':
      // Move the cursor up
      cursor_move_up(s);
      break;
    case 'w':
      // Move the cursor forward a word
      cursor_move_word_forward(s);
      break;
    case 'b':
      // Move the cursor backward a word
      cursor_move_word_backward(s);
      break;
    case 's':
      save_file(s);
      break;
  }
  adjust_scroll(s);
}
