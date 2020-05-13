#include "ui.h"
#include "font.h"
#include "button.h"
#include "button_utils.h"
#include "ui12864.h"
#include "ch.h"
#include "hal.h"
#include "chprintf.h"
#include <stdio.h>
#include <string.h>


extern volatile uint16_t bus_vot;
extern volatile int16_t shunt_vot;
extern volatile int16_t bus_cur;
extern volatile uint32_t ina_count;

#define UI_ID_MAIN 0x00
#define UI_ID_TEST 0xFF
uint8_t ui_id;

char str_buf[32];
systime_t btn_time;
uint32_t last_ina_count;
struct btn_utils_info btn[4];
const font_t *pfont;

void ui_init(void)
{
	button_init();
	btn_utils_init(&btn[0]);
	btn_utils_init(&btn[1]);
	btn_utils_init(&btn[2]);
	btn_utils_init(&btn[3]);

	UI12864_Init();
}

void ui_main(void)
{
	UI12864_Clear();
	pfont = UI12864_FontSave(&font_5x8_ascii);
	UI12864_PutString(0, 10, "miniPowerMeter");
	UI12864_FontRestore(&font_8x16_ascii);
	UI12864_PutString(2, 4, "Vot=");
	UI12864_PutString(4, 4, "Cur=");
	UI12864_PutString(6, 4, "Cap=");
	btn_time = chVTGetSystemTimeX();
	last_ina_count = ina_count;
	while (1) {
		if (chVTGetSystemTimeX() - btn_time >= 20) {
			btn_time += 20;
			button_scan();
			if (button_state[3] == BUTTON_STATE_RELEASE) {
				ui_id = UI_ID_TEST;
				UI12864_FontRestore(pfont);
				return;
			}
		}

		if (last_ina_count != ina_count) {
			last_ina_count = ina_count;

			palClearPad(GPIOA, GPIOA_LED1);
			chThdSleepMilliseconds(2);
			palSetPad(GPIOA, GPIOA_LED1);

			chsnprintf(str_buf, sizeof(str_buf), "%2.3fV", bus_vot * 0.00125f);
			UI12864_PutString(2, 40, str_buf);
			if (bus_cur < 0) {
				str_buf[0] = '-';
				chsnprintf(str_buf, sizeof(str_buf), "%4.1fmA", -1 * bus_cur * 0.05f);
			} else {
				str_buf[0] = ' ';
				chsnprintf(str_buf, sizeof(str_buf), "%4.1fmA", bus_cur * 0.05f);
			}
			UI12864_PutString(4, 40, str_buf);
#if 0
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
#endif
		}
	}
}

void ui_test(void)
{
	int i;
	unsigned char line = 1;
	systime_t free_time;

	UI12864_Clear();
	UI12864_PutString(0, 10, "Test Mode");
	btn_time = chVTGetSystemTimeX();
	free_time = chVTGetSystemTimeX();
	while (1) {
		if (chVTGetSystemTimeX() - free_time >= 10000) {
			/* AUtomatic return to main frame after idle for 10 seconds */
			ui_id = UI_ID_MAIN;
			return;
		}
		if (chVTGetSystemTimeX() - btn_time >= 20) {
			btn_time += 20;
			button_scan();
			btn_utils_process(&btn[0], button_state[0]);
			btn_utils_process(&btn[1], button_state[1]);
			btn_utils_process(&btn[2], button_state[2]);
			btn_utils_process(&btn[3], button_state[3]);
			/* Button test */
			for (i=0; i<4; i++) {
				str_buf[0] = i + '0';
				str_buf[1] = ' ';
				if (btn[i].event_raw) {
					/* any action will re-calc idle time */
					free_time = chVTGetSystemTimeX();
				}
				if (btn[i].event.short_press) {
					btn[i].event.short_press = 0;
					strcpy(str_buf+2, "Short ");
					UI12864_PutString(line, 0, str_buf);
					line = (line % 7) + 1;
				}
				if (btn[i].event.long_press) {
					btn[i].event.long_press = 0;
					strcpy(str_buf+2, "Long  ");
					UI12864_PutString(line, 0, str_buf);
					line = (line % 7) + 1;
				}
				if (btn[i].event.long_press_ex) {
					btn[i].event.long_press_ex = 0;
					strcpy(str_buf+2, "LongEx");
					UI12864_PutString(line, 0, str_buf);
					line = (line % 7) + 1;
				}
				if (btn[i].event.double_press) {
					btn[i].event.double_press = 0;
					strcpy(str_buf+2, "Double");
					UI12864_PutString(line, 0, str_buf);
					line = (line % 7) + 1;
				}
			}
		}

	}
}


void ui_entry(void)
{
	ui_id = UI_ID_MAIN;

	while (1) {
		switch (ui_id) {
		case UI_ID_MAIN:
			ui_main();
			break;
		case UI_ID_TEST:
			ui_test();
			break;
		default:
			/* Error */
			break;
		}
	}
}

