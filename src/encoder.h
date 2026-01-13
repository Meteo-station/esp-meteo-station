#pragma once
#include <EncButton.h>

enum class EncoderEvent {
    NONE,
    LEFT,
    RIGHT,
    CLICK,
};

class EncoderClass {
public:
    EncoderClass() : _enc(3, 4, 2) {
    }

    EncoderEvent readState() {
        _enc.tick();

        if (_enc.right()) return EncoderEvent::RIGHT;
        if (_enc.left()) return EncoderEvent::LEFT;
        if (_enc.press()) return EncoderEvent::CLICK;

        return EncoderEvent::NONE;
    }

private:
    EncButton _enc; // без аргументов здесь
};
