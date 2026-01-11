#include <HardwareSerial.h>
#include <stdint.h>

namespace HAL {
    namespace SerialPort {
        void init(uint32_t baud) {
            Serial.begin(baud);
        }

        void print(const char* str) {
            Serial.print(str);
        }

        void print(float value, uint8_t decimals = 2) {
            Serial.print(value, decimals);
        }

        void println() {
            Serial.println();
        }

        void println(const char* str) {
            Serial.println(str);
        }

        void println(float value, uint8_t decimals = 2) {
            Serial.println(value, decimals);
        }
    }
}
