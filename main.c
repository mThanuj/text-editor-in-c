#include <stdbool.h>
#include <unistd.h>

#include "display.h"
#include "editor_state.h"
#include "input.h"

int main() {
  EditorState* state = create_editor_state();
  init_display();

  while (true) {
    render_screen(state);
    int ch = getch();
    if (ch == 'q' && state->mode == NORMAL_MODE) {
      break;
    }

    handle_input(state, ch);
  }

  close_display();
  destroy_editor_state(state);
  return 0;
}
