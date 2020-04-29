#include <stdbool.h>
#include <stddef.h>
#include "ina226.h"
//#include "bq25601.h"
//#include "YB24.h"
#include "ch.h"
#include "hal.h"

/*
 * Implement low level driver for porting device to SOC
 */
static const I2CConfig i2cfg1 = {
	STM32_TIMINGR_PRESC(0U) |
	STM32_TIMINGR_SCLDEL(1U) | STM32_TIMINGR_SDADEL(0U) |
	STM32_TIMINGR_SCLH(2U)  | STM32_TIMINGR_SCLL(10U),
	0,
	0
};

static void i2c_dev_init(void)
{
    i2cStart(&I2CD1, &i2cfg1);
}

static uint32_t i2c_read(uint16_t DevAddr, uint8_t RegAddr, void* ptr, uint16_t size)
{
	msg_t msg;

	i2cAcquireBus(&I2CD1);
	do
	{
		msg = i2cMasterTransmitTimeout(&I2CD1, DevAddr, &RegAddr, 1, NULL, 0, 1000);
		if(msg != MSG_OK)
			break;
		msg = i2cMasterReceiveTimeout(&I2CD1, DevAddr, ptr, size, 1000);
		if(msg != MSG_OK)
			break;
	}while(0);
	i2cReleaseBus(&I2CD1);
	if(msg != MSG_OK)
		return 0;
	else
		return size;
}

static uint32_t i2c_write(uint16_t DevAddr, uint8_t RegAddr, void* ptr, uint16_t size)
{
	msg_t msg;
	uint16_t i;
	uint8_t tmp_data[16];

	if(size >= sizeof(tmp_data) - 1)
		return;
	tmp_data[0] = RegAddr;
	for(i=0; i<size; i++)
	{
		tmp_data[i+1] = ((uint8_t*)ptr)[i];
	}
	i2cAcquireBus(&I2CD1);
	do
	{
		msg = i2cMasterTransmitTimeout(&I2CD1, DevAddr, tmp_data, size+1, NULL, 0, 1000);
		if(msg != MSG_OK)
			break;
	}while(0);
	i2cReleaseBus(&I2CD1);
	if(msg != MSG_OK)
		return 0;
	else
		return size;
}

uint8_t spi_send_byte(uint8_t data)
{
#if 0
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) != SET);
	SPI_SendData8(SPI1, data);
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) != SET);
	return SPI_ReceiveData8(SPI1);
#endif
}

uint32_t spi_transfer(void* pDataOut, void* pDataIn, uint16_t size)
{
	uint8_t *p, *q;
#if 0
	p = pDataOut;
	q = pDataIn;
	if((p == NULL) && (q == NULL))
		return 0;
	if(p == NULL)
	{
		while(size--)
			*q++ = spi_send_byte(0xFF);
	}
	else if(q == NULL)
	{
		while(size--)
			spi_send_byte(*p++);
	}
	else
	{
		while(size--)
			*q++ = spi_send_byte(*p++);
	}
#endif
	return size;
}

uint32_t YB24_ioctrl(uint32_t param0, uint32_t param1)
{
#if 0
	switch(param0)
	{
		case SPI_IOCTRL_CS_LOW:
			GPIO_ResetBits(GPIOB, GPIO_Pin_9);
			break;
		case SPI_IOCTRL_CS_HIGH:
			GPIO_SetBits(GPIOB, GPIO_Pin_9);
			break;
	}
#endif
}

static const i2c_ops_vmt ina226 =
{
	0,
	INA226_ADDR_A1_GND_A0_GND,          //[A1:A0]=00
	i2c_read,
	i2c_write
};

static const i2c_ops_vmt bq25601 =
{
	0,
	0x6B,
	i2c_read,
	i2c_write
};

static const spi_ops_vmt YB24 =
{
	spi_transfer,
	YB24_ioctrl
};

void dev_init(void)
{
	i2c_dev_init();

	// Device Config
	ina226_init(&ina226);
	//bq25601_init(&bq25601);
	//YB24_init(&YB24);
}

