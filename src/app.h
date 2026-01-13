#pragma once

#include <Arduino.h>
#include "config.h"
#include "encoder.h"
#include "meteoSensors.h"
#include "display.h"

class App {
public:
    // Конструктор принимает все объекты по ссылке
    App(MeteoSensors &sensors,
        EncoderClass &encoder,
        Display &display)
        : _meteoSensors(sensors),
          _encoder(encoder),
          _display(display) {
    }

    void begin() {
        _meteoSensors.begin();
        _display.begin();
    }

    void tick() {
        uint32_t now = millis();

        // Получаем состояние железа
        EncoderEvent encoderState = _encoder.readState();

        // Читаем метео сенсоры
        _meteoSensors.tick();
        _meteoSensors.readMeteoData(now, _sensorData);

        // Подготавливаем состояние дисплея
        _prepareDisplayState(encoderState, now);

        // Рендерим дисплей
        _display.render(_displayState, _sensorData);
    }

private:
    MeteoSensorData _sensorData;
    DisplayState _displayState;

    MeteoSensors &_meteoSensors;
    EncoderClass &_encoder;
    Display &_display;

    void _prepareDisplayState(EncoderEvent event, uint32_t now) {
        switch (event) {
            case EncoderEvent::LEFT:
                _displayState.prevScreen();
                break;

            case EncoderEvent::RIGHT:
                _displayState.nextScreen();
                break;

            case EncoderEvent::CLICK:
                _displayState.toggleBacklight();
                break;

            default:
                break;
        }
    }
};
