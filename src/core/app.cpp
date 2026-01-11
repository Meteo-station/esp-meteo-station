#include "app.h"

#include <Arduino.h>


#include "config.h"
#include "../output/reporter.h"
#include "../hal/sensors.h"
#include "hal/photoResistor.h"
#include "ui/ui.h"

namespace {
    uint32_t lastSensorUpdate = 0;
    uint32_t lastReport = 0;
    uint32_t systemScreenEnterredAt = 0;
}

namespace Core {
    void init(AppState &state) {
        Output::init();
        state.currentScreen = Screen::TEMPERATURE;
        state.backlightOn = false;
        state.isAutoBacklightOn = false;
        state.sensors = {0.0f, 0.0f, 0.0f};
    }

    void run(AppState &appState) {
        const uint32_t now = millis();

        // Читаем ввод (энкодер), получаем текущее событие энкодера
        const EncoderEvent event = HAL::Encoder::poll();

        const uint8_t level = HAL::PhotoResistor::poll();

        tick(appState, now);

        // Обрабатываем событие в бизнес-логике
        handleEvent(appState, event, level, now);

        // Обновляем данные сенсоров
        updateSensorsData(appState, now);

        // Рендерим UI
        UI::render(appState);

        // Отправляем сырые данные
        reportData(appState, now);
    }

    void tick(AppState &appState, uint32_t now) {

        if (appState.currentScreen == Screen::AUTO_BACKLIGHT) {
            if (now - systemScreenEnterredAt >= 1000) {
                Serial.print(now);
                Serial.print(" ");
                Serial.println(systemScreenEnterredAt);
                appState.currentScreen = appState.lastScreen;
            }
        }
    }

    void reportData(AppState &appState, uint32_t now) {
        if (now - lastReport >= REPORT_INTERVAL_MS) {
            lastReport = now;
            Output::report(appState);
        }
    }


    void handleEvent(AppState &state, EncoderEvent event, uint8_t level, uint32_t now) {

        switch (event) {
            case EncoderEvent::LEFT:
                prevScreen(state);
                break;
            case EncoderEvent::RIGHT:
                nextScreen(state);
                break;
            case EncoderEvent::CLICK_AND_HOLD:
                if (state.currentScreen == Screen::AUTO_BACKLIGHT) {
                    break;
                }
                state.isAutoBacklightOn = !state.isAutoBacklightOn;
                state.lastScreen = state.currentScreen;

                state.currentScreen = Screen::AUTO_BACKLIGHT;
                systemScreenEnterredAt = now;

                break;
            case EncoderEvent::CLICK:
                if (!state.isAutoBacklightOn) {
                    state.backlightOn = !state.backlightOn;
                }
                break;
            default:
                break;
        }

        if (state.isAutoBacklightOn) {
            if (level < 5) {
                state.backlightOn = true;
            } else {
                state.backlightOn = false;
            }
        }
    }

    void updateSensorsData(AppState &state, uint32_t now) {
        if (now - lastSensorUpdate >= SENSOR_UPDATE_MS) {
            lastSensorUpdate = now;

            HAL::Sensors::tick(now);
            HAL::Sensors::update(now, state.sensors);
        }
    }

    void nextScreen(AppState &state) {
        uint8_t s = static_cast<uint8_t>(state.currentScreen);
        s = (s + 1) % static_cast<uint8_t>(Screen::_COUNT);
        state.currentScreen = static_cast<Screen>(s);
    }

    void prevScreen(AppState &state) {
        uint8_t s = static_cast<uint8_t>(state.currentScreen);
        s = (s + static_cast<uint8_t>(Screen::_COUNT) - 1) % static_cast<uint8_t>(Screen::_COUNT);
        state.currentScreen = static_cast<Screen>(s);
    }
} // namespace Core

