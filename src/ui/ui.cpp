#include "ui.h"

#include <HardwareSerial.h>
#include <string.h>

#include "../hal/display.h"

namespace {

const char* getScreenTitle(Screen screen) {
    switch (screen) {
        case Screen::TEMPERATURE:    return "Temperature";
        case Screen::HUMIDITY:       return "Humidity";
        case Screen::PRESSURE:       return "Pressure";
        case Screen::AUTO_BACKLIGHT: return "Auto Backlight";
        default:                     return "Unknown";
    }

}

char bufferLine1[17] = "";
char bufferLine2[17] = "";

void renderHeader(Screen screen) {

    const char *line1 = getScreenTitle(screen);

    if (strcmp(line1, bufferLine1) != 0) {

        Serial.println("Update line 1");

        strcpy(bufferLine1, line1);

        HAL::Display::setCursor(0, 0);
        // Очищаем строку пробелами
        HAL::Display::print("                ");
        HAL::Display::setCursor(0, 0);
        HAL::Display::print(bufferLine1);

    }

}

void renderValue(AppState& state) {

    char line2[17];

    switch (state.currentScreen) {

        case Screen::TEMPERATURE:

            char* p = line2;

            // dtostrf возвращает указатель на буфер, идём до '\0'
            dtostrf(state.sensors.temperature, 0, 1, p);
            while (*p) p++;  // находим конец

            *p++ = ' ';
            *p++ = 'C';
            *p = '\0';
            break;

        case Screen::HUMIDITY:
            snprintf(line2, 17, "%.0f %%", state.sensors.temperature);
            break;

        case Screen::PRESSURE:
            snprintf(line2, 17, "%.0f mmHg", state.sensors.temperature);
            break;

        case Screen::AUTO_BACKLIGHT:
            snprintf(line2, 17, "%s", state.isAutoBacklightOn ? "On" : "Off");
            break;

        default:
            break;
    }

    if (strcmp(line2, bufferLine2) != 0) {
        strcpy(bufferLine2, line2);

        Serial.print(line2);
        Serial.println(bufferLine2);
        Serial.println("Update line 2");

        HAL::Display::setCursor(0, 1);
        // Очищаем строку пробелами
        HAL::Display::print("                ");
        HAL::Display::setCursor(0, 1);
        HAL::Display::print(bufferLine2);
    }

}

bool lastBacklightState = true;

} // namespace

namespace UI {

void init() {
    HAL::Display::init();
    HAL::Display::clear();
}

void render(AppState& state) {
    // Обновляем подсветку если изменилась
    if (state.backlightOn != lastBacklightState) {
        lastBacklightState = state.backlightOn;
        applyBacklight(state.backlightOn);
    }

    renderHeader(state.currentScreen);
    renderValue(state);
}

void applyBacklight(bool on) {
    HAL::Display::setBacklight(on);
}

} // namespace UI


