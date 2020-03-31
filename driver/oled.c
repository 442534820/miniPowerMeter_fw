#include "oled.h"
#include "font.h"
#include "ch.h"
#include "hal.h"

#define OLED_RES_0()    palClearPad(GPIOB, 11)
#define OLED_RES_1()    palSetPad(GPIOB, 11)
#define OLED_CS_0()     palClearPad(GPIOB, 12)
#define OLED_CS_1()     palSetPad(GPIOB, 12)
#define OLED_SCK_0()    palClearPad(GPIOB, 13)
#define OLED_SCK_1()    palSetPad(GPIOB, 13)
#define OLED_DC_0()     palClearPad(GPIOB, 10)
#define OLED_DC_1()     palSetPad(GPIOB, 10)
#define OLED_SDA_0()    palClearPad(GPIOB, 15)
#define OLED_SDA_1()    palSetPad(GPIOB, 15)


void oled_WriteData(uint8_t data);
void oled_WriteCmd(uint8_t cmd);
static void oled_LowlevelInit(void);

void oled_Init(void)
{
	OLED_RES_0();
	OLED_RES_1();
	
	oled_WriteCmd(0xAE);
	oled_WriteCmd(0x00);
	oled_WriteCmd(0x10);
	oled_WriteCmd(0x40);
	oled_WriteCmd(0xB0);
	
	oled_WriteCmd(0x81);
	oled_WriteCmd(0xCF);
	
	oled_WriteCmd(0xA0);
	oled_WriteCmd(0xC0);
	
	oled_WriteCmd(0xA8);
	oled_WriteCmd(0x3F);
	
	oled_WriteCmd(0xD3);
	oled_WriteCmd(0x00);
	
	oled_WriteCmd(0xD5);
	oled_WriteCmd(0x80);
	
	oled_WriteCmd(0xD9);
	oled_WriteCmd(0xF1);
	
	oled_WriteCmd(0xDA);
	oled_WriteCmd(0x12);
	
	oled_WriteCmd(0xDB);
	oled_WriteCmd(0x30);
	
	oled_WriteCmd(0x8D);
	oled_WriteCmd(0x14);
	
	oled_WriteCmd(0xAF);
}


void oled_WriteData(uint8_t data)
{
	uint8_t i;
	
	OLED_CS_0();
	OLED_DC_1();
	for(i=0;i<8;i++)
	{
		OLED_SCK_0();
		if(data & 0x80)
			OLED_SDA_1();
		else
			OLED_SDA_0();
		data <<= 1;
		OLED_SCK_1();
	}
	OLED_CS_1();
}

void oled_WriteCmd(uint8_t cmd)
{
	uint8_t i;
	
	OLED_CS_0();
	OLED_DC_0();
	for(i=0;i<8;i++)
	{
		OLED_SCK_0();
		if(cmd & 0x80)
			OLED_SDA_1();
		else
			OLED_SDA_0();
		cmd <<= 1;
		OLED_SCK_1();
	}
	OLED_CS_1();
}

void oled_UpdateWordPixcels(uint8_t Page, uint8_t Column, uint8_t dp8)
{
	oled_WriteCmd(0xB0 + Page);               //Write page address
	oled_WriteCmd(0x00 + (Column & 0x0F));    //Write column low address
	oled_WriteCmd(0x10 + (Column >> 4));      //Write column high address
	oled_WriteData(dp8);                      //Write 8-bits pixcels data
}

void oled_fill(uint8_t d)
{
	uint8_t i,j;
	
	oled_WriteCmd(0x00);
	oled_WriteCmd(0x00);
	oled_WriteCmd(0xB0);
	
	for(j=0;j<8;j++)
	{
		oled_WriteCmd(0xB0 + j);
		oled_WriteCmd(0x00);
		oled_WriteCmd(0x10);
		for(i=0;i<128;i++)
		{
			oled_WriteData(d);
		}
	}
}

void oled_putstr_at(const char* str, uint8_t x, uint8_t y, font_t* font)
{
    uint8_t i;
    const uint8_t* data;
    
    while(*str)
    {
        #if 1
            oled_WriteCmd(0xB0 + x);
            oled_WriteCmd(0x00 + (y & 0x0F));
            oled_WriteCmd(0x10 + (y >> 4));
            oled_WriteData(0x14);
            oled_WriteData(0x7f);
            oled_WriteData(0x14);
            oled_WriteData(0x7f);
            oled_WriteData(0x14);
            oled_WriteData(0x00);
        #else
        data = font->data + 8
        for(i=0;i<5;i++)
        {
            oled_WriteCmd(0xB0 + x);
            oled_WriteCmd(0x00 + (y & 0x0F));
            oled_WriteCmd(0x10 + (y >> 4));
            oled_WriteData(*data);
            data++;
        }
        #endif
        str++;
    }
}
