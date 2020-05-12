#include "button.h"
#include "button_utils.h"
#include <stddef.h>

void btn_utils_init(struct btn_utils_info *pbtn)
{
    if (pbtn == NULL) {
        return;
    }

    pbtn->mask_raw = 0;
    pbtn->event_raw = 0;
    pbtn->flags_raw = 0;
    pbtn->count = 0;
}

void btn_utils_process(struct btn_utils_info *pbtn, unsigned char btn_base_event)
{
    if (pbtn == NULL) {
        return;
    }

    switch (btn_base_event) {
    case BUTTON_STATE_IDLE:
        if (pbtn->flags.pressed) {
            pbtn->count++;
            if (pbtn->count > BTN_UTILS_DOUBLE_PRESS_INTERVAL * 2) {
                pbtn->flags.pressed = 0;
            }
        }
        break;
    case BUTTON_STATE_FALL:
        break;
    case BUTTON_STATE_DOWN:
        pbtn->count++;
        if (pbtn->flags.long_triged) {
            if (pbtn->count >= BTN_UTILS_LONG_PRESS_TRIG_PERIOD) {
                pbtn->count = 0;
                pbtn->event.long_press_ex = 1; //LONG PRESS EX
                return;
            }
        } else {
            if (pbtn->count >= BTN_UTILS_LONG_PRESS_TRIG_TIME) {
                pbtn->count = 0;
                pbtn->flags.long_triged = 1;
            }
        }
        break;
    case BUTTON_STATE_RELEASE:
        if (pbtn->flags.long_triged) {
            pbtn->flags.long_triged = 0;
//            pbtn->flags.pressed = 0; //TODO
            //No events generated
        } else {
            if (pbtn->flags.pressed == 0) {
                if (pbtn->count >= BTN_UTILS_LONG_PRESS_TIME) {
                    pbtn->count = 0;
                    pbtn->event.long_press = 1; //LONG PRESS
                    return;
                } else {
                    pbtn->flags.pressed = 1;
                    pbtn->count = 0;
                    pbtn->event.short_press = 1; //SHORT PRESS
                    return;
                }
            } else {
                if (pbtn->count <= BTN_UTILS_DOUBLE_PRESS_INTERVAL) {
                    pbtn->flags.pressed = 0;
                    pbtn->count = 0;
                    pbtn->event.double_press = 1; //DOUBLE PRESS
                } else {
                    pbtn->flags.pressed = 1;
                    pbtn->count = 0;
                    pbtn->event.short_press = 1; //SHORT PRESS
                    return;
                }
            }
        }
        break;
    }
}

