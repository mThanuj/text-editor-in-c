#include "../header/insert_mode.h"

#include "../header/buffer.h"
#include "../header/display.h"

/*
 *
 * Function name: insert_mode_handle
 * Description: Handle user input in insert mode
 * Parameters: EditorState* s, int ch
 * Returns: void
 *
 */
void insert_mode_handle(EditorState* s, int ch) {
  // Handle the input
  switch (ch) {
    case 27:
      // Switch to normal mode if the user presses escape
      s->mode = NORMAL_MODE;
      break;
    case KEY_BACKSPACE:
      if (s->col > 0)
        // Delete the character before the cursor
        buffer_delete_char(s);
      else if (s->row > 0)
        // Merge the current line with the previous line
        buffer_merge_line(s);
      break;
    case '\n':
      // Split the current line into two lines
      buffer_split_line(s);
      break;
    default:
      if (ch >= 32 && ch <= 126) {
        // Insert the character into the buffer
        buffer_insert_char(s, ch);
      }
      break;
  }

  // Adjust the scroll offset based on the cursor position
  adjust_scroll(s);
}
