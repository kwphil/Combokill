#include "keys.hpp"
#include <unordered_map>

std::unordered_map<uint8_t, bool> keymap;
float mouse_x = 0;
float mouse_y = 0;

void update_key(uint8_t scan_code, bool isDown) {
        keymap[scan_code] = isDown;
}
