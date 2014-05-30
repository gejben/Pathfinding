#ifndef GAME_HPP
#define GAME_HPP
#include "WinMain.hpp"

bool game_preload();
bool game_init(HWND);
void game_update();
void game_end();
void game_graphics_update();


#endif