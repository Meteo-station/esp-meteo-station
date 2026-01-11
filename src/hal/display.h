#pragma once

#include <stdint.h>

namespace HAL {
namespace Display {

void init();

void setBacklight(bool on);
void clear();
void setCursor(uint8_t col, uint8_t row);
void print(const char* str);
void print(float value, uint8_t decimals = 1);
void print(int value);

} // namespace Display
} // namespace HAL


