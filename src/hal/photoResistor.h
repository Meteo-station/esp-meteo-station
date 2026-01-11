#pragma once

#include <stdint.h>

namespace HAL {
namespace PhotoResistor {

void init();

uint8_t poll();

} // namespace Display
} // namespace HAL

