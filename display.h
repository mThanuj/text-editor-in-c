#ifndef DISPLAY_H
#define DISPLAY_H

#include <ncurses.h>

#include "editor_state.h"

void init_display();
void close_display();
void render_screen(const EditorState* state);
void adjust_scroll(EditorState* state);

#endif
