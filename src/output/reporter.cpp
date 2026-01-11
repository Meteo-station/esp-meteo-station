#include "config.h"
#include "../hal/serialPort.h"

#include "core/app.h"

struct AppState;

namespace {
}

namespace Output {
    void init() {
        HAL::SerialPort::init(SERIAL_BAUD);
    }

    void report(AppState &app) {
        HAL::SerialPort::print(app.sensors.temperature);
        HAL::SerialPort::print(",");
        HAL::SerialPort::print(app.sensors.pressure);
        HAL::SerialPort::print(",");
        HAL::SerialPort::print(app.sensors.humidity);
        HAL::SerialPort::println();
    }
}
