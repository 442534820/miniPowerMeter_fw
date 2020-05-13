/*
    ChibiOS - Copyright (C) 2006..2018 Giovanni Di Sirio

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

#include "ch.h"
#include "hal.h"
#include "usbd/usbcfg.h"
#include "chprintf.h"
#include "driver/ui12864.h"
#include "driver/device_port.h"
#include "driver/ina226.h"
#include "driver/button.h"
#include "driver/button_utils.h"
#include "ui.h"
#include <stdio.h>

uint32_t connect_count;
volatile uint16_t bus_vot;
volatile int16_t shunt_vot;
volatile int16_t bus_cur;
volatile uint32_t ina_count;
volatile int32_t cap_sum;

#define INA_MEASURE_PERIOD  200  //200ms
static THD_WORKING_AREA(waThread_INA, 256);
static THD_FUNCTION(Thread_INA, arg)
{
	systime_t measure_time;

	(void)arg;
	chRegSetThreadName("INA");
	ina226_config(0x4527);
	ina226_set_calibration_by_RI(500, 0.05);
	measure_time = chVTGetSystemTimeX();
	while (true) {
		if (chVTGetSystemTimeX() - measure_time >= INA_MEASURE_PERIOD) {
			measure_time += INA_MEASURE_PERIOD;

			ina226_read_bus_voltage((uint16_t*)&bus_vot);
			ina226_read_current((uint16_t*)&bus_cur);
			ina226_read_shunt_voltage((uint16_t*)&shunt_vot);
			cap_sum += bus_cur * INA_MEASURE_PERIOD;

			ina_count++;
		}
	}
}


static THD_WORKING_AREA(waThread_UI, 1024);
static THD_FUNCTION(Thread_UI, arg)
{
	(void)arg;
	chRegSetThreadName("UI");
	ui_init();
	ui_entry();
	/* Never reach here */
	while (1);
}

/*
 * Application entry point.
 */
int main(void) {

	/*
	 * System initializations.
	 * - HAL initialization, this also initializes the configured device drivers
	 *   and performs the board-specific initializations.
	 * - Kernel initialization, the main() function becomes a thread and the
	 *   RTOS is active.
	 */
	halInit();
	chSysInit();

	sduObjectInit(&SDU1);
	sduStart(&SDU1, &serusbcfg);
	usbDisconnectBus(serusbcfg.usbp);
	chThdSleepMilliseconds(500);
	usbStart(serusbcfg.usbp, &usbcfg);
	usbConnectBus(serusbcfg.usbp);

	/* SERIAL_DEFAULT_BITRATE is setting to 115200 */
	sdStart(&SD2, NULL);
	chprintf((BaseSequentialStream*)&SD2, "miniPowerMeter\r\n");

	dev_init();

	chThdCreateStatic(waThread_UI, sizeof(waThread_UI), NORMALPRIO, Thread_UI, NULL);
	chThdCreateStatic(waThread_INA, sizeof(waThread_INA), NORMALPRIO, Thread_INA, NULL);

	while (true) {
		if(SDU1.config->usbp->state == USB_ACTIVE) {
			chprintf((BaseSequentialStream*)&SDU1, "miniPowerMeter Connected!\n");
			while (true) {
				if(SDU1.config->usbp->state != USB_ACTIVE) {
					break;
				}
				chThdSleepMilliseconds(1000);
				chprintf((BaseSequentialStream*)&SDU1, "%d\r\n", connect_count);
			}
		}
		chThdSleepMilliseconds(500);
	}
}
