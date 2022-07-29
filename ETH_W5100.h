/*
 * ETH_W5100.h
 *
 *  Created on: 18 jul. 2022
 *      Author: mggarcia
 */

//#ifndef ETH_W5100_H_
//#define ETH_W5100_H_
#include "main.h"

// ****** Begin COMMON Registers Address ****** //
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
 IR_ADDR_BASEH 		    =	0x00,
 IR_ADDR_BASEL   	 	=	0x15,
 IMR_ADDR_BASEH 		=	0x00,
 IMR_ADDR_BASEL   	 	=	0x16,
 RMSR_ADDR_BASEH 		=	0x00,
 RMSR_ADDR_BASEL   	 	=	0x1A,
 TMSR_ADDR_BASEH 		=	0x00,
 TMSR_ADDR_BASEL   	 	=	0x1B,
};
// ****** End COMMON Registers Address ****** //

// ****** Begin SOCKET0 Registers Address ****** //
enum
{
 S0_MR_ADDR_BASEH 		=	0x04,
 S0_MR_ADDR_BASEL   	=	0x00,
 S0_CR_ADDR_BASEH 		=	0x04,
 S0_CR_ADDR_BASEL   	=	0x01,
 S0_IR_ADDR_BASEH 		=	0x04,
 S0_IR_ADDR_BASEL   	=	0x02,
 S0_SR_ADDR_BASEH 		=	0x04,
 S0_SR_ADDR_BASEL   	=	0x03,
 S0_PORT_ADDR_BASEHH 	=	0x04,
 S0_PORT_ADDR_BASEHL   	=	0x05,
 S0_PORT_ADDR_BASELH 	=	0x04,
 S0_PORT_ADDR_BASELL  	=	0x04,

 S0_RX_SZ_ADDR_BASEHH 	=	0x04,
 S0_RX_SZ_ADDR_BASEHL  	=	0x26,
 S0_RX_SZ_ADDR_BASELH 	=	0x04,
 S0_RX_SZ_ADDR_BASELL  	=	0x27,

 S0_RX_RD_ADDR_BASEHH 	=	0x04, //S0_RX_RD0H
 S0_RX_RD_ADDR_BASEHL  	=	0x28, //S0_RX_RD0L
 S0_RX_RD_ADDR_BASELH 	=	0x04, //S0_RX_RD1H
 S0_RX_RD_ADDR_BASELL  	=	0x29, //S0_RX_RD1L
 S0_RX_RD0              =   0x0428
};
// ****** End SOCKET0  Registers Address ****** //

// ****** Begin Socket COMMANDS Sn_CR ****** //
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

// ****** end Socket COMMANDS Sn_CR ****** //

// ****** Begin Socket STATUS Sn_SR ****** //
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
// ****** End Socket STATUS Sn_SR ****** //

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
	char data[254];
};


// End Socket SPI
/****************************************************************************
 * Función para el comunicación SPI.
 ****************************************************************************/
void setVar_ETH(void);
uint8_t SPI_ETH(struct W5100_SPI *);
uint16_t SPI_ETH_REG(struct W5100_SPI *, uint8_t ,uint8_t ,uint8_t , uint8_t * , uint8_t );
uint16_t SPI_ETH_WR_REG_16(struct W5100_SPI * , uint16_t , uint8_t , uint16_t );
uint16_t SPI_ETH_RD_REG_16(struct W5100_SPI * , uint16_t , uint8_t , uint8_t * , uint16_t);
uint8_t SPI_ETH_PORT_CMD(struct W5100_SPI *, uint8_t);

//#endif /* ETH_W5100_H_ */
