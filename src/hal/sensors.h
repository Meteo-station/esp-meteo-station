#pragma once

#include <stdint.h>

// Данные с датчиков
struct SensorData {
    float temperature;  // °C (среднее BME + HTU)
    float humidity;     // % (HTU21D)
    float pressure;     // Па (BME280)
};

namespace HAL {
namespace Sensors {

void init();

// Вызывать каждый loop для асинхронного чтения HTU21D
void tick(uint32_t now);

// Возвращает true если данные обновились
bool update(uint32_t now, SensorData& out);

} // namespace Sensors
} // namespace HAL


