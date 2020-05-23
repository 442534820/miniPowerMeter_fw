#ifndef __MEASURE_H__
#define __MEASURE_H__

#include <stdint.h>

#define INA_MEASURE_PERIOD  100  //100ms
extern volatile uint16_t bus_vot;
extern volatile int16_t shunt_vot;
extern volatile int16_t bus_cur;
extern volatile uint32_t ina_count;
extern volatile int64_t cap_sum;

#define MEASURE_LOG_DATA_LEN  256
extern volatile uint16_t log_data[MEASURE_LOG_DATA_LEN];
extern volatile uint16_t log_data_read_ptr;
extern volatile uint16_t log_data_write_ptr;
extern volatile uint8_t log_data_switch;

void measure_init(void);
void measure_set_period(uint16_t period);
uint16_t measure_get_period(void);
void measure_start(void);
void measure_stop(void);
void measure_clear(void);

#endif
