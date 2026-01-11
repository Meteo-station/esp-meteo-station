#pragma once

#include <stdint.h>

// События энкодера
enum class EncoderEvent : uint8_t {
    NONE,
    LEFT,
    RIGHT,
    CLICK,
    CLICK_AND_HOLD,
};

namespace HAL {
namespace Encoder {

void init();

// Вызывать каждый loop, возвращает событие
EncoderEvent poll();

} // namespace Encoder
} // namespace HAL


