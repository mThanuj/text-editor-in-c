#ifndef BUFFER_H
#define BUFFER_H

#include "editor_state.h"

void buffer_insert_char(EditorState* state, char ch);
void buffer_delete_char(EditorState* state);
void buffer_split_line(EditorState* state);
void buffer_merge_line(EditorState* state);

#endif
