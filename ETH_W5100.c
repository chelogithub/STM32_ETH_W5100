/*
 * ETH_W5100.c
 *
 *  Created on: 18 jul. 2022
 *      Author: mggarcia
 */

#include "ETH_W5100.h"


// ****** Begin Socket Memory assignment ****** //
/*void setVar_ETH(void)
{
	gS0_RX_BASE = 0x6000;
	gS0_RX_MASK = 0x07FF;
	gS1_RX_BASE = 0x6800;
	gS1_RX_MASK = 0x07FF;
	gS2_RX_BASE = 0x7000;
	gS2_RX_MASK = 0x07FF;
	gS3_RX_BASE = 0x7800;
	gS3_RX_MASK = 0x07FF;

	gS0_TX_BASE = 0x4000;
	gS0_TX_MASK = 0x07FF;
	gS1_TX_BASE = 0x4800;
	gS1_TX_MASK = 0x07FF;
	gS2_TX_BASE = 0x5000;
	gS2_TX_MASK = 0x07FF;
	gS3_TX_BASE = 0x5800;
	gS3_TX_MASK = 0x07FF;

	S0_get_size = 0;
	S0_get_offset = 0;
	S0_RX_RD = 0;
	S0_get_start_address = 0;

	spi_no_debug=0;
}*/

// ****** End Socket Memory assignment ****** //



//uint16_t nr016bit = ByteToInt( S0_RX_SZ_ADDR_BASEHH, S0_RX_SZ_ADDR_BASEHL ); // #include "STR_Chelo.h"




uint8_t  SPI_ETH(struct  W5100_SPI * x )
{
	//x->TX[0]= x->operacion; //asigno lectura o escritura
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
			res|=SPI_ETH(x);
			x->TX[2]++;
			if (i==0)res<<8;
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
uint16_t SPI_ETH_WR_REG_16(struct W5100_SPI * x, uint16_t addr, uint8_t op, uint16_t  data)
{
 uint16_t res=0;
 uint8_t num[2];

 x->TX[0]= op; //asigno lectura o escritura

 num[1] = data & 0x00FF ;
 num[0] = (data & 0xFF00)>>8 ;

 if( op == SPI_WRITE)
 {
	 for(int i=0; i<(2); i++)
	 {
		x->TX[2]= addr & 0x00FF;
		x->TX[1]=(addr & 0xFF00)>>8;
		addr++;
		x->TX[3]=num[i];
		res=SPI_ETH(x);
	 }
	 return(res);
 }

}
uint16_t SPI_ETH_RD_REG_16(struct W5100_SPI * x, uint16_t addr, uint8_t op, uint8_t * data, uint16_t lnght )
{
	if(op == SPI_READ)
	 {

		for(int i=0; i<(lnght); i++)
			{
			x->TX[2] = addr & 0x00FF;
			x->TX[1] = (addr & 0xFF00)>>8;
			data[i]=SPI_ETH(x);
			addr++;
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


