#pragma once

#include <cstdint>

#include <unordered_map>

extern std::unordered_map<uint8_t, bool> keymap;

extern void update_key(uint8_t scan_code, bool isDown);
