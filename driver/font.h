#ifndef __FONT_H__
#define __FONT_H__

#include <stdint.h>

typedef struct font_t
{
    const char* name;      //������
    uint8_t width;         //���
    uint8_t height;        //�߶�
    uint8_t mode;          //ȡģ����
    uint16_t begin;        //�ֿ���ʼ
    uint16_t end;          //�ֿ����
    uint16_t len;          //�ֿ����
    const void* data;      //��ģ����
}font_t;


extern const font_t font_5x8_ascii;
extern const font_t font_8x16_ascii;

#endif
