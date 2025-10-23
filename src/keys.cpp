#include "keys.hpp"
#include <unordered_map>


void update_key(uint8_t scan_code, bool isDown) {
        keymap[scan_code] = isDown;
}
