#include "../header/display.h"

// Define the width of the line number column
#define LINE_NUMBER_WIDTH 6

/*
 *
 * Function name: init_display
 * Description: Initialize the display
 * Parameters: void
 * Returns: void
 *
 */
void init_display() {
  // Initialize ncurses
  initscr();

  // Make sure ESC is not interpreted as a control character
  ESCDELAY = 25;

  // Set the terminal to raw mode
  raw();

  // Allow Function Keys and Arrow Keys to be taken as input
  keypad(stdscr, TRUE);

  // Donot echo input
  noecho();

  // Allow scrolling
  scrollok(stdscr, TRUE);
}

/*
 *
 * Function name: close_display
 * Description: Close the display
 * Parameters: void
 * Returns: void
 *
 */
void close_display() { endwin(); }

/*
 *
 * Function name: render_screen
 * Description: Render the screen
 * Parameters: EditorState* state
 * Returns: void
 *
 */
void render_screen(const EditorState* state) {
  // Clear the screen
  clear();

  int screen_lines = LINES - 1;

  // For every line
  for (int i = 0; i < screen_lines; i++) {
    // Get the buffer row number
    int buffer_row = state->scroll_offset_row + i;

    // If the buffer row is within bounds
    if (buffer_row < state->total_lines) {
      // Print the line number
      mvprintw(i, 0, "%*d ", LINE_NUMBER_WIDTH - 1, buffer_row + 1);

      // Print the line
      mvaddnstr(i, LINE_NUMBER_WIDTH,
                state->buffer[buffer_row] + state->scroll_offset_col,
                COLS - LINE_NUMBER_WIDTH);
    }
  }

  // Determine the mode
  char* mode_str = (state->mode == NORMAL_MODE) ? "NORMAL" : "INSERT";

  // Print the mode
  mvprintw(LINES - 1, 0, "%s %d:%d", mode_str, state->row + 1, state->col + 1);

  // Get the screen row and column
  int screen_row = state->row - state->scroll_offset_row;
  int screen_col = state->col - state->scroll_offset_col + LINE_NUMBER_WIDTH;

  // If the screen row and column are within bounds
  if (screen_row >= 0 && screen_row < LINES - 1 &&
      screen_col >= LINE_NUMBER_WIDTH && screen_col < COLS) {
    // Move the cursor to the screen row and column
    move(screen_row, screen_col);
  }

  // Refresh the screen
  refresh();
}

/*
 *
 * Function name: adjust_scroll
 * Description: Adjust the scroll offset
 * Parameters: EditorState* state
 * Returns: void
 *
 */
void adjust_scroll(EditorState* state) {
  // Adjust the scroll offset for the main window
  if (state->row < state->scroll_offset_row) {
    // If the cursor is at the top of the page
    // then don't scroll
    state->scroll_offset_row = state->row;
  } else if (state->row >= state->scroll_offset_row + (LINES - 1)) {
    // If the cursor is at the bottom of the page
    // then scroll
    state->scroll_offset_row = state->row - (LINES - 2);
  }

  // Adjust the scroll offset for the line number column
  if (state->col < state->scroll_offset_col) {
    // If the cursor is at the left of the page
    // then don't scroll
    state->scroll_offset_col = state->col;
  } else if (state->col >=
             state->scroll_offset_col + (COLS - LINE_NUMBER_WIDTH)) {
    // If the cursor is at the right of the page
    // then scroll
    state->scroll_offset_col = state->col - (COLS - LINE_NUMBER_WIDTH - 1);
  }
}
