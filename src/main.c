#include <stdbool.h>
#include <unistd.h>

#include "header/display.h"
#include "header/editor_state.h"
#include "header/input.h"

int main(int argc, char* argv[]) {
  const char* filename = NULL;

  if (argc > 1) {
    filename = argv[1];
  }

  // Create the editor state
  EditorState* state = create_editor_state(filename);

  // Initialize the display
  init_display();

  while (true) {
    // Render the screen
    render_screen(state);

    // Get user input
    int ch = getch();
    // Check if the user wants to quit
    // User can quit if they press 'q' in normal mode
    if (ch == 'q' && state->mode == NORMAL_MODE) {
      break;
    }

    // Handle the input
    handle_input(state, ch);
  }

  // Close the display
  close_display();
  // Destroy the editor state and free memory
  destroy_editor_state(state);
  return 0;
}
