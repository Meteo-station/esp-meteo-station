#pragma once

#include "../hal/sensors.h"
#include "../hal/encoder.h"
#include <stdint.h>

// Экраны приложения
enum class Screen : uint8_t {
    TEMPERATURE,
    HUMIDITY,
    PRESSURE,
    AUTO_BACKLIGHT,
    _COUNT
};

// Состояние приложения
struct AppState {
    Screen currentScreen;
    Screen lastScreen;

    bool backlightOn;
    bool isAutoBacklightOn;
    SensorData sensors;
};

namespace Core {

void init(AppState& state);

void run(AppState& state);

void tick(AppState &appState, uint32_t now);

void reportData(AppState& appState, uint32_t now);

void renderUI(AppState& appState, uint32_t now);

// Обработка события энкодера
void handleEvent(AppState& state, EncoderEvent event, uint8_t level, uint32_t now);

// Обновление данных сенсоров
void updateSensorsData(AppState& state, uint32_t now);

// Переключение экрана
void nextScreen(AppState& state);
void prevScreen(AppState& state);

} // namespace Core


