#include <Arduino.h>

#include "display.h"
#include "../config.h"

namespace HAL {
namespace PhotoResistor {

void init() {}

uint8_t poll() {

    int photoResistorVoltage = analogRead(PIN_PHOTO_RESISTOR);

    return map(photoResistorVoltage, 0, 1023, 10, 1);
}

} // namespace PhotoResistor
} // namespace HAL


