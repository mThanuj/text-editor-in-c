#ifndef NAVIGATION_H
#define NAVIGATION_H

#include "editor_state.h"

void cursor_move_left(EditorState* s);
void cursor_move_right(EditorState* s);
void cursor_move_up(EditorState* s);
void cursor_move_down(EditorState* s);
void cursor_move_word_forward(EditorState* s);
void cursor_move_word_backward(EditorState* s);

#endif
