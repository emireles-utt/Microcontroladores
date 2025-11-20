#ifndef __INC_MAX7219_MATRIX_H__
#define __INC_MAX7219_MATRIX_H__

#include "main.h"

#define NUM_DEV		4

extern SPI_HandleTypeDef hspi1;

void max7219_cmd(uint8_t addr, uint8_t data);
void max_write(int row, uint8_t data);
void flushBuffer(void);
void clearDisplay(void);
void shiftLeft(void);
void shiftChar(uint8_t ch, int delay);
void scrollString(char *str, int delay);
void matrixInit(void);

#endif
