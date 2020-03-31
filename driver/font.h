#ifndef __FONT_H__
#define __FONT_H__

#include <stdint.h>

typedef struct font_t
{
    const char* name;      //字体名
    uint8_t width;         //宽度
    uint8_t height;        //高度
    uint8_t mode;          //取模方向
    uint16_t begin;        //字库起始
    uint16_t end;          //字库结束
    uint16_t len;          //字库个数
    const void* data;      //字模数据
}font_t;


extern const font_t font_5x8_ascii;
extern const font_t font_8x16_ascii;

#endif
