/*
 * ETH_W5100.c
 *
 *  Created on: 18 jul. 2022
 *      Author: mggarcia
 */

#include "ETH_W5100.h"

uint8_t  SPI_ETH(struct  W5100_SPI * x )
{
	x->TX[0]= x->operacion; //asigno lectura o escritura
	HAL_GPIO_WritePin(x->PORT, x->PIN , GPIO_PIN_RESET);				// NSS LOW
	HAL_SPI_TransmitReceive(x->SPI, x->TX , x->RX, 4, 100);						//SPI COMM
	HAL_GPIO_WritePin(x->PORT, x->PIN , GPIO_PIN_SET);			//NSS HIGH
	return (x->RX[3]);
}

uint8_t SPI_ETH_REG(struct W5100_SPI * x, uint8_t addrh, uint8_t addrl, uint8_t op, uint8_t * data, uint8_t lnght)
{

 x->TX[0]= op; //asigno lectura o escritura
 x->TX[1]= addrh;
 x->TX[2]= addrl;
 for(int i=0; i<(lnght); i++)
 {

	x->TX[3]=data[i];
	HAL_GPIO_WritePin(x->PORT, x->PIN , GPIO_PIN_RESET);				// NSS LOW
	HAL_SPI_TransmitReceive(x->SPI, x->TX , x->RX, 4, 100);						//SPI COMM
	HAL_GPIO_WritePin(x->PORT, x->PIN , GPIO_PIN_SET);			//NSS HIGH
	x->TX[2]++;

 }

}


/*uint8_t SPI_ETH_REGS(struct W5100_SPI * x, uint8_t addrh, uint8_t addrl, uint8_t op, uint8_t gwy1, uint8_t gwy2, uint8_t gwy3, uint8_t gwy4)
{
 uint8_t data[4];
 data[0]=gwy1;
 data[1]=gwy2;
 data[2]=gwy3;
 data[3]=gwy4;
 x->TX[0]= op; //asigno lectura o escritura
 x->TX[1]= addrh;
 x->TX[2]= addrl;
 for(int i=0; i<4; i++)
 {

	x->TX[3]=data[i];
	HAL_GPIO_WritePin(x->PORT, x->PIN , GPIO_PIN_RESET);				// NSS LOW
	HAL_SPI_TransmitReceive(x->SPI, x->TX , x->RX, 4, 100);						//SPI COMM
	HAL_GPIO_WritePin(x->PORT, x->PIN , GPIO_PIN_SET);			//NSS HIGH
	x->TX[2]++;

 }

}*/
/* OLD
uint8_t  SPI_COM( SPI_HandleTypeDef *SPI, GPIO_TypeDef * GPIONSS , uint16_t a, int  op, char * addr, char * data)
{
	addr[0]=op; //asigno lectura o escritura
	HAL_GPIO_WritePin(GPIONSS, a , GPIO_PIN_RESET);				// NSS LOW
	HAL_SPI_TransmitReceive(SPI, addr, data, 4, 100);						//SPI COMM
	HAL_GPIO_WritePin(GPIONSS, a , GPIO_PIN_SET);			//NSS HIGH
	return (data[3]);
}*/
