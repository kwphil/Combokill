#pragma once

#include <cstdint>

#include <unordered_map>

extern std::unordered_map<uint8_t, bool> keymap;
extern std::unordered_map<uint8_t, bool> mouse_button;
extern float mouse_x, mouse_y;

extern void update_key(uint8_t scan_code, bool isDown);
