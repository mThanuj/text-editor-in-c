#include <ctype.h>
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINES 100
#define MAX_COLS 1000

char* buffer[MAX_LINES];
int total_lines = 1;

int row = 0, col = 0;
int mode = 0;
int scroll_offset_row = 0;
int scroll_offset_col = 0;

void initialize(void);
void render_screen(void);
void print_statusbar(void);
void handle_input(int ch);
void handle_normal_mode_input(int ch);
void handle_insert_mode_input(int ch);
int find_col(int row);
void get_text_range(int row, int start_col, int end_col, char* buffer);
void adjust_scroll(void);
void find_next_word(int* row, int* col);

int main(void) {
  int ch;
  bool running = true;

  initialize();

  while (running) {
    ch = getch();

    if (ch == 'q' && mode == 0) {
      running = false;
      break;
    }

    handle_input(ch);
    render_screen();
    refresh();
  }

  endwin();

  for (int i = 0; i < MAX_LINES; i++) {
    free(buffer[i]);
  }
  return 0;
}

void initialize(void) {
  initscr();
  ESCDELAY = 25;
  raw();
  keypad(stdscr, TRUE);
  noecho();
  scrollok(stdscr, TRUE);

  for (int i = 0; i < MAX_LINES; i++) {
    buffer[i] = (char*)calloc(MAX_COLS, sizeof(char));
  }

  render_screen();
}

void render_screen(void) {
  clear();
  int screen_lines = LINES - 1;

  for (int i = 0; i < screen_lines; i++) {
    int buffer_row = scroll_offset_row + i;
    if (buffer_row < total_lines) {
      mvaddnstr(i, 0, buffer[buffer_row] + scroll_offset_col, COLS);
    }
  }

  print_statusbar();
}

void print_statusbar(void) {
  char* mode_string = (mode == 0) ? "NORMAL" : "INSERT";
  int max_col = strlen(buffer[row]);
  if (col > max_col) col = max_col;

  mvprintw(LINES - 1, 0, "%s %d:%d", mode_string, row, col);

  int screen_row = row - scroll_offset_row;
  int screen_col = col - scroll_offset_col;

  if (screen_row >= 0 && screen_row < LINES - 1 && screen_col >= 0 &&
      screen_col < COLS) {
    move(screen_row, screen_col);
  }
}

void handle_input(int ch) {
  switch (mode) {
    case 0:
      handle_normal_mode_input(ch);
      break;
    case 1:
      handle_insert_mode_input(ch);
      break;
  }
}

void handle_normal_mode_input(int ch) {
  switch (ch) {
    case 'i':
      mode = 1;
      break;
    case 'w': {
      fprintf(stderr, "from: %d:%d\n", row, col);
      find_next_word(&row, &col);
      fprintf(stderr, "to: %d:%d\n", row, col);
      break;
    }
    case 'h':
      if (col > 0) col--;
      break;
    case 'l': {
      int len = strlen(buffer[row]);
      if (col < len) col++;
      break;
    }
    case 'j': {
      if (row < total_lines - 1) {
        row++;
        int len = strlen(buffer[row]);
        if (col > len) col = len;
      }
      break;
    }
    case 'k': {
      if (row > 0) {
        row--;
        int len = strlen(buffer[row]);
        if (col > len) col = len;
      }
      break;
    }
  }
  adjust_scroll();
}

void handle_insert_mode_input(int ch) {
  switch (ch) {
    case 27:
      mode = 0;
      break;
    case KEY_BACKSPACE: {
      int current_len = strlen(buffer[row]);
      if (col > 0) {
        memmove(&buffer[row][col - 1], &buffer[row][col],
                current_len - col + 1);
        col--;
      } else if (row > 0) {
        int prev_len = strlen(buffer[row - 1]);
        if (prev_len + strlen(buffer[row]) < MAX_COLS) {
          strcat(buffer[row - 1], buffer[row]);
          for (int i = row; i < total_lines - 1; i++) {
            strcpy(buffer[i], buffer[i + 1]);
          }
          total_lines--;
          row--;
          col = prev_len;
        }
      }
      break;
    }
    case '\n': {
      if (total_lines < MAX_LINES) {
        for (int i = total_lines; i > row + 1; i--) {
          strcpy(buffer[i], buffer[i - 1]);
        }
        strcpy(buffer[row + 1], &buffer[row][col]);
        buffer[row][col] = '\0';
        row++;
        col = 0;
        total_lines++;
      }
      break;
    }
    default: {
      int current_len = strlen(buffer[row]);
      if (col >= MAX_COLS - 1) break;

      if (col > current_len) {
        int pad = col - current_len;
        if (current_len + pad >= MAX_COLS - 1) pad = MAX_COLS - 1 - current_len;
        if (pad > 0) {
          memset(buffer[row] + current_len, ' ', pad);
          buffer[row][current_len + pad] = '\0';
        }
      }

      if (strlen(buffer[row]) < MAX_COLS - 1) {
        memmove(&buffer[row][col + 1], &buffer[row][col],
                strlen(buffer[row]) - col + 1);
        buffer[row][col] = ch;
        col++;
      }
      break;
    }
  }
  adjust_scroll();
}

int find_col(int row) {
  int last_col = 0;
  for (int c = 0; c < COLS; c++) {
    chtype ch = mvwinch(stdscr, row, c);
    if ((ch & A_CHARTEXT) != ' ') {
      last_col = c + 1;
    }
  }
  return last_col;
}

void get_text_range(int row, int start_col, int end_col, char* buffer) {
  int len = 0;
  for (int col = start_col; col <= end_col; col++) {
    chtype ch = mvwinch(stdscr, row, col);
    buffer[len++] = ch & A_CHARTEXT;
  }
  buffer[len] = '\0';
}

void adjust_scroll() {
  if (row < scroll_offset_row) {
    scroll_offset_row = row;
  } else if (row >= scroll_offset_row + (LINES - 1)) {
    scroll_offset_row = row - (LINES - 2);
  }

  if (col < scroll_offset_col) {
    scroll_offset_col = col;
  } else if (col >= scroll_offset_col + COLS) {
    scroll_offset_col = col - (COLS - 1);
  }
}

void find_next_word(int* row, int* col) {
  int cur_row = *row;
  int cur_col = *col;

  int len = strlen(buffer[cur_row]);
  while (cur_col < len) {
    chtype ch = mvwinch(stdscr, cur_row, cur_col);
    if ((ch & A_CHARTEXT) == ' ') {
      break;
    }
    cur_col++;
  }
  if (cur_col == len) {
    cur_row += 1;
    cur_col = 0;
  }

  while (cur_col < len) {
    chtype ch = mvwinch(stdscr, cur_row, cur_col);
    if (!((ch & A_CHARTEXT) == ' ')) {
      break;
    }
    cur_col++;
  }

  *row = cur_row == total_lines ? cur_row - 1 : cur_row;
  *col = cur_col == len ? cur_col - 1 : cur_col;
}
