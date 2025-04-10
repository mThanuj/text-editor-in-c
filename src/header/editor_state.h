#ifndef EDITOR_STATE_H
#define EDITOR_STATE_H

#define MAX_LINES 10000
#define MAX_COLS 10000

typedef enum { NORMAL_MODE, INSERT_MODE } EditorMode;

typedef struct {
  char* buffer[MAX_LINES];
  int total_lines;
  int row, col;
  EditorMode mode;
  int scroll_offset_row;
  int scroll_offset_col;
  const char* filename;
  char* status_msg;
} EditorState;

EditorState* create_editor_state(const char* filename);
void destroy_editor_state(EditorState* state);
void set_status_message(const EditorState* state);

#endif
