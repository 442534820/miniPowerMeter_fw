#include "ui.h"
#include "font.h"
#include "measure.h"
#include "button.h"
#include "button_utils.h"
#include "ui12864.h"
#include "ch.h"
#include "hal.h"
#include "chprintf.h"
#include <stdio.h>
#include <string.h>


#define UI_ID_MAIN    0x00
#define UI_ID_MENU_1  0x10
#define UI_ID_TEST    0xFF
static uint8_t ui_id;
static uint8_t measure_running;

char str_buf[32];
systime_t btn_time;
systime_t view_time;
uint32_t last_ina_count;
struct btn_utils_info btn[4];
const font_t *pfont;

union {
	uint8_t   d_u8;
	int8_t    d_i8;
	uint16_t  d_u16;
	int16_t   d_i16;
	uint32_t  d_u32;
	int32_t   d_i32;
}edit_value;

#define VIEW_CAPTION3_NUM  4
const char* const ViewCaption3[VIEW_CAPTION3_NUM] = {
	"Cap=",
	"RaI=",
	"RaU=",
	"RaC="
};


static THD_WORKING_AREA(waThread_UI, 1024);
static THD_FUNCTION(Thread_UI, arg)
{
	(void)arg;
	chRegSetThreadName("UI");
	measure_start();
	measure_running = 1;
	ui_entry();
	/* Never reach here */
	while (1);
}

void ui_init(void)
{
	button_init();
	btn_utils_init(&btn[0]);
	btn_utils_init(&btn[1]);
	btn_utils_init(&btn[2]);
	btn_utils_init(&btn[3]);

	UI12864_Init();
	chThdCreateStatic(waThread_UI, sizeof(waThread_UI), NORMALPRIO, Thread_UI, NULL);
}

void ui_main(void)
{
	static uint8_t view_mode = 0;

	UI12864_Clear();
	pfont = UI12864_FontSave(&font_5x8_ascii);
	UI12864_PutString(0, 10, "miniPowerMeter");
	UI12864_FontRestore(&font_8x16_ascii);
	UI12864_PutString(2, 4, "Vot=");
	UI12864_PutString(4, 4, "Cur=");
	UI12864_PutString(6, 4, ViewCaption3[view_mode]);
	btn_time = chVTGetSystemTimeX();
	view_time = chVTGetSystemTimeX();
	last_ina_count = ina_count;
	while (1) {
		if (chVTGetSystemTimeX() - btn_time >= 20) {
			btn_time += 20;
			button_scan();
			if (button_state[3] == BUTTON_STATE_RELEASE) {
				ui_id = UI_ID_MENU_1;
				UI12864_FontRestore(pfont);
				return;
			}
			if (button_state[2] == BUTTON_STATE_RELEASE) {
				view_mode = (view_mode + 1) % VIEW_CAPTION3_NUM;
				UI12864_PutString(6, 40, "          ");
				UI12864_PutString(6, 4, ViewCaption3[view_mode]);
			}
			if (button_state[1] == BUTTON_STATE_RELEASE) {
				if (view_mode == 0)
					view_mode = VIEW_CAPTION3_NUM;
				view_mode--;
				UI12864_PutString(6, 40, "          ");
				UI12864_PutString(6, 4, ViewCaption3[view_mode]);
			}
			if (button_state[0] == BUTTON_STATE_RELEASE) {
				if (measure_running) {
					measure_running = 0;
					measure_stop();
				} else {
					measure_running = 1;
					measure_start();
				}
			}
		}

		if ((last_ina_count != ina_count) && (chVTGetSystemTimeX() - view_time >= 200)) {
			last_ina_count = ina_count;
			view_time += 200;

			palClearPad(GPIOA, GPIOA_LED1);
			chThdSleepMilliseconds(2);
			palSetPad(GPIOA, GPIOA_LED1);

			chsnprintf(str_buf, sizeof(str_buf), "%5.3fV", bus_vot * 0.00125f);
			UI12864_PutString(2, 40, str_buf);
			if (bus_cur < 0) {
				str_buf[0] = '-';
				chsnprintf(str_buf + 1, sizeof(str_buf), "%5.1fmA", -1 * bus_cur * 0.05f);
			} else {
				str_buf[0] = ' ';
				chsnprintf(str_buf + 1, sizeof(str_buf), "%5.1fmA", bus_cur * 0.05f);
			}
			UI12864_PutString(4, 40, str_buf);
			switch (view_mode) {
			case 0 : {
				float cap_val = cap_sum * 0.05 / 1000.0 / 3600.0; //Convert to mAh
				if (cap_val >= 1000000)
					chsnprintf(str_buf, sizeof(str_buf), "--over--mAh");
				else if (cap_val >= 100000)
					chsnprintf(str_buf, sizeof(str_buf), "%6.0fmAh", cap_val);
				else if (cap_val >= 10000)
					chsnprintf(str_buf, sizeof(str_buf), "%6.1fmAh", cap_val);
				else if (cap_val >= 1000)
					chsnprintf(str_buf, sizeof(str_buf), "%6.2fmAh", cap_val);
				else if (cap_val >= 100)
					chsnprintf(str_buf, sizeof(str_buf), "%6.3fmAh", cap_val);
				else if (cap_val >= 10)
					chsnprintf(str_buf, sizeof(str_buf), "%6.4fmAh", cap_val);
				else if (cap_val >= 1)
					chsnprintf(str_buf, sizeof(str_buf), "%6.5fmAh", cap_val);
				else if (cap_val >= 0)
					chsnprintf(str_buf, sizeof(str_buf), "%6.6fmAh", cap_val);
				else if (cap_val > -1)
					chsnprintf(str_buf, sizeof(str_buf), "%5.5fmAh", cap_val);
				else if (cap_val > -10)
					chsnprintf(str_buf, sizeof(str_buf), "%5.4fmAh", cap_val);
				else if (cap_val > -100)
					chsnprintf(str_buf, sizeof(str_buf), "%5.3fmAh", cap_val);
				else if (cap_val > -1000)
					chsnprintf(str_buf, sizeof(str_buf), "%5.2fmAh", cap_val);
				else if (cap_val > -10000)
					chsnprintf(str_buf, sizeof(str_buf), "%5.1fmAh", cap_val);
				else if (cap_val > -100000)
					chsnprintf(str_buf, sizeof(str_buf), "%5.0fmAh", cap_val);
				else
					chsnprintf(str_buf, sizeof(str_buf), "--over--mAh");
				UI12864_PutString(6, 40, str_buf);
				break;
				}
			case 1:
				chsnprintf(str_buf, sizeof(str_buf), "%04X", bus_cur);
				UI12864_PutString(6, 40, str_buf);
				break;
			case 2:
				chsnprintf(str_buf, sizeof(str_buf), "%4.2fuV", shunt_vot * 2.5f);
				UI12864_PutString(6, 40, str_buf);
				break;
			case 3:
				chsnprintf(str_buf, sizeof(str_buf), "%d", cap_sum);
				UI12864_PutString(6, 40, str_buf);
				break;
			}
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

#define MENU_BORDER_TOP 2
#define MENU_BORDER_LEF 0
#define MENU_BORDER_HEIGHT 6

#define MENU_1_COUNT 4
const char* const MENU_1_STRINGS[MENU_1_COUNT] = {
	"..    ",
	"Period",
	"Led   ",
	"Clear ",
};

void ui_menu_1_update(uint8_t menu_off, uint8_t menu_index)
{
	uint8_t i;

	for (i=0; i<MENU_BORDER_HEIGHT; i++) {
		if (i+menu_off >= MENU_1_COUNT)
			return;
		if (i+menu_off == menu_index)
			UI12864_PutStringReverse(i+MENU_BORDER_TOP,
					MENU_BORDER_LEF,
					MENU_1_STRINGS[menu_index]);
		else
			UI12864_PutString(i+MENU_BORDER_TOP,
					MENU_BORDER_LEF,
					MENU_1_STRINGS[i+menu_off]);
	}
}

void ui_menu_1_view_value(void)
{
	chsnprintf(str_buf, sizeof(str_buf), "%6d", measure_get_period());
	UI12864_PutString(3, 64, str_buf);
	UI12864_PutString(4, 64, "    ON");
}

/*
 * trig_type : 0=normal trig  1=continuous trig
 */
uint8_t ui_menu_1_tune(uint8_t button_index, uint8_t trig_type)
{
	static uint8_t menu_off = 0;
	static uint8_t menu_cursor = 0;
	static uint8_t menu_selected = 0;
	uint8_t ret = 0;
	uint8_t changed = 0;

	if (menu_selected) {
		switch (menu_cursor) {
		case 0:
			break; //Error '..' can not be selected
		case 1:
			switch (button_index) {
			case 0:
				/* Abort period edit */
				edit_value.d_u16 = measure_get_period();
				chsnprintf(str_buf, sizeof(str_buf), "%6d", edit_value.d_u16);
				UI12864_PutString(3, 64, str_buf);
				menu_selected = 0;
				break;
			case 1:
				/* Decrease period value */
				if (edit_value.d_u16 > 2) {
					edit_value.d_u16--;
					chsnprintf(str_buf, sizeof(str_buf), "%6d", edit_value.d_u16);
					UI12864_PutStringReverse(3, 64, str_buf);
				}
				break;
			case 2:
				/* Increase period value */
				if (edit_value.d_u16 < 60000) {
					chsnprintf(str_buf, sizeof(str_buf), "%6d", edit_value.d_u16);
					UI12864_PutStringReverse(3, 64, str_buf);
					edit_value.d_u16++;
				}
				break;
			case 3:
				/* Apply period edit */
				measure_set_period(edit_value.d_u16);
				measure_stop();
				measure_start();
				chsnprintf(str_buf, sizeof(str_buf), "%6d", edit_value.d_u16);
				UI12864_PutString(3, 64, str_buf);
				menu_selected = 0;
				break;
			}
			break;
		case 2:
			switch (button_index) {
			case 0:
				/* Abort LED switch */
				UI12864_PutString(4, 64, "    ON");
				menu_selected = 0;
				break;
			case 1:
			case 2:
				/* Switch LED ON/OFF */
				edit_value.d_u8 = !edit_value.d_u8;
				if (edit_value.d_u8) {
					UI12864_PutStringReverse(4, 64, "    ON");
				} else {
					UI12864_PutStringReverse(4, 64, "   OFF");
				}
				break;
			case 3:
				/* Aplly LED switch */
				// TODO
				UI12864_PutString(4, 64, "    ON");
				menu_selected = 0;
				break;
			}
			break;
		case 3:
			break; //Error 'Clear' can not be selected
		}
	} else {
		switch (button_index) {
		case 0:
			/* Turn back */
			return 0xFF;
		case 1:
			/* Cursor up */
			if (menu_cursor > 0)
				menu_cursor--;
			else
				menu_cursor = MENU_1_COUNT-1;
			changed = 1;
			break;
		case 2:
			/* Cursor down */
			if (menu_cursor < MENU_1_COUNT-1)
				menu_cursor++;
			else
				menu_cursor = 0;
			changed = 1;
			break;
		case 3:
			/* Enter or select */
			switch (menu_cursor) {
			case 0:
				/* Turn back */
				return 0xFF;
			case 1:
				edit_value.d_u8 = measure_get_period();
				chsnprintf(str_buf, sizeof(str_buf), "%6d", edit_value.d_u16);
				UI12864_PutStringReverse(3, 64, str_buf);
				menu_selected = 1;
				break;
			case 2:
				edit_value.d_u8 = 0; //TODO
				if (edit_value.d_u8) {
					UI12864_PutStringReverse(4, 64, "    ON");
				} else {
					UI12864_PutStringReverse(4, 64, "   OFF");
				}
				menu_selected = 1;
				break;
			case 3:
				/* Clear capacity acc */
				measure_clear();
				break;
			}
			break;
		}
	}
	if (changed) {
		ui_menu_1_update(menu_off, menu_cursor);
	}

	return ret;
}

void ui_menu(void)
{
	uint8_t ret;
	uint8_t i;

	UI12864_Clear();
	pfont = UI12864_FontSave(&font_5x8_ascii);
	UI12864_PutString(0, 10, "Sys Conifg");
	ui_menu_1_update(0, 0);
	ui_menu_1_view_value();
	btn_time = chVTGetSystemTimeX();
	while (1) {
		if (chVTGetSystemTimeX() - btn_time >= 20) {
			btn_time += 20;
			button_scan();
			/* Just process + - button */
			btn_utils_process(&btn[1], button_state[1]);
			btn_utils_process(&btn[2], button_state[2]);
			for (i=1; i<=2; i++) {
				if (btn[i].event.long_press_ex) {
					btn[i].event.long_press_ex = 0;
					ui_menu_1_tune(i, 1);
				}
			}
			for (i=0; i<4; i++) {
				if (button_state[i] == BUTTON_STATE_RELEASE) {
					ret = ui_menu_1_tune(i, 0);
					if (ret == 0xFF) {
						ui_id = UI_ID_MAIN;
						return;
					}
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
		case UI_ID_MENU_1:
			ui_menu();
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

