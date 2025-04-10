#include "display.h"

void init_display() {
  initscr();
  ESCDELAY = 25;
  raw();
  keypad(stdscr, TRUE);
  noecho();
  scrollok(stdscr, TRUE);
}

void close_display() { endwin(); }

void render_screen(const EditorState* state) {
  clear();
  int screen_lines = LINES - 1;

  for (int i = 0; i < screen_lines; i++) {
    int buffer_row = state->scroll_offset_row + i;
    if (buffer_row < state->total_lines) {
      mvaddnstr(i, 0, state->buffer[buffer_row] + state->scroll_offset_col,
                COLS);
    }
  }

  char* mode_str = (state->mode == NORMAL_MODE) ? "NORMAL" : "INSERT";
  mvprintw(LINES - 1, 0, "%s %d:%d", mode_str, state->row, state->col);

  int screen_row = state->row - state->scroll_offset_row;
  int screen_col = state->col - state->scroll_offset_col;
  if (screen_row >= 0 && screen_row < LINES - 1 && screen_col >= 0 &&
      screen_col < COLS) {
    move(screen_row, screen_col);
  }

  refresh();
}

void adjust_scroll(EditorState* state) {
  if (state->row < state->scroll_offset_row) {
    state->scroll_offset_row = state->row;
  } else if (state->row >= state->scroll_offset_row + (LINES - 1)) {
    state->scroll_offset_row = state->row - (LINES - 2);
  }

  if (state->col < state->scroll_offset_col) {
    state->scroll_offset_col = state->col;
  } else if (state->col >= state->scroll_offset_col + COLS) {
    state->scroll_offset_col = state->col - (COLS - 1);
  }
}
