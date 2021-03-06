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
#include "driver/button.h"
#include "driver/button_utils.h"
#include "measure.h"
#include "ui.h"
#include <stdio.h>

uint32_t connect_count;


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

	measure_init();
	ui_init();

	while (true) {
		if(SDU1.config->usbp->state == USB_ACTIVE) {
			chprintf((BaseSequentialStream*)&SDU1, "miniPowerMeter Connected!\n");
			log_data_switch = 1;
			while (true) {
				if(SDU1.config->usbp->state != USB_ACTIVE) {
					log_data_switch = 0;
					break;
				}
				if (log_data_write_ptr != log_data_read_ptr) {
					streamPut((BaseSequentialStream*)&SDU1, 0xA5);
					streamPut((BaseSequentialStream*)&SDU1, log_data[log_data_read_ptr] & 0xFF);
					streamPut((BaseSequentialStream*)&SDU1, log_data[log_data_read_ptr] >> 8);
					if (log_data_read_ptr >= MEASURE_LOG_DATA_LEN)
						log_data_read_ptr = 0;
					else
						log_data_read_ptr++;
				} else {
					chThdSleepMilliseconds(100);
				}
			}
		}
		chThdSleepMilliseconds(500);
	}
}
