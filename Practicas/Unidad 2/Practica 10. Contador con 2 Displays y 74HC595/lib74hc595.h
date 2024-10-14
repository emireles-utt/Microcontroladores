#ifndef __LIB_74HC595_H
#define __LIB_74HC595_H
#include "main.h"
//
// PA0 - DS Pin 14 (74HC595)
// PA1 - SH_CP Pin 11 (74HC595)
// PA2 - ST_CP Pin 12 (74HC595)
//
// Entrada de dato serial (DS o SDI)
#define SDI_SetHigh()		HAL_GPIO_WritePin(SDI_GPIO_Port, SDI_Pin, GPIO_PIN_SET)
#define SDI_SetLow()		HAL_GPIO_WritePin(SDI_GPIO_Port, SDI_Pin, GPIO_PIN_RESET)

// Serial Shift Clock (SH_CP o CLK)
#define CLK_SetHigh()		HAL_GPIO_WritePin(CLK_GPIO_Port, CLK_Pin, GPIO_PIN_SET)
#define CLK_SetLow()		HAL_GPIO_WritePin(CLK_GPIO_Port, CLK_Pin, GPIO_PIN_RESET)

// Parallel Update Output (ST_CP o LATCH)
#define LATCH_SetHigh()		HAL_GPIO_WritePin(LATCH_GPIO_Port, LATCH_Pin, GPIO_PIN_SET)
#define LATCH_SetLow()		HAL_GPIO_WritePin(LATCH_GPIO_Port, LATCH_Pin, GPIO_PIN_RESET)

void shiftOut(uint8_t val);
void display_led(uint8_t *data, uint8_t len);

#endif
