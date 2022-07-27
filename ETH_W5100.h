/*
 * ETH_W5100.h
 *
 *  Created on: 18 jul. 2022
 *      Author: mggarcia
 */

//#ifndef ETH_W5100_H_
//#define ETH_W5100_H_
#include "main.h"


// Begin Socket COMMANDS Sn_CR
enum
{
 OPEN 			=	0x01,
 LISTEN 		=	0x02,
 CONNECT 		=	0x04,
 DISCON  		=	0x08,
 CLOSE 			=	0x10,
 SEND 			=	0x20,
 SEND_MAC		=	0x21,
 SEND_KEEP  	=	0x22,
 RECV 			=	0x40
};
// end Socket COMMANDS Sn_CR

// Begin Socket STATUS Sn_SR
enum
{
 SOCK_CLOSED 		=	0x00,
 SOCK_ARP   	 	=	0x01,
 SOCK_INIT			=	0x13,
 SOCK_LISTEN		=	0x14,
 SOCK_SYNSENT 		=	0x15,
 SOCK_SYNRECV		=	0x16,
 SOCK_ESTABLISHED	=	0x17,
 SOCK_FIN_WAIT		=	0x18,
 SOCK_CLOSING  		=	0x1A,
 SOCK_TIME_WAIT		=	0x1B,
 SOCK_CLOSE_WAIT	=	0x1C,
 SOCK_LAST_ACK		=	0x1D,
 SOCK_UDP			=	0x22,
 SOCK_IPRAW			=	0x32,
 SOCK_MACRAW		=	0x42,
 SOCK_PPOE			=	0x5F,
};
// End Socket STATUS Sn_SR
// Begin Registers Address
enum
{
 GAR_ADDR_BASEH 		=	0x00,
 GAR_ADDR_BASEL   	 	=	0x01,
 SUBR_ADDR_BASEH 		=	0x00,
 SUBR_ADDR_BASEL   	 	=	0x05,
 SHAR_ADDR_BASEH 		=	0x00,
 SHAR_ADDR_BASEL   	 	=	0x09,
 SIPR_ADDR_BASEH 		=	0x00,
 SIPR_ADDR_BASEL   	 	=	0x0F,

 S0_MR_ADDR_BASEH 		=	0x04,
 S0_MR_ADDR_BASEL   	=	0x00,

 S0_CR_ADDR_BASEH 		=	0x04,
 S0_CR_ADDR_BASEL   	=	0x01,

 S0_IR_ADDR_BASEH 		=	0x04,
 S0_IR_ADDR_BASEL   	=	0x02,

 S0_SR_ADDR_BASEH 		=	0x04,
 S0_SR_ADDR_BASEL   	=	0x03,

 S0_PORT_ADDR_BASEH 	=	0x04,
 S0_PORT_ADDR_BASEL   	=	0x04,
};
// Begin Socket SPI
enum
{
 SPI_WRITE			=	0xF0,
 SPI_READ   	 	=	0x0F,
};

struct W5100_SPI
{
	SPI_HandleTypeDef *SPI;
	GPIO_TypeDef  *PORT;
	uint16_t PIN;
	uint8_t operacion;
	char TX[4];
	char RX[4];
};

// End Socket SPI
/****************************************************************************
 * Función para el comunicación SPI.
 ****************************************************************************/

uint8_t SPI_ETH(struct W5100_SPI *);
uint8_t SPI_ETH_REG(struct W5100_SPI *, uint8_t ,uint8_t ,uint8_t , uint8_t * , uint8_t );
uint8_t SPI_ETH_PORT_CMD(struct W5100_SPI *, uint8_t);

//#endif /* ETH_W5100_H_ */
