#include "sensors.h"
#include "../config.h"
#include <GyverBME280.h>
#include <GyverHTU21D.h>

namespace {
    GyverBME280 bme;
    GyverHTU21D htu;
    uint32_t lastUpdate = 0;
    constexpr uint32_t MIN_INTERVAL = 200;  // аппаратное ограничение
}

namespace HAL {
namespace Sensors {

void init() {
    htu.begin();
    bme.begin(I2C_ADDR_BME280);
}

void tick(uint32_t now) {
    // Асинхронное чтение HTU21D
    htu.readTick(MIN_INTERVAL);
}

bool update(uint32_t now, SensorData& out) {
    if (now - lastUpdate < MIN_INTERVAL) {
        return false;
    }
    lastUpdate = now;

    float bmeTemp = bme.readTemperature();
    float htuTemp = htu.getTemperature();

    out.temperature = (bmeTemp + htuTemp) / 2.0f;
    out.humidity    = htu.getHumidity();
    out.pressure    = bme.readPressure() / 133.322f;

    return true;
}

} // namespace Sensors
} // namespace HAL


