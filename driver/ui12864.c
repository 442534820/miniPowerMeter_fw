#include "ui12864.h"
#include "font.h"


static const font_t *ui_font;

#if UI_CHACHE_ENABLE
static uint8_t ui_cache[128][64 / 8];
static uint8_t ui_cache_hit_map[128];
#endif

void UI12864_Init(void)
{
	oled_Init();
	oled_fill(0x00);
    ui_font = &font_5x8_ascii;
}

#if UI_CHACHE_ENABLE
void UI12864_SetPixcel(uint8_t x, uint8_t y, uint8_t Color)
{
    if(Color)
        ui_cache[x][y / 8] |= 0x1 << (y % 8);
    else
        ui_cache[x][y / 8] &= ~(0x1 << (y % 8));
    ui_cache_hit_map[x] |= 1 << (y / 8);
}

void UI12864_DrawHLine(uint8_t xStart, uint8_t xEnd, uint8_t y, uint8_t Color)
{
    uint8_t i, tmp;
    if(xStart > xEnd)
    {
        tmp = xStart;
        xStart = xEnd;
        xEnd = tmp;
    }
    for(i=xStart; i<=xEnd; i++)
    {
        UI12864_SetPixcel(i, y, Color);
    }
}

void UI12864_DrawVLine(uint8_t x, uint8_t yStart, uint8_t yEnd, uint8_t Color)
{
    uint8_t i, tmp;
    if(yStart > yEnd)
    {
        tmp = yStart;
        yStart = yEnd;
        yEnd = tmp;
    }
    for(i=yStart; i<=yEnd; i++)
    {
        UI12864_SetPixcel(x, i, Color);
    }
}

void UI12864_DrawLine(uint8_t xStart, uint8_t yStart, uint8_t xEnd, uint8_t yEnd, uint8_t Color)
{
    int16_t i,dx,dy,sgndx,sgndy,dxabs,dyabs,x,y,drawx,drawy;
    
    dx = xEnd - xStart;
    dy = yEnd - yStart;
    dxabs = (dx>0) ? dx : -dx;
    dyabs = (dy>0) ? dy : -dy;
    sgndx = (dx>0) ? 1 : -1;
    sgndy = (dy>0) ? 1 : -1;
    x = dyabs / 2;
    y = dxabs / 2;
    drawx = xStart;
    drawy = yStart;
    
    UI12864_SetPixcel(drawx, drawy, Color);
    if(dxabs >= dyabs)
    {
        for(i=0; i<dxabs; i++)
        {
            y += dyabs;
            if(y >= dxabs)
            {
                y -= dxabs;
                drawy += sgndy;
            }
            drawx += sgndx;
            UI12864_SetPixcel(drawx, drawy, Color);
        }
    }
    else
    {
        for(i=0; i<dyabs; i++)
        {
            x += dxabs;
            if(x >= dyabs)
            {
                x -= dyabs;
                drawx += sgndx;
            }
            drawy += sgndy;
            UI12864_SetPixcel(drawx, drawy, Color);
        }
    }
}

void UI12864_DrawRect(uint8_t xStart, uint8_t xEnd, uint8_t yStart, uint8_t yEnd, uint8_t FrontColor, uint8_t BackColor)
{
    uint8_t i, tmp;
    if(xStart > xEnd)
    {
        tmp = xStart;
        xStart = xEnd;
        xEnd = tmp;
    }
    if(yStart > yEnd)
    {
        tmp = yEnd;
        yStart = yEnd;
        yEnd = tmp;
    }
    if(FrontColor == BackColor)
    {
        if((signed int)(xEnd - xStart) - (signed int)(yEnd - yStart) > 0)
        {
            for(i=yStart; i<=yEnd; i++)
            {
                UI12864_DrawHLine(xStart, xEnd, i, FrontColor);
            }
        }
        else
        {
            for(i=xStart; i<=xEnd; i++)
            {
                UI12864_DrawVLine(i, yStart, yEnd, FrontColor);
            }
        }
    }
}

void UI12864_DrawBitmap(uint8_t x, uint8_t y, const UI12864_Bitmap_Type *pBitmapData)
{
	uint8_t i,j,k,t;
    const uint8_t* pData;
	
	if(!pBitmapData->Height)
		return;
	if(!pBitmapData->Width)
		return;
	
    pData = pBitmapData->pData;
    for(j=1; j <= ((pBitmapData->Height - 1) / 8 +1); j++)
	{
        if(pBitmapData->Height < j*8)
            k = ((pBitmapData->Height - 1) % 8) + 1;
        else
            k = 8;
		for(i=0; i<pBitmapData->Width; i++)
		{
            for(t=0; t<k; t++)
            {
                UI12864_SetPixcel(x+i, y+(j-1)*8+t, (*pData & (0x1 << t)) ? 1 : 0);
			}
            pData++;
		}
	}
}

void UI12864_Update(void)
{
    uint8_t i,j;
    for(i=0; i<sizeof(ui_cache_hit_map); i++)
    {
        if(ui_cache_hit_map[i])
        {
            for(j=0; j<8; j++)
            {
                if(ui_cache_hit_map[i] & (0x1 << j))
                {
                    oled_UpdateWordPixcels(j, i, ui_cache[i][j]);
                }
            }
            ui_cache_hit_map[i] = 0x00;
        }
    }
}
#endif

void UI12864_PutChar(uint8_t Page, uint8_t Column, char Char)
{
	uint8_t i;
    const uint8_t* font_ptr;
    
    if((Char < ui_font->begin) || (Char > ui_font->end))
        return;
    font_ptr = (const uint8_t*)&((uint8_t*)ui_font->data)[(Char - ui_font->begin) * ui_font->width * ui_font->height / 8]; 
	
	for(i=0;i<ui_font->width;i++)
	{
		oled_UpdateWordPixcels(Page, Column + i, font_ptr[i]);
	}
}

void UI12864_PutCharReverse(uint8_t Page, uint8_t Column, char Char)
{
	uint8_t i;
    const uint8_t* font_ptr;
    
    if((Char < ui_font->begin) || (Char > ui_font->end))
        return;
    font_ptr = (const uint8_t*)&((const uint8_t*)ui_font->data)[(Char - ui_font->begin) * ui_font->height]; 
	
	for(i=0;i<ui_font->width;i++)
	{
		oled_UpdateWordPixcels(Page, Column + i, ~font_ptr[i]);
	}
}

void UI12864_PutString(uint8_t Page, uint8_t Column, char *pStr)
{
	while(*pStr)
	{
		UI12864_PutChar(Page, Column, *pStr);
		pStr++;
		Column += 6;
		if(Column >= 128 - 6)
		{
			Page++;
			Column = 0;
		}
	}
}
/*
void UI12864_DrawRect(uint8_t Page, uint8_t Column, uint8_t Height, uint8_t Width, const uint8_t *pData)
{
	uint8_t i;
	
	if(!Height)
		return;
	if(!Width)
		return;
	
	Height = (Height - 1) / 8 +1;
	while(Height--)
	{
		for(i=0;i<Width;i++)
		{
			oled_UpdateWordPixcels(Page, Column + i, *pData);
			pData++;
		}
		Page++;
	}
}
*/ /*
void UI12864_DrawBitmap(uint8_t Page, uint8_t Column, const UI12864_Bitmap_Type *pBitmapData)
{
	uint8_t i;
	uint8_t Height;
	uint8_t *pData;
	
	Height = pBitmapData->Height;
	pData = pBitmapData->pData;
	
	if(!Height)
		return;
	if(!pBitmapData->Width)
		return;
	
	Height = (Height - 1) / 8 +1;
	if(pBitmapData->Inverse)
	{
		while(Height--)
		{
			for(i=0;i<pBitmapData->Width;i++)
			{
				oled_UpdateWordPixcels(Page, Column + i, ~*pData);
				pData++;
			}
			Page++;
		}
	}
	else
	{
		while(Height--)
		{
			for(i=0;i<pBitmapData->Width;i++)
			{
				oled_UpdateWordPixcels(Page, Column + i, *pData);
				pData++;
			}
			Page++;
		}
	}
}
*/
void UI12864_Fill(uint8_t Page, uint8_t Column, uint8_t Height, uint8_t Width, uint8_t FillData)
{
	uint8_t i;
	
	if(!Height)
		return;
	if(!Width)
		return;
	
	Height = (Height - 1) / 8 +1;
	while(Height--)
	{
		for(i=0;i<Width;i++)
		{
			oled_UpdateWordPixcels(Page, Column + i, FillData);
		}
		Page++;
	}
}

void UI12864_Clear(void)
{
	UI12864_Fill(0, 0, 64, 128, 0x00);
}


