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
uint16_t bus_vot;
int16_t shunt_vot;
int16_t bus_cur;
char str_buf[32];
volatile uint32_t ina_count;

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
        if (chVTGetSystemTimeX() - measure_time >= 200) {
            measure_time += 200;

            ina226_read_bus_voltage(&bus_vot);
            ina226_read_current((uint16_t*)&bus_cur);
            ina226_read_shunt_voltage((uint16_t*)&shunt_vot);

            ina_count++;
        }

  }
}

struct btn_utils_info btn[4];

static THD_WORKING_AREA(waThread_UI, 1024);
static THD_FUNCTION(Thread_UI, arg)
{
    systime_t btn_time;
    uint32_t last_ina_count;

    (void)arg;
    chRegSetThreadName("UI");
    button_init();
    btn_utils_init(&btn[0]);
    btn_utils_init(&btn[1]);
    btn_utils_init(&btn[2]);
    btn_utils_init(&btn[3]);
    ui_init();
    btn_time = chVTGetSystemTimeX();
    last_ina_count = ina_count;
    while (1) {
        if (chVTGetSystemTimeX() - btn_time >= 20) {
            btn_time += 20;
            button_scan();
            btn_utils_process(&btn[0], button_state[0]);
            if (btn[0].event.short_press) {
                btn[0].event.short_press = 0;
                UI12864_PutString(6, 0, "Short ");
            }
            if (btn[0].event.long_press) {
                btn[0].event.long_press = 0;
                UI12864_PutString(6, 0, "Long  ");
            }
            if (btn[0].event.long_press_ex) {
                btn[0].event.long_press_ex = 0;
                UI12864_PutString(6, 0, "LongEx");
            }
            if (btn[0].event.double_press) {
                btn[0].event.double_press = 0;
                UI12864_PutString(6, 0, "Double");
            }
        }

        if (last_ina_count != ina_count) {
            last_ina_count = ina_count;

            palClearPad(GPIOA, GPIOA_LED1);
            chThdSleepMilliseconds(2);
            palSetPad(GPIOA, GPIOA_LED1);

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
        }

        chsnprintf(str_buf, sizeof(str_buf), "%d", btn_time);
        UI12864_PutString(5, 10, str_buf);

//        ui_main();
//        chThdSleepMilliseconds(10);
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
  chThdSleepMilliseconds(500);
  usbStart(serusbcfg.usbp, &usbcfg);
  usbConnectBus(serusbcfg.usbp);

  /* SERIAL_DEFAULT_BITRATE is setting to 115200 */
  sdStart(&SD2, NULL);
  chprintf((BaseSequentialStream*)&SD2, "miniPowerMeter\r\n");

  UI12864_Init();
  UI12864_PutString(0, 0, "miniPowerMeter");
  UI12864_PutString(1, 10, "OLED test ok!");

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
