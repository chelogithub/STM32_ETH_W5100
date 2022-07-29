/*
 * ETH_W5100.c
 *
 *  Created on: 18 jul. 2022
 *      Author: mggarcia
 */

#include "ETH_W5100.h"


// ****** Begin Socket Memory assignment ****** //
uint16_t gS0_RX_BASE = 0x6000;
uint16_t gS0_RX_MASK = 0x07FF;
uint16_t gS1_RX_BASE = 0x6800;
uint16_t gS1_RX_MASK = 0x07FF;
uint16_t gS2_RX_BASE = 0x7000;
uint16_t gS2_RX_MASK = 0x07FF;
uint16_t gS3_RX_BASE = 0x7800;
uint16_t gS3_RX_MASK = 0x07FF;

uint16_t gS0_TX_BASE = 0x4000;
uint16_t gS0_TX_MASK = 0x07FF;
uint16_t gS1_TX_BASE = 0x4800;
uint16_t gS1_TX_MASK = 0x07FF;
uint16_t gS2_TX_BASE = 0x5000;
uint16_t gS2_TX_MASK = 0x07FF;
uint16_t gS3_TX_BASE = 0x5800;
uint16_t gS3_TX_MASK = 0x07FF;

uint16_t nr016bit = ByteToInt( S0_RX_SZ_ADDR_BASEHH, S0_RX_SZ_ADDR_BASEHL ); // #include "STR_Chelo.h"
// ****** End Socket Memory assignment ****** //



uint8_t  SPI_ETH(struct  W5100_SPI * x )
{
	x->TX[0]= x->operacion; //asigno lectura o escritura
	HAL_GPIO_WritePin(x->PORT, x->PIN , GPIO_PIN_RESET);				// NSS LOW
	HAL_SPI_TransmitReceive(x->SPI, x->TX , x->RX, 4, 100);						//SPI COMM
	HAL_GPIO_WritePin(x->PORT, x->PIN , GPIO_PIN_SET);			//NSS HIGH
	return (x->RX[3]);
}

uint16_t SPI_ETH_REG(struct W5100_SPI * x, uint8_t addrh, uint8_t addrl, uint8_t op, uint8_t * data, uint8_t lnght)
{
 uint16_t res=0;
 x->TX[0]= op; //asigno lectura o escritura
 x->TX[1]= addrh;
 x->TX[2]= addrl;
 if(op = SPI_WRITE)
 {
	 for(int i=0; i<(lnght); i++)
	 {
		x->TX[3]=data[i];
		res=SPI_ETH(x);
		x->TX[2]++;
	 }
	 return(res);
 }
	 if(op = SPI_READ)
	 {
	   if (lnght==2)
		{
		for(int i=0; i<(lnght); i++)
			{
			res=SPI_ETH(x);
			x->TX[2]++;
			}
		 return(res);
		}else
		{
			res=SPI_ETH(x);
			x->TX[2]++;
			return(res);
		}
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


