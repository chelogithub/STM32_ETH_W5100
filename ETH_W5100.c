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
	SPI_ETH(x);
	x->TX[2]++;
 }
}

uint8_t SPI_ETH_PORT_CMD(struct  W5100_SPI * y, uint8_t z)
{
	y->TX[1]= SPI_WRITE ;
	y->TX[1]= S0_CR_ADDR_BASEH ;
	y->TX[2]= S0_CR_ADDR_BASEL ;
	y->TX[3]= z ;		//Lo carga en la info a enviar
	SPI_ETH(y);
}


