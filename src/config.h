#pragma once

#include <stdint.h>

// Пины энкодера
#define PIN_ENCODER_BTN    2
#define PIN_ENCODER_A      3
#define PIN_ENCODER_B      4
#define PIN_PHOTO_RESISTOR 14

// I2C адреса
#define I2C_ADDR_BME280   0x76

// LCD размеры
constexpr uint8_t LCD_COLS = 16;
constexpr uint8_t LCD_ROWS = 2;

// Serial baud
constexpr uint32_t SERIAL_BAUD = 9600;

