#ifndef __OLED_H__
#define __OLED_H__

#include <stdint.h>


void oled_Init(void);
void oled_fill(uint8_t d);
void oled_UpdateWordPixcels(uint8_t Page, uint8_t Column, uint8_t dp8);


#endif

