#include "lib74hc595.h"

//
// Esta funcion recorre el dato y saca bit a bit  por el pin seleccionado.
//
void shiftOut(uint8_t val){
	uint8_t i;							// contador de datos seriales
	
	for(i = 0; i < 8; i++){				// sacamos 8 bits seriales
		if((val & 0x80) != 0){			// es un uno en el bit mas significativo (octavo bit)?
			SDI_SetHigh();				// sacamos un uno en serie por el pin seleccionado.
		}else{							// es un cero en el bit mas significativo (octavo bit)?
			SDI_SetLow();				// sacamos un cero en serie por el pin seleccionado.
		}
		val <<= 1;						// recorremos el dato una posicion a la derecha posicion mas significativa (MSB).
		CLK_SetHigh();					// enviamos un flanco de subida al 74HC595 en el pin SH_CP
		CLK_SetLow();					// para hacer un corrimiento en el registro de corrimientos.
	}
}

//
// Esta funcion recibe el dato que sera sacado serialmente y
// habilitamos el LATCH (salida paralela) de salida del 74HC595.
//
void display_led(uint8_t *data, uint8_t len){
	uint8_t i;							// contador de datos que seran sacados serialmente.
	
	LATCH_SetLow();						// ponemos a bajo el pin ST_CP para despues enviar el flando de subida.
	for(i = 0; i < len; i++){			// sacamos tantos datos como se indique en la variable len.
		shiftOut(data[i]);				// pasamos los datos que seran enviados serialmente.
	}
	LATCH_SetHigh();					// enviamos el flanco de subida para habilitar la salida paralela en el 74HC595.
}