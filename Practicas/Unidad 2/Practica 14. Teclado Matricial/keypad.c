#include "keypad.h"

char read_keypad(void)
{
	/* Ponemos ROW 1 a BAJO y las demas COLUMNAS a alto */
	HAL_GPIO_WritePin (R1_GPIO_Port, R1_Pin, GPIO_PIN_RESET);	// R1 low
	HAL_GPIO_WritePin (R2_GPIO_Port, R2_Pin, GPIO_PIN_SET);		// R2 High
	HAL_GPIO_WritePin (R3_GPIO_Port, R3_Pin, GPIO_PIN_SET);		// R3 High
	HAL_GPIO_WritePin (R4_GPIO_Port, R4_Pin, GPIO_PIN_SET);		// R4 High

	if (!(HAL_GPIO_ReadPin (C1_GPIO_Port, C1_Pin)))   // si COL 1 es bajo
	{
		while (!(HAL_GPIO_ReadPin (C1_GPIO_Port, C1_Pin)));   // esperamos a que el boton sea presionado
		return '1';
	}

	if (!(HAL_GPIO_ReadPin (C2_GPIO_Port, C2_Pin)))   // si COL 2 es bajo
	{
		while (!(HAL_GPIO_ReadPin (C2_GPIO_Port, C2_Pin)));   // esperamos a que el boton sea presionado
		return '2';
	}

	if (!(HAL_GPIO_ReadPin (C3_GPIO_Port, C3_Pin)))   // si COL 3 es bajo
	{
		while (!(HAL_GPIO_ReadPin (C3_GPIO_Port, C3_Pin)));   // esperamos a que el boton sea presionado
		return '3';
	}

	if (!(HAL_GPIO_ReadPin (C4_GPIO_Port, C4_Pin)))   // si COL 3 es bajo
	{
		while (!(HAL_GPIO_ReadPin (C4_GPIO_Port, C4_Pin)));   // esperamos a que el boton sea presionado
		return 'A';
	}

	/* Ponemos ROW 1 a BAJO y las demas COLUMNAS a alto */
	HAL_GPIO_WritePin (R1_GPIO_Port, R1_Pin, GPIO_PIN_SET);		// R1 High
	HAL_GPIO_WritePin (R2_GPIO_Port, R2_Pin, GPIO_PIN_RESET);	// R2 Low
	HAL_GPIO_WritePin (R3_GPIO_Port, R3_Pin, GPIO_PIN_SET);		// R3 High
	HAL_GPIO_WritePin (R4_GPIO_Port, R4_Pin, GPIO_PIN_SET);		// R4 High

	if (!(HAL_GPIO_ReadPin (C1_GPIO_Port, C1_Pin)))   			// si COL 1 es bajo
	{
		while (!(HAL_GPIO_ReadPin (C1_GPIO_Port, C1_Pin)));   	// esperamos a que el boton sea presionado
		return '4';
	}

	if (!(HAL_GPIO_ReadPin (C2_GPIO_Port, C2_Pin)))   			// si COL 2 es bajo
	{
		while (!(HAL_GPIO_ReadPin (C2_GPIO_Port, C2_Pin)));   	// esperamos a que el boton sea presionado
		return '5';
	}

	if (!(HAL_GPIO_ReadPin (C3_GPIO_Port, C3_Pin)))   			// si COL 3 es bajo
	{
		while (!(HAL_GPIO_ReadPin (C3_GPIO_Port, C3_Pin)));   	// esperamos a que el boton sea presionado
		return '6';
	}

	if (!(HAL_GPIO_ReadPin (C4_GPIO_Port, C4_Pin)))   			// si COL 4 es bajo
	{
		while (!(HAL_GPIO_ReadPin (C4_GPIO_Port, C4_Pin)));   	// esperamos a que el boton sea presionado
		return 'B';
	}


	/* Ponemos ROW 3 a BAJO y las demas COLUMNAS a alto */
	HAL_GPIO_WritePin (R1_GPIO_Port, R1_Pin, GPIO_PIN_SET);		// R1 High
	HAL_GPIO_WritePin (R2_GPIO_Port, R2_Pin, GPIO_PIN_SET);		// R2 High
	HAL_GPIO_WritePin (R3_GPIO_Port, R3_Pin, GPIO_PIN_RESET);	// R3 Low
	HAL_GPIO_WritePin (R4_GPIO_Port, R4_Pin, GPIO_PIN_SET);  	// R4 High

	if (!(HAL_GPIO_ReadPin (C1_GPIO_Port, C1_Pin)))   			// si COL 1 es bajo
	{
		while (!(HAL_GPIO_ReadPin (C1_GPIO_Port, C1_Pin)));   	// esperamos a que el boton sea presionado
		return '7';
	}

	if (!(HAL_GPIO_ReadPin (C2_GPIO_Port, C2_Pin)))   			// si COL 2 es bajo
	{
		while (!(HAL_GPIO_ReadPin (C2_GPIO_Port, C2_Pin)));   	// esperamos a que el boton sea presionado
		return '8';
	}

	if (!(HAL_GPIO_ReadPin (C3_GPIO_Port, C3_Pin)))   			// si COL 3 es bajo
	{
		while (!(HAL_GPIO_ReadPin (C3_GPIO_Port, C3_Pin)));   	// esperamos a que el boton sea presionado
		return '9';
	}

	if (!(HAL_GPIO_ReadPin (C4_GPIO_Port, C4_Pin)))   			// si COL 4 es bajo
	{
		while (!(HAL_GPIO_ReadPin (C4_GPIO_Port, C4_Pin)));   	// esperamos a que el boton sea presionado
		return 'C';
	}


	/* Ponemos ROW 4 a BAJO y las demas COLUMNAS a alto */
	HAL_GPIO_WritePin (R1_GPIO_Port, R1_Pin, GPIO_PIN_SET);		// R1 High
	HAL_GPIO_WritePin (R2_GPIO_Port, R2_Pin, GPIO_PIN_SET);  	// R2 High
	HAL_GPIO_WritePin (R3_GPIO_Port, R3_Pin, GPIO_PIN_SET);  	// R3 High
	HAL_GPIO_WritePin (R4_GPIO_Port, R4_Pin, GPIO_PIN_RESET);  	// R4 Low

	if (!(HAL_GPIO_ReadPin (C1_GPIO_Port, C1_Pin)))   			// si COL 1 es bajo
	{
		while (!(HAL_GPIO_ReadPin (C1_GPIO_Port, C1_Pin)));   	// esperamos a que el boton sea presionado
		return '*';
	}

	if (!(HAL_GPIO_ReadPin (C2_GPIO_Port, C2_Pin)))   			// si COL 2 es bajo
	{
		while (!(HAL_GPIO_ReadPin (C2_GPIO_Port, C2_Pin)));   	// esperamos a que el boton sea presionado
		return '0';
	}

	if (!(HAL_GPIO_ReadPin (C3_GPIO_Port, C3_Pin)))   			// si COL 3 es bajo
	{
		while (!(HAL_GPIO_ReadPin (C3_GPIO_Port, C3_Pin)));   	// esperamos a que el boton sea presionado
		return '#';
	}

	if (!(HAL_GPIO_ReadPin (C4_GPIO_Port, C4_Pin)))   			// si COL 4 es bajo
	{
		while (!(HAL_GPIO_ReadPin (C4_GPIO_Port, C4_Pin)));   	// esperamos a que el boton sea presionado
		return 'D';
	}

	return 1;  // si no se ha presionado
}

