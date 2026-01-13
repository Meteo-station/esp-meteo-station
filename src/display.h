#pragma once

#include <LiquidCrystal_I2C.h>

enum class Screen : uint8_t {
    TEMPERATURE,
    HUMIDITY,
    PRESSURE,
    _COUNT
};

struct DisplayState {
    bool isBacklightOn = false;
    Screen lastScreen = Screen::TEMPERATURE;
    Screen currentScreen = Screen::TEMPERATURE;

    void nextScreen() {
        uint8_t s = static_cast<uint8_t>(currentScreen);
        currentScreen = static_cast<Screen>((s + 1) % uint8_t(Screen::_COUNT));
    }

    void prevScreen() {
        uint8_t s = static_cast<uint8_t>(currentScreen);
        currentScreen = static_cast<Screen>((s + uint8_t(Screen::_COUNT) - 1) % uint8_t(Screen::_COUNT));
    }

    void toggleBacklight() {
        isBacklightOn = !isBacklightOn;
    }
};

class Display {
public:
    Display() { _lcd = LiquidCrystal_I2C(PCF8574_ADDR_A21_A11_A01); }

    void begin() {
        _lcd.begin(LCD_COLS, LCD_ROWS);
        _lcd.noBacklight();
    }

    void render(DisplayState &state, MeteoSensorData &sensorData) {

        // Обновляем подсветку если изменилась
        if (state.isBacklightOn != _lastBacklightState) {
            _lastBacklightState = state.isBacklightOn;

            state.isBacklightOn ? _lcd.backlight() : _lcd.noBacklight();
        }

        _renderHeader(state);
        _renderValue(state, sensorData);
    }

private:
    LiquidCrystal_I2C _lcd;

    bool _lastBacklightState = false;
    char bufferLine1[17] = "";
    char bufferLine2[17] = "";

    void _print(uint8_t line, const char *text) {
        _lcd.setCursor(0, line);
        _lcd.print("                ");
        _lcd.setCursor(0, line);
        _lcd.print(text);
    }

    void _renderHeader(DisplayState &state) {
        const char *line = _getScreenTitle(state.currentScreen);
        if (strcmp(line, bufferLine1) != 0) {
            strcpy(bufferLine1, line);

            Serial.print("Print header: ");
            Serial.println(bufferLine1);
            _print(0, bufferLine1);
        }
    }


    void _renderValue(DisplayState &state, MeteoSensorData &sensorData) {
        char line[17];
        _getScreenValue(line, sizeof(line), state, sensorData);

        if (strcmp(line, bufferLine2) != 0) {
            strcpy(bufferLine2, line);

            Serial.print("Print value: ");
            Serial.println(bufferLine2);

            _print(1, bufferLine2);
        }
    }

    void _getScreenValue(
        char *out,
        size_t outSize,
        const DisplayState &state,
        const MeteoSensorData &sensorData
    ) {
        switch (state.currentScreen) {
            case Screen::TEMPERATURE: {
                int t10 = (int) (sensorData.temperature_1 * 10);
                snprintf(out, outSize, "%d.%d C", t10 / 10, abs(t10 % 10));
                break;
            }
            case Screen::HUMIDITY:
                snprintf(out, outSize, "%d %%", (int) sensorData.humidity);
                break;
            case Screen::PRESSURE:
                snprintf(out, outSize, "%d mmHg", (int) sensorData.pressure);
                break;
            default:
                out[0] = '\0';
                break;
        }
    }

    const char *_getScreenTitle(Screen screen) {
        switch (screen) {
            case Screen::TEMPERATURE: return "Temperature";
            case Screen::HUMIDITY: return "Humidity";
            case Screen::PRESSURE: return "Pressure";
            default: return "Unknown";
        }
    }
};
