#pragma once

#include <cstdint>

#include <unordered_map>

/// @brief A hashmap with uint8_t referencing SDL scancodes
/// To use just use keymap[SDL_scancode_XX]
extern std::unordered_map<uint8_t, bool> keymap;
// NOT IMPLEMENTED
extern std::unordered_map<uint8_t, bool> mouse_button;
/// @brief the current location of the mouse on screen.
extern float mouse_x, mouse_y;

extern void update_key(uint8_t scan_code, bool isDown);
