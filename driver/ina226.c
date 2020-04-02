#include "ina226.h"
#include <stdint.h>
#include <stdbool.h>

#define INA226_REG_CR                (0x00U)  //[RW] Configuration Register
#define INA226_REG_SVR               (0x01U)  //[R ] Shunt Voltage Register
#define INA226_REG_BVR               (0x02U)  //[R ] Bus Voltage Register
#define INA226_REG_PWR               (0x03U)  //[R ] Power Register
#define INA226_REG_CUR               (0x04U)  //[R ] Current Register
#define INA226_REG_CAR               (0x05U)  //[RW] Calibration Register
#define INA226_REG_MER               (0x06U)  //[RW] Mask/Enable Register
#define INA226_REG_ALR               (0x07U)  //[RW] Alert Limit Register
#define INA226_REG_MIR               (0xFEU)  //[R ] Manufacturer ID Register
#define INA226_REG_DIR               (0xFFU)  //[R ] Die ID Register



// Register Bit Map
#define INA226_CR_BLANK              (0x4000U)
#define INA226_RST                   (0x01U << 15U)
#define INA226_AVG_MASK              (0x07U <<  9U)
#define INA226_AVG_1                 (0x00U <<  9U)
#define INA226_AVG_4                 (0x01U <<  9U)
#define INA226_AVG_16                (0x02U <<  9U)
#define INA226_AVG_64                (0x03U <<  9U)
#define INA226_AVG_128               (0x04U <<  9U)
#define INA226_AVG_256               (0x05U <<  9U)
#define INA226_AVG_512               (0x06U <<  9U)
#define INA226_AVG_1024              (0x07U <<  9U)
#define INA226_VBUSCT_MASK           (0x07U <<  6U)
#define INA226_VBUSCT_140US          (0x00U <<  6U)
#define INA226_VBUSCT_204US          (0x01U <<  6U)
#define INA226_VBUSCT_332US          (0x02U <<  6U)
#define INA226_VBUSCT_588US          (0x03U <<  6U)
#define INA226_VBUSCT_1100US         (0x04U <<  6U)
#define INA226_VBUSCT_2116US         (0x05U <<  6U)
#define INA226_VBUSCT_4156US         (0x06U <<  6U)
#define INA226_VBUSCT_8244US         (0x07U <<  6U)
#define INA226_VSHCT_MASK            (0x07U <<  3U)
#define INA226_VSHCT_140US           (0x00U <<  3U)
#define INA226_VSHCT_204US           (0x01U <<  3U)
#define INA226_VSHCT_332US           (0x02U <<  3U)
#define INA226_VSHCT_588US           (0x03U <<  3U)
#define INA226_VSHCT_1100US          (0x04U <<  3U)
#define INA226_VSHCT_2116US          (0x05U <<  3U)
#define INA226_VSHCT_4156US          (0x06U <<  3U)
#define INA226_VSHCT_8244US          (0x07U <<  3U)
#define INA226_MODE_MASK             (0x07U <<  0U)
#define INA226_MODE_PD               (0x00U <<  0U)
#define INA226_MODE_SVT              (0x01U <<  0U)
#define INA226_MODE_BVT              (0x02U <<  0U)
#define INA226_MODE_SBT              (0x03U <<  0U)
#define INA226_MODE_PD_              (0x04U <<  0U)
#define INA226_MODE_SVC              (0x05U <<  0U)
#define INA226_MODE_BVC              (0x06U <<  0U)
#define INA226_MODE_SBC              (0x07U <<  0U)

#define INA226_MASK_SOL              (0x01U << 15U)  //Shunt Voltage Over-Voltage
#define INA226_MASK_SUL              (0x01U << 14U)  //Shunt Voltage Under-Voltage
#define INA226_MASK_BOL              (0x01U << 13U)  //Bus Voltage Over-Voltage
#define INA226_MASK_BUL              (0x01U << 12U)  //Bus Voltage Under-Voltage
#define INA226_MASK_POL              (0x01U << 11U)  //Power Over-Limit
#define INA226_MASK_CNVR             (0x01U << 10U)  //Conversion Ready

#define INA226_MASK_AFF              (0x01U <<  4U)  //Alert Function Flag
#define INA226_MASK_CVRF             (0x01U <<  3U)  //Conversion Ready Flag
#define INA226_MASK_OVF              (0x01U <<  2U)  //Math Overflow Flag
#define INA226_MASK_APOL             (0x01U <<  1U)  //Alert Polarity bit
#define INA226_MASK_LEN              (0x01U <<  0U)  //Alert Latch Enable

#define U16_SWAP(x)                  ((uint16_t)((((uint16_t)x) >> 8) | (((uint16_t)x) << 8)))


static i2c_ops_vmt ina226;

void ina226_init(const i2c_ops_vmt* i2c_dev_ops)
{
	ina226.DevAddr = i2c_dev_ops->DevAddr;
	ina226.read = i2c_dev_ops->read;
	ina226.write = i2c_dev_ops->write;
}

void ina226_read_shunt_voltage(uint16_t* value)
{
	uint16_t data;

	ina226.read(ina226.DevAddr, INA226_REG_SVR, &data, 2);
	*value = U16_SWAP(data);
}

void ina226_read_bus_voltage(uint16_t* value)
{
	uint16_t data;

	ina226.read(ina226.DevAddr, INA226_REG_BVR, &data, 2);
	*value = U16_SWAP(data);
}

void ina226_read_power(uint16_t* value)
{
	uint16_t data;

	ina226.read(ina226.DevAddr, INA226_REG_PWR, &data, 2);
	*value = U16_SWAP(data);
}

void ina226_read_current(uint16_t* value)
{
	uint16_t data;

	ina226.read(ina226.DevAddr, INA226_REG_CUR, &data, 2);
	*value = U16_SWAP(data);
}

void ina226_read_MID(uint16_t* value)
{
	uint16_t data;

	ina226.read(ina226.DevAddr, INA226_REG_MIR, &data, 2);
	*value = U16_SWAP(data);
}

void ina226_read_DID(uint16_t* value)
{
	uint16_t data;

	ina226.read(ina226.DevAddr, INA226_REG_DIR, &data, 2);
	*value = U16_SWAP(data);
}

void ina226_reset(void)
{
	uint16_t data;

	data = U16_SWAP(INA226_RST);
	ina226.write(ina226.DevAddr, INA226_REG_CR, &data, 2);
}

void ina226_config(uint16_t config_value)
{
	uint16_t data;

	data = U16_SWAP(config_value | INA226_CR_BLANK);
	ina226.write(ina226.DevAddr, INA226_REG_CR, &data, 2);	
}

/*
	CAL = 0.00512 / Current_LSB / Rsense
*/
void ina226_set_calibration(uint16_t value)
{
	uint16_t data;

	data = U16_SWAP(value);
	ina226.write(ina226.DevAddr, INA226_REG_CAR, &data, 2);
}

/*
	@biref: Config INA226 calibration value by R_sense and the I_min
	@param R_value: R_sense value  1m Ohm
	@param I_value: I_min value  1mA
*/
void ina226_set_calibration_by_RI(float R_value, float I_value)
{
	uint16_t cal_value;

	cal_value = (uint16_t)(5120.0 / I_value / R_value);
	ina226_set_calibration(cal_value);
}

