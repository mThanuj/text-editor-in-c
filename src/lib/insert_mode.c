#include "insert_mode.h"

#include "buffer.h"
#include "display.h"

void insert_mode_handle(EditorState* s, int ch) {
  switch (ch) {
    case 27:
      s->mode = NORMAL_MODE;
      break;
    case KEY_BACKSPACE:
      if (s->col > 0)
        buffer_delete_char(s);
      else if (s->row > 0)
        buffer_merge_line(s);
      break;
    case '\n':
      buffer_split_line(s);
      break;
    default:
      if (ch >= 32 && ch <= 126) buffer_insert_char(s, ch);
      break;
  }
  adjust_scroll(s);
}
