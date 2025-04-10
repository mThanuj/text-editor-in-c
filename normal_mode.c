#include "normal_mode.h"

#include "display.h"
#include "navigation.h"

void normal_mode_handle(EditorState* s, int ch) {
  switch (ch) {
    case 'i':
      s->mode = INSERT_MODE;
      break;
    case 'h':
      cursor_move_left(s);
      break;
    case 'l':
      cursor_move_right(s);
      break;
    case 'j':
      cursor_move_down(s);
      break;
    case 'k':
      cursor_move_up(s);
      break;
    case 'w':
      cursor_move_word_forward(s);
      break;
  }
  adjust_scroll(s);
}
