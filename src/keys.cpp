#include "keys.hpp"
#include <unordered_map>

#include <iostream>

std::unordered_map<uint8_t, bool> keymap;

void update_key(uint8_t scan_code, bool isDown) {
        std::cout << (int)scan_code << ", " << isDown << std::endl;
        keymap[scan_code] = isDown;
}
