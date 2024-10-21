/**********************************************
	Las siguietes macros deben configurarse
	dependiendo del puerto que se quiera usar.
**********************************************/
#include "main.h"

#define PCF_ADDR	0x4E	// para prueba modulo PCF8576
//#define PCF_ADDR	0x7E	// para prueba modulo FreeNove

// comando para configurar el LCD
#define LIMPIARLCD			0x01
#define INICIOLINEA			0x02
#define RECORRECURRIZQ		0x04
#define RECORRECURRDER		0x06
#define RECORRERPANTDER		0x05
#define RECORRERPANTIZQ		0x07
#define DISPOFFCUROFF		0x08
#define DISPOFFCURON		0x0A
#define DISPONCUROFF		0x0C
#define DISPONCURBLNK1		0x0E
#define DISPONCURBLNK2		0x0F
#define DESPCURIZQ			0x10
#define DESPCURDER			0x14
#define DESPDISPIZQ			0x18
#define DESPDISPDER			0x1C
#define FORZARCURINCLINEA1	0x80
#define FORZARCURINCLINEA2	0xC0
#define DOSLINEAS5X74B		0x28
#define DOSLINEAS5X78B		0x38

void Lcd_Command(unsigned char cmnd);
void Lcd_Data(unsigned char data);
void Lcd_Init(void);
void Lcd_Gotoxy(unsigned char x, unsigned char y);
void Lcd_Print(char* str);
void Lcd_SendPacketBCD(uint8_t data);
