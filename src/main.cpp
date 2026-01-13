#include <Arduino.h>
#include "app.h"

MeteoSensors sensors;
EncoderClass encoder;
Display display;
App app(sensors, encoder, display);

void setup() {
    Serial.begin(115200);
    app.begin();
}

void loop() {
    app.tick();
}
