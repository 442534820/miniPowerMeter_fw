#ifndef __INA226_H__
#define __INA226_H__

#include <stdint.h>
#include "device_hal.h"

/*
 * INA226 Address Pins and Slave Addresses Map
 */
#define INA226_ADDR_A1_GND_A0_GND       (0x40)
#define INA226_ADDR_A1_GND_A0_VS        (0x41)
#define INA226_ADDR_A1_GND_A0_SDA       (0x42)
#define INA226_ADDR_A1_GND_A0_SCL       (0x43)
#define INA226_ADDR_A1_VS_A0_GND        (0x44)
#define INA226_ADDR_A1_VS_A0_VS         (0x45)
#define INA226_ADDR_A1_VS_A0_SDA        (0x46)
#define INA226_ADDR_A1_VS_A0_SCL        (0x47)
#define INA226_ADDR_A1_SDA_A0_GND       (0x48)
#define INA226_ADDR_A1_SDA_A0_VS        (0x49)
#define INA226_ADDR_A1_SDA_A0_SDA       (0x4A)
#define INA226_ADDR_A1_SDA_A0_SCL       (0x4B)
#define INA226_ADDR_A1_SCL_A0_GND       (0x4C)
#define INA226_ADDR_A1_SCL_A0_VS        (0x4D)
#define INA226_ADDR_A1_SCL_A0_SDA       (0x4E)
#define INA226_ADDR_A1_SCL_A0_SCL       (0x4F)


void ina226_init(const i2c_ops_vmt* i2c_dev_ops);
void ina226_read_shunt_voltage(uint16_t* value);
void ina226_read_bus_voltage(uint16_t* value);
void ina226_read_power(uint16_t* value);
void ina226_read_current(uint16_t* value);
void ina226_read_MID(uint16_t* value);
void ina226_read_DID(uint16_t* value);
void ina226_reset(void);
void ina226_config(uint16_t config_value);
void ina226_set_calibration(uint16_t value);
void ina226_set_calibration_by_RI(float R_value, float I_value);


#endif //__INA226_H__
