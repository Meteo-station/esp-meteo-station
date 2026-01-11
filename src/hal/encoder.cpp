#include "encoder.h"
#include "../config.h"
#include <EncButton.h>

EncButton enc(3, 4, 2);

namespace HAL {
    namespace Encoder {
        void init() {
        }

        EncoderEvent poll() {
            enc.tick();

            if (enc.right()) return EncoderEvent::RIGHT;
            if (enc.left()) return EncoderEvent::LEFT;
            if (enc.pressFor(2000)) return EncoderEvent::CLICK_AND_HOLD;
            if (enc.press()) return EncoderEvent::CLICK;

            return EncoderEvent::NONE;
        }

    } // namespace Encoder
} // namespace HAL

