#ifndef __BUTTON_H__
#define __BUTTON_H__

#include <stdint.h>


#define BUTTON_STATE_IDLE    0
#define BUTTON_STATE_FALL    1
#define BUTTON_STATE_DOWN    2
#define BUTTON_STATE_RELEASE 3

#define BUTTON_COUNT         4

extern uint8_t button_state[BUTTON_COUNT];

void button_init(void);
void button_scan(void);


#endif
