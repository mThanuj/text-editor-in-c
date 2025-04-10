#include <unistd.h>

#include "display.h"
#include "editor_state.h"
#include "input.h"

int main() {
  EditorState* state = create_editor_state();
  init_display();

  bool running = true;
  while (running) {
    int ch = getch();
    if (ch == 'q' && state->mode == NORMAL_MODE) running = false;
    handle_input(state, ch);
    render_screen(state);
  }

  close_display();
  destroy_editor_state(state);
  return 0;
}
