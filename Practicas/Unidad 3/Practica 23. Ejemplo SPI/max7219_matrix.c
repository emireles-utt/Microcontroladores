#include "max7219_matrix.h"
#include "Fonts.h"

uint8_t bufferCol[NUM_DEV * 8];

void max7219_cmd(uint8_t addr, uint8_t data){
	uint16_t writeData = (addr << 8) | data;

	HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, GPIO_PIN_RESET);	// habilitar esclavo
	for(int i = 0; i < NUM_DEV; i++){
		HAL_SPI_Transmit(&hspi1, (uint8_t*)&writeData, 1, 100);
	}
	HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, GPIO_PIN_SET);	// dehabilitar esclavo
}

void max_write(int row, uint8_t data){
	int devTarget = (row - 1) / 8;
	int offset = devTarget * 8;
	uint16_t writeData = 0;

	HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, GPIO_PIN_RESET);	// habilitar esclavo
	for(int dev = 0; dev < NUM_DEV; dev++){
		if(dev == devTarget){
			writeData = ((row - offset) << 8) | data;
			HAL_SPI_Transmit(&hspi1, (uint8_t*)&writeData, 1, 1000);
 		}else{
 			writeData = 0;
 			HAL_SPI_Transmit(&hspi1, (uint8_t*)&writeData, 1, 1000);
 		}
	}
	HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, GPIO_PIN_SET);	// dehabilitar esclavo
}

void flushBuffer(void){
	uint8_t bufferRow[NUM_DEV * 8] = { 0 };

	/* convert cols to rows */
	for(int i = 0; i < NUM_DEV * 8; i++){	// for loop por all the bytes
		int dev = i / 8;					// 0, 1, 2, 3 ... keep track which max is being written
		for(int j = 0; j < 8; j++){			// for loop to extract bits
			if((bufferCol[i]) & (1 << (j))){	// if the bit is 1 start extracting from the 0th bit of C0
				bufferRow[j + (8 * dev)] |= (1 << (7 - (i - (8 * dev))));	// start writing it from the 7th bit of R0
			}
		}
	}
	/* send row data */
	for(int row = 1; row <= (NUM_DEV * 8); row++){
		max_write(row, bufferRow[row - 1]);
	}
}

void clearDisplay(void){
	for (int i = 0; i < NUM_DEV * 8 - 1; i++){
		bufferCol[i] = 0;
	}
	flushBuffer();
}

void shiftLeft(void){
	for(int cnt = NUM_DEV *8 - 2; cnt >= 0; cnt--){
		bufferCol[cnt + 1] = bufferCol[cnt];
	}
	bufferCol[0] = 0;
	flushBuffer();
}

void shiftChar(uint8_t ch, int delay){
	int indx = 0;

	for (int i = 0; i < FONT_WIDTH - 1; i++){  // loop for all the bytes of the font
		uint8_t data = 0;
		/* Chnage the order of the bits */
		for (int j = 7; j >= 0; j--){  // extract bits from a single byte
			if ((MAX7219_Dot_Matrix_font[ch][indx]) & (1 << j)){  // if the bit is 1 // start extracting from the 7th bit of byte
				data |= (1 << (7 - j));  // start writing it from the 0th bit of data
			}
		}
		bufferCol[0] = data;  // store the modified byte to the first element only. It will shift later
		flushBuffer();
		shiftLeft();
		indx++;
		HAL_Delay(delay);
	}
}

void scrollString(char *str, int delay){
	while(*str){
		shiftChar(*str, delay);
		str++;
	}
}

void matrixInit(void){
	max7219_cmd(0x09, 0);			// no decoding
	max7219_cmd(0x0A, 0x01);		// 3/32 intensity
	max7219_cmd(0x0B, 0x07);		// scan all 7 columns
	max7219_cmd(0x0C, 0x01);		// normal operation
	max7219_cmd(0x0F, 0);			// no display test
}

