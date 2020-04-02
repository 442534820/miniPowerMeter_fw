#ifndef __DEVICE_HAL_H__
#define __DEVICE_HAL_H__

#include <stdint.h>

typedef uint32_t(i2c_ops_func_t)(uint16_t DevAddr, uint8_t RegAddr, void* ptr, uint16_t size);
typedef uint32_t(spi_ops_func_t)(void* pDataOut, void* pDataIn, uint16_t size);
typedef uint32_t(spi_ioctl_func_t)(uint32_t param0, uint32_t param1);

typedef struct i2c_ops_vmt
{
	uint16_t DevStatus;
	uint16_t DevAddr;
	i2c_ops_func_t *read;
	i2c_ops_func_t *write;
}i2c_ops_vmt;

typedef struct spi_ops_vmt
{
	spi_ops_func_t *Transfer;
	spi_ioctl_func_t *ioctrl;
}spi_ops_vmt;


#endif //__DEVICE_HAL_H__
