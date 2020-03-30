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

uint32_t connect_count;

/*
 * Blue LED blinker thread, times are in milliseconds.
 */
static THD_WORKING_AREA(waThread1, 128);
static THD_FUNCTION(Thread1, arg) {

  (void)arg;
  chRegSetThreadName("blinker1");
  while (true) {
    palClearPad(GPIOA, GPIOA_LED1);
    chThdSleepMilliseconds(500);
    palSetPad(GPIOA, GPIOA_LED1);
    chThdSleepMilliseconds(500);
  }
}

/*
 * Green LED blinker thread, times are in milliseconds.
 */
static THD_WORKING_AREA(waThread2, 128);
static THD_FUNCTION(Thread2, arg) {

  (void)arg;
  chRegSetThreadName("blinker2");
  while (true) {
    palClearPad(GPIOA, GPIOA_LED2);
    chThdSleepMilliseconds(250);
    palSetPad(GPIOA, GPIOA_LED2);
    chThdSleepMilliseconds(250);
  }
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
  chThdSleepMilliseconds(1500);
  usbStart(serusbcfg.usbp, &usbcfg);
  usbConnectBus(serusbcfg.usbp);

  /* SERIAL_DEFAULT_BITRATE is setting to 115200 */
  sdStart(&SD2, NULL);
  chprintf(&SD2, "miniPowerMeter\r\n");

  /*
   * Creates the blinker threads.
   */
  chThdCreateStatic(waThread1, sizeof(waThread1), NORMALPRIO, Thread1, NULL);
  chThdCreateStatic(waThread2, sizeof(waThread2), NORMALPRIO, Thread2, NULL);

  while (true) {
    if(SDU1.config->usbp->state == USB_ACTIVE) {
        chprintf(&SDU1, "miniPowerMeter Connected!\n");
        while (true) {
            if(SDU1.config->usbp->state != USB_ACTIVE) {
                break;
            }
            chThdSleepMilliseconds(1000);
            chprintf(&SDU1, "%d\r\n", connect_count);
        }
    }
    chThdSleepMilliseconds(500);
  }
}
