#pragma once

#include <stdint.h>

namespace HAL {
    namespace SerialPort {

        void init(uint32_t baud);
        void print(const char* str);
        void print(float value, uint8_t decimals = 2);
        void println();
        void println(const char* str);
        void println(float value, uint8_t decimals = 2);

    } // namespace SerialPort
} // namespace HAL

