/*
 * BMP280_STM32.h
 *
 *  Created on: Oct 28, 2023
 *      Author: Chandula Nethmal
 */

#ifndef INC_BMP280_STM32_H_
#define INC_BMP280_STM32_H_

#define BMP280_dev_address 0xEC
extern signed long temperature_raw, pressure_raw;
extern unsigned short Dig_T1, Dig_P1;
extern signed short Dig_T2, Dig_T3, Dig_P2, Dig_P3, Dig_P4, Dig_P5, Dig_P6, Dig_P7, Dig_P8, Dig_P9;
extern float temperature, pressure, altitude, init_height;

extern uint8_t I2C_Read_Register(uint8_t device_adr, uint8_t internal_adr);

extern void I2C_Write_Register(uint8_t device_adr, uint8_t internal_adr, uint8_t data);

extern void BMP280_get_calib_values(void);

extern void BMP280_init(void);

extern void BMP280_calc_values(void);

#endif /* INC_BMP280_STM32_H_ */
