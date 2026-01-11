#include "display.h"
#include "../config.h"
#include <LiquidCrystal_I2C.h>

namespace {
    LiquidCrystal_I2C lcd(I2C_ADDR_LCD);
}

namespace HAL {
namespace Display {

void init() {
    lcd.begin(LCD_COLS, LCD_ROWS);
    lcd.noBacklight();
}

void setBacklight(bool on) {
    if (on)
        lcd.backlight();
    else
        lcd.noBacklight();
}

void clear() {
    lcd.clear();
}

void setCursor(uint8_t col, uint8_t row) {
    lcd.setCursor(col, row);
}

void print(const char* str) {
    lcd.print(str);
}

void print(float value, uint8_t decimals) {
    lcd.print(value, decimals);
}

void print(int value) {
    lcd.print(value);
}

} // namespace Display
} // namespace HAL


