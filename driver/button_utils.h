#ifndef __BUTTON_UTILS_H__
#define __BUTTON_UTILS_H__


struct btn_utils_event {
    unsigned char short_press : 1;
    unsigned char long_press : 1;
    unsigned char long_press_ex : 1;
    unsigned char double_press : 1;
};

struct btn_utils_flags {
    unsigned char pressed : 1;
    unsigned char long_triged : 1;
};

struct btn_utils_info {
    union {
        struct btn_utils_event mask;
        unsigned char mask_raw;
    };
    union {
        struct btn_utils_event event;
        unsigned char event_raw;
    };
    union {
        struct btn_utils_flags flags;
        unsigned char flags_raw;
    };
    unsigned int count;
};

//The button process interval is 20 ms in normal
#define BTN_UTILS_DOUBLE_PRESS_INTERVAL   10 //200ms
#define BTN_UTILS_LONG_PRESS_TIME         50 //1s
#define BTN_UTILS_LONG_PRESS_TRIG_TIME    80 //1.6s
#define BTN_UTILS_LONG_PRESS_TRIG_PERIOD  25 //0.5s

#if BTN_UTILS_LONG_PRESS_TRIG_TIME <= BTN_UTILS_LONG_PRESS_TIME
    #error "'BTN_UTILS_LONG_PRESS_TIME' must bigger than 'BTN_UTILS_LONG_PRESS_TIME"
#endif


void btn_utils_init(struct btn_utils_info *pbtn);
void btn_utils_process(struct btn_utils_info *pbtn, unsigned char btn_base_event);

#endif //__BUTTON_UTILS_H__

