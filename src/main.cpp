#include <Arduino.h>
#include "config.h"
#include "hal/sensors.h"
#include "hal/encoder.h"
#include "core/app.h"
#include "output/reporter.h"
#include "ui/ui.h"

AppState appState;

void setup() {

    Output::init();

    // Инициализируем метеодатчики
    HAL::Sensors::init();

    // Инициализируем энкодер
    HAL::Encoder::init();

    // Инициализация UI (включает инициализацию дисплея)
    UI::init();

    // Инициализация состояния приложения
    Core::init(appState);
}

void loop() {
    Core::run(appState);
}
