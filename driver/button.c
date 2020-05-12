#include <stdint.h>
#include "button.h"
#include "ch.h"
#include "hal.h"


#define BUTTON_DOWN          0
#define BUTTON_UP            1

typedef struct {
    uint8_t (*read_pin)(void);  // return 0=down; 1=up
}button_dev_t;

uint8_t button_1_read(void);
uint8_t button_2_read(void);
uint8_t button_3_read(void);
uint8_t button_4_read(void);

static const button_dev_t button_dev[BUTTON_COUNT] = {
    {.read_pin = button_1_read},
    {.read_pin = button_2_read},
    {.read_pin = button_3_read},
    {.read_pin = button_4_read},
};

uint8_t button_state[BUTTON_COUNT];

void button_init(void)
{
    uint8_t i;

    for (i=0; i<BUTTON_COUNT; i++)
        button_state[i] = BUTTON_STATE_IDLE;
}

void button_scan(void)
{
    uint8_t i;
    uint8_t state;

    for (i=0; i<BUTTON_COUNT; i++) {
        state = button_dev[i].read_pin();
        switch(button_state[i]) {
        case BUTTON_STATE_IDLE:
            if (state == BUTTON_DOWN)
                button_state[i] = BUTTON_STATE_FALL;
            break;
        case BUTTON_STATE_FALL:
            if (state == BUTTON_DOWN)
                button_state[i] = BUTTON_STATE_DOWN;
            else
                button_state[i] = BUTTON_STATE_IDLE;
            break;
        case BUTTON_STATE_DOWN:
            if (state == BUTTON_UP)
                button_state[i] = BUTTON_STATE_RELEASE;
            break;
        case BUTTON_STATE_RELEASE:
            button_state[i] = BUTTON_STATE_IDLE;
            break;
        default:
            break;
        }
    }
}

uint8_t button_1_read(void)
{
    if (palReadPort(GPIOB) & (1 << 0))
        return BUTTON_UP;
    else
        return BUTTON_DOWN;
}

uint8_t button_2_read(void)
{
    if (palReadPort(GPIOB) & (1 << 1))
        return BUTTON_UP;
    else
        return BUTTON_DOWN;
}

uint8_t button_3_read(void)
{
    if (palReadPort(GPIOB) & (1 << 2))
        return BUTTON_UP;
    else
        return BUTTON_DOWN;
}

uint8_t button_4_read(void)
{
    if (!(palReadPort(GPIOA) & (1 << 15)))
        return BUTTON_UP;
    else
        return BUTTON_DOWN;
}

