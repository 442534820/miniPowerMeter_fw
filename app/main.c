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
#include "ui.h"
#include <stdio.h>

uint32_t connect_count;
uint16_t bus_vot;
int16_t shunt_vot;
int16_t bus_cur;
char str_buf[32];
/*
 * Blue LED blinker thread, times are in milliseconds.
 */
static THD_WORKING_AREA(waThread1, 512);
static THD_FUNCTION(Thread1, arg) {

  (void)arg;
  chRegSetThreadName("blinker1");
  ina226_config(0x4527);
  ina226_set_calibration_by_RI(500, 0.05);
  while (true) {
    palClearPad(GPIOA, GPIOA_LED1);
    chThdSleepMilliseconds(10);
    palSetPad(GPIOA, GPIOA_LED1);
    chThdSleepMilliseconds(10);
    ina226_read_bus_voltage(&bus_vot);
    ina226_read_current((uint16_t*)&bus_cur);
    ina226_read_shunt_voltage(&shunt_vot);
    chsnprintf(str_buf, sizeof(str_buf), "%04X", bus_vot);
    UI12864_PutString(2, 10, str_buf);
    chsnprintf(str_buf, sizeof(str_buf), "%2.3fV", bus_vot * 0.00125f);
    UI12864_PutString(2, 50, str_buf);
    chsnprintf(str_buf, sizeof(str_buf), "%04X", (uint16_t)bus_cur);
    UI12864_PutString(3, 10, str_buf);
    chsnprintf(str_buf, sizeof(str_buf), "%4.1fmA", bus_cur * 0.05f);
    UI12864_PutString(3, 50, str_buf);
    chsnprintf(str_buf, sizeof(str_buf), "%04X", (uint16_t)shunt_vot);
    UI12864_PutString(4, 10, str_buf);
    chsnprintf(str_buf, sizeof(str_buf), "%4.2fuV", shunt_vot * 2.5f);
    UI12864_PutString(4, 50, str_buf);

//    if (button_state[0] == BUTTON_STATE_RELEASE) {
//      UI12864_PutString(4, 0, "1234");
//    }
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

static THD_WORKING_AREA(waThread_Btn, 64);
static THD_FUNCTION(Thread_Btn, arg)
{
    (void)arg;
    chRegSetThreadName("BtnScan");
    button_init();
    while (1) {
        button_scan();
        chThdSleepMilliseconds(100);
    }
}

static THD_WORKING_AREA(waThread_UI, 512);
static THD_FUNCTION(Thread_UI, arg)
{
    (void)arg;
    chRegSetThreadName("UI");
    ui_init();
    while (1) {
        ui_main();
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
  chprintf((BaseSequentialStream*)&SD2, "miniPowerMeter\r\n");

  UI12864_Init();
  UI12864_PutString(0, 0, "miniPowerMeter");
  UI12864_PutString(1, 10, "OLED test ok!");

  dev_init();

  /*
   * Creates the blinker threads.
   */
  chThdCreateStatic(waThread_Btn, sizeof(waThread_Btn), NORMALPRIO, Thread_Btn, NULL);
  //chThdCreateStatic(waThread_UI, sizeof(waThread_UI), NORMALPRIO, Thread_UI, NULL);
  chThdCreateStatic(waThread1, sizeof(waThread1), NORMALPRIO, Thread1, NULL);
  chThdCreateStatic(waThread2, sizeof(waThread2), NORMALPRIO, Thread2, NULL);

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
