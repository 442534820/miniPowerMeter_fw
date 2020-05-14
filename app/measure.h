#ifndef __MEASURE_H__
#define __MEASURE_H__

#include <stdint.h>

extern volatile uint16_t bus_vot;
extern volatile int16_t shunt_vot;
extern volatile int16_t bus_cur;
extern volatile uint32_t ina_count;
extern volatile int32_t cap_sum;

void measure_init(void);
void measure_set_period(uint16_t period);
void measure_start(void);
void measure_stop(void);
void measure_clear(void);

#endif
