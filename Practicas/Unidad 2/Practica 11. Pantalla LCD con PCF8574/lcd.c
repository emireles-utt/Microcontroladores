#include "lcd.h"

extern I2C_HandleTypeDef hi2c1;

/**************************************************
	Funcion para enviar comandos al LCD
	RS = 0 (modo comando)
	EN = 1 (habiliatamos el LCD)
**************************************************/
void Lcd_Command(unsigned char cmd)
{
	char data_u, data_l;
	uint8_t data_t[4];
	
	data_u = (cmd & 0xF0);
	data_l = ((cmd << 4) & 0xf0);
	data_t[0] = data_u | 0x0C;  //en=1, rs=0
	data_t[1] = data_u | 0x08;  //en=0, rs=0
	data_t[2] = data_l | 0x0C;  //en=1, rs=0
	data_t[3] = data_l | 0x08;  //en=0, rs=0
	HAL_I2C_Master_Transmit (&hi2c1, PCF_ADDR, (uint8_t *)data_t, 4, 100);
}
/***************************************************
	Funcion para enviar datos al LCD
	RS = 1 (modo dato)
	EN = 1 (habilitamos el LCD)
***************************************************/
void Lcd_Data(unsigned char data)
{
	char data_u, data_l;
	uint8_t data_t[4];
	
	data_u = (data & 0xf0);
	data_l = ((data << 4) & 0xf0);
	data_t[0] = data_u | 0x0D;  //en=1, rs=1
	data_t[1] = data_u | 0x09;  //en=0, rs=1
	data_t[2] = data_l | 0x0D;  //en=1, rs=1
	data_t[3] = data_l | 0x09;  //en=0, rs=1
	HAL_I2C_Master_Transmit (&hi2c1, PCF_ADDR, (uint8_t *)data_t, 4, 100);
}

/***************************************************
	Funcion para inicializar el LCD
	Nota: Esta funcion debe ser llama antes de 
	enviar cualquier dato o comando al LCD.
***************************************************/
void Lcd_Init(void)
{
	Lcd_Command(0x33);			// secuencia de inicio para el LCD
	Lcd_Command(0x32);
	Lcd_Command(DOSLINEAS5X74B);	// configuramos 2 lineas y matriz de 5x7 e interfaz de 4 bits
	Lcd_Command(DISPONCUROFF);	// Display on, cursor off
	Lcd_Command(LIMPIARLCD);		// borramos el LCD
	HAL_Delay(2);
}

/***************************************************
	Funcion para posicionar el cursor del LCD
	en las coordenadas X y Y.
	Nota: La primera linea es X = 1, Y = 1
		  La segunda linea es X = 1, Y = 1
	Formato:
		  lcd_gotoxy(x, y)
***************************************************/
void Lcd_Gotoxy(uint8_t x, uint8_t y)
{
	uint8_t firstCharAdr[] = {0x80, 0xC0, 0x94, 0xD4};
	Lcd_Command(firstCharAdr[y - 1] + x - 1);
}

/***************************************************
	Funcion para sacar una cadena de caracteres
	por el LCD.
	La funcion recibe un arreglo de caracteres
	para desplegarlos en el LCD.
***************************************************/
void Lcd_Print(char* str)
{
	while(*str)
	{
		Lcd_Data(*str++);
	}
}

void Lcd_SendPacketBCD(uint8_t data)
{
	Lcd_Data('0' + (data >> 4));
	Lcd_Data('0' + (data & 0x0F));
}
