#ifndef __UI12864_H__
#define __UI12864_H__

#include <stdint.h>
#include "oled.h"
#include "font.h"


#define UI_CHACHE_ENABLE            (1)

typedef struct
{
	uint8_t Height;
	uint8_t Width;
	uint8_t Inverse;
	const uint8_t *pData;
}UI12864_Bitmap_Type;


extern void UI12864_Init(void);
extern void UI12864_PutChar(uint8_t Page, uint8_t Column, char Char);
extern void UI12864_PutCharReverse(uint8_t Page, uint8_t Column, char Char);
extern void UI12864_PutString(uint8_t Page, uint8_t Column, const char *pStr);
//extern void UI12864_DrawRect(uint8_t Page, uint8_t Column, uint8_t Height, uint8_t Width, const uint8_t *pData);
//extern void UI12864_DrawBitmap(uint8_t Page, uint8_t Column, const UI12864_Bitmap_Type *pBitmapData);
extern void UI12864_Fill(uint8_t Page, uint8_t Column, uint8_t Height, uint8_t Width, uint8_t FillData);
extern void UI12864_Clear(void);
extern const font_t* UI12864_FontSave(const font_t *font);
extern void UI12864_FontRestore(const font_t *font);


#if UI_CHACHE_ENABLE
void UI12864_SetPixcel(uint8_t x, uint8_t y, uint8_t Color);
void UI12864_DrawHLine(uint8_t xStart, uint8_t xEnd, uint8_t y, uint8_t Color);
void UI12864_DrawVLine(uint8_t x, uint8_t yStart, uint8_t yEnd, uint8_t Color);
void UI12864_DrawLine(uint8_t xStart, uint8_t yStart, uint8_t xEnd, uint8_t yEnd, uint8_t Color);
void UI12864_DrawRect(uint8_t xStart, uint8_t xEnd, uint8_t yStart, uint8_t yEnd, uint8_t FrontColor, uint8_t BackColor);
void UI12864_DrawBitmap(uint8_t x, uint8_t y, const UI12864_Bitmap_Type *pBitmapData);
void UI12864_Update(void);
#endif


#endif
