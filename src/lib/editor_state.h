#ifndef EDITOR_STATE_H
#define EDITOR_STATE_H

#define MAX_LINES 100
#define MAX_COLS 1000

typedef enum { NORMAL_MODE, INSERT_MODE } EditorMode;

typedef struct {
  char* buffer[MAX_LINES];
  int total_lines;
  int row, col;
  EditorMode mode;
  int scroll_offset_row;
  int scroll_offset_col;
} EditorState;

EditorState* create_editor_state();
void destroy_editor_state(EditorState* state);

#endif
