#include "measure.h"
#include "ch.h"
#include "hal.h"
#include "driver/ina226.h"


volatile uint16_t bus_vot;
volatile int16_t shunt_vot;
volatile int16_t bus_cur;
volatile uint32_t ina_count;
volatile int64_t cap_sum;
volatile systime_t measure_timestamp;

volatile uint16_t log_data[MEASURE_LOG_DATA_LEN];
volatile uint16_t log_data_read_ptr;
volatile uint16_t log_data_write_ptr;
volatile uint8_t log_data_switch;

static uint16_t trig_period = INA_MEASURE_PERIOD;
static semaphore_t sem1;
static void measure_trig(GPTDriver *param);
static GPTConfig gpt3cfg = {
	.frequency = 1000,
	.callback = measure_trig,
	.cr2 = 0,
	.dier = 0,
};

static void measure_trig(GPTDriver *param)
{
	(void)param;

	chSemSignalI(&sem1);
	palClearPad(GPIOA, GPIOA_LED2);
}

static THD_WORKING_AREA(waThread_INA, 256);
static THD_FUNCTION(Thread_INA, arg)
{
	(void)arg;

	chRegSetThreadName("INA");
	ina226_config(0x4527);
	ina226_set_calibration_by_RI(500, 0.05);
	chSemObjectInit(&sem1, 0);
	gptStart(&GPTD3, &gpt3cfg);
	while (true) {
		chSemWait(&sem1);
		ina226_read_bus_voltage((uint16_t*)&bus_vot);
//		ina226_read_current((uint16_t*)&bus_cur);
		ina226_read_shunt_voltage((uint16_t*)&shunt_vot);
		/* use shunt_vot as current to make result more accurate */
		bus_cur = shunt_vot;
		cap_sum += bus_cur * trig_period;

		ina_count++;
		palSetPad(GPIOA, GPIOA_LED2);

		/* log data */
		if (log_data_switch) {
			log_data[log_data_write_ptr] = bus_cur;
			if (log_data_write_ptr >= MEASURE_LOG_DATA_LEN - 1)
				log_data_write_ptr = 0;
			else
				log_data_write_ptr++;
		}
	}
}

void measure_init(void)
{
	chThdCreateStatic(waThread_INA, sizeof(waThread_INA), NORMALPRIO, Thread_INA, NULL);
}

void measure_set_period(uint16_t period)
{
	trig_period = period;
}

uint16_t measure_get_period(void)
{
	return trig_period;
}

uint32_t measure_get_time_seconds(void)
{
	return (chVTGetSystemTimeX() - measure_timestamp) / 1000;
}

void measure_start(void)
{
	measure_timestamp = chVTGetSystemTimeX();
	gptStartContinuous(&GPTD3, trig_period);
}

void measure_stop(void)
{
	gptStopTimer(&GPTD3);
}

void measure_clear(void)
{
	cap_sum = 0;
	measure_timestamp = chVTGetSystemTimeX();
}

