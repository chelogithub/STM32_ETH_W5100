/*
 * ETH_W5100.c
 *
 *  Created on: 18 jul. 2022
 *      Author: mggarcia
 */

enum{

	OPEN,
	LISTENING,

};

/*
 ITM0_Write("\r\n SET-UP W5100 \r\n",strlen("\r\n SET-UP W5100 \r\n"));
  //HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_RESET);
     spi_addr[0]= 0xF0;
	 spi_addr[1]= 0;
	 spi_addr[2]= 1;
	 spi_addr[3]= 192;
	  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, 0);
	  HAL_SPI_TransmitReceive(&hspi2, (uint8_t *)spi_addr, (uint8_t *)spi_buf, 4, 100);
	  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, 1);
 ITM0_Write("\r\n SPI WRITE 0x0001 GAR0 192\r\n",strlen("\r\n SPI WRITE 0x0001 GAR0 192\r\n"));
	  spi_addr[2]= 2;
	  spi_addr[3]= 168;
	  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, 0);
	  HAL_SPI_TransmitReceive(&hspi2, (uint8_t *)spi_addr, (uint8_t *)spi_buf, 4, 100);
	  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, 1);
ITM0_Write("\r\n SPI WRITE 0x0002 GAR1 168\r\n",strlen("\r\n SPI WRITE 0x0002 GAR0 168\r\n"));
	  spi_addr[2]= 3;
	  spi_addr[3]= 0;
	  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, 0);
	  HAL_SPI_TransmitReceive(&hspi2, (uint8_t *)spi_addr, (uint8_t *)spi_buf, 4, 100);
	  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, 1);
ITM0_Write("\r\n SPI WRITE 0x0003 GAR2 0\r\n",strlen("\r\n SPI WRITE 0x0003 GAR0 0\r\n"));
	  spi_addr[2]= 4;
	  spi_addr[3]= 1;
	  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, 0);
	  HAL_SPI_TransmitReceive(&hspi2, (uint8_t *)spi_addr, (uint8_t *)spi_buf, 4, 100);
	  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, 1);
ITM0_Write("\r\n SPI WRITE 0x0004 GAR3 1\r\n",strlen("\r\n SPI WRITE 0x0004 GAR0 1\r\n"));

	spi_addr[2]= 5;
	spi_addr[3]= 255;
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, 0);
	HAL_SPI_TransmitReceive(&hspi2, (uint8_t *)spi_addr, (uint8_t *)spi_buf, 4, 100);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, 1);
ITM0_Write("\r\n SPI WRITE SUBR0 255\r\n",strlen("\r\n SPI WRITE SUBR 255\r\n"));
	spi_addr[2]= 6;
	spi_addr[3]= 255;
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, 0);
	HAL_SPI_TransmitReceive(&hspi2, (uint8_t *)spi_addr, (uint8_t *)spi_buf, 4, 100);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, 1);
ITM0_Write("\r\n SPI WRITE SUBR1 255\r\n",strlen("\r\n SPI WRITE SUBR 255\r\n"));
	spi_addr[2]= 7;
	spi_addr[3]= 255;
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, 0);
	HAL_SPI_TransmitReceive(&hspi2, (uint8_t *)spi_addr, (uint8_t *)spi_buf, 4, 100);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, 1);
ITM0_Write("\r\n SPI WRITE SUBR2 255\r\n",strlen("\r\n SPI WRITE SUBR 255\r\n"));
	spi_addr[2]= 8;
	spi_addr[3]= 0;
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, 0);
	HAL_SPI_TransmitReceive(&hspi2, (uint8_t *)spi_addr, (uint8_t *)spi_buf, 4, 100);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, 1);
ITM0_Write("\r\n SPI WRITE SUBR3 0\r\n",strlen("\r\n SPI WRITE SUBR 0\r\n"));

	spi_addr[2]= 9;
	spi_addr[3]= 0x00;
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, 0);
	HAL_SPI_TransmitReceive(&hspi2, (uint8_t *)spi_addr, (uint8_t *)spi_buf, 4, 100);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, 1);
ITM0_Write("\r\n SPI WRITE SHAR0 0\r\n",strlen("\r\n SPI WRITE SHAR0 0\r\n"));
	spi_addr[2]= 10;
	spi_addr[3]= 0x08;
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, 0);
	HAL_SPI_TransmitReceive(&hspi2, (uint8_t *)spi_addr, (uint8_t *)spi_buf, 4, 100);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, 1);
ITM0_Write("\r\n SPI WRITE SHAR1 0\r\n",strlen("\r\n SPI WRITE SHAR1 0\r\n"));
	spi_addr[2]= 11;
	spi_addr[3]= 0xDC;
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, 0);
	HAL_SPI_TransmitReceive(&hspi2, (uint8_t *)spi_addr, (uint8_t *)spi_buf, 4, 100);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, 1);
ITM0_Write("\r\n SPI WRITE SHAR2 0\r\n",strlen("\r\n SPI WRITE SHAR2 0\r\n"));
	spi_addr[2]= 12;
	spi_addr[3]= 0x00;
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, 0);
	HAL_SPI_TransmitReceive(&hspi2, (uint8_t *)spi_addr, (uint8_t *)spi_buf, 4, 100);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, 1);
ITM0_Write("\r\n SPI WRITE SHAR3 0\r\n",strlen("\r\n SPI WRITE SHAR3 0\r\n"));
	spi_addr[2]= 13;
	spi_addr[3]= 0x00;
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, 0);
	HAL_SPI_TransmitReceive(&hspi2, (uint8_t *)spi_addr, (uint8_t *)spi_buf, 4, 100);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, 1);
ITM0_Write("\r\n SPI WRITE SHAR4 0\r\n",strlen("\r\n SPI WRITE SHAR4 0\r\n"));
	spi_addr[2]= 14;
	spi_addr[3]= 0x01;
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, 0);
	HAL_SPI_TransmitReceive(&hspi2, (uint8_t *)spi_addr, (uint8_t *)spi_buf, 4, 100);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, 1);
ITM0_Write("\r\n SPI WRITE SHAR5 0\r\n",strlen("\r\n SPI WRITE SHAR5 0\r\n"));


	spi_addr[2]= 15;
	spi_addr[3]= 192;
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, 0);
	HAL_SPI_TransmitReceive(&hspi2, (uint8_t *)spi_addr, (uint8_t *)spi_buf, 4, 100);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, 1);
ITM0_Write("\r\n SPI WRITE SIPR0 192\r\n",strlen("\r\n SPI WRITE SIPR0 192\r\n"));
	spi_addr[2]= 16;
	spi_addr[3]= 168;
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, 0);
	HAL_SPI_TransmitReceive(&hspi2, (uint8_t *)spi_addr, (uint8_t *)spi_buf, 4, 100);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, 1);
ITM0_Write("\r\n SPI WRITE SIPR1 168\r\n",strlen("\r\n SPI WRITE SIPR1 168\r\n"));
	spi_addr[2]= 17;
	spi_addr[3]= 0;
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, 0);
	HAL_SPI_TransmitReceive(&hspi2, (uint8_t *)spi_addr, (uint8_t *)spi_buf, 4, 100);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, 1);
ITM0_Write("\r\n SPI WRITE SIPR2 0\r\n",strlen("\r\n SPI WRITE SIPR2 0\r\n"));
	spi_addr[2]= 18;
	spi_addr[3]= 3;
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, 0);
	HAL_SPI_TransmitReceive(&hspi2, (uint8_t *)spi_addr, (uint8_t *)spi_buf, 4, 100);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, 1);
ITM0_Write("\r\n SPI WRITE SIPR3 3\r\n",strlen("\r\n SPI WRITE SIPR3 3\r\n"));

	spi_addr[1]= 0x04;
	spi_addr[2]= 0x00;
	spi_addr[3]= 0x01;
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, 0);
	HAL_SPI_TransmitReceive(&hspi2, (uint8_t *)spi_addr, (uint8_t *)spi_buf, 4, 100);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, 1);
ITM0_Write("\r\n SPI WRITE SOMR\r\n",strlen("\r\n SPI WRITE SOMR\r\n"));
	spi_addr[2]= 0x04;
	spi_addr[3]= 0x01;
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, 0);
	HAL_SPI_TransmitReceive(&hspi2, (uint8_t *)spi_addr, (uint8_t *)spi_buf, 4, 100);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, 1);
ITM0_Write("\r\n SPI WRITE SOPORT0\r\n",strlen("\r\n SPI WRITE SOPORT0\r\n"));
	spi_addr[2]= 0x05;
	spi_addr[3]= 0xF6;
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, 0);
	HAL_SPI_TransmitReceive(&hspi2, (uint8_t *)spi_addr, (uint8_t *)spi_buf, 4, 100);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, 1);
ITM0_Write("\r\n SPI WRITE SOPORT1\r\n",strlen("\r\n SPI WRITE SOPORT1\r\n"));
	spi_addr[2]= 0x01;
	spi_addr[3]= 0x01;
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, 0);
	HAL_SPI_TransmitReceive(&hspi2, (uint8_t *)spi_addr, (uint8_t *)spi_buf, 4, 100);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, 1);
ITM0_Write("\r\n SPI WRITE SOCR\r\n",strlen("\r\n SPI WRITE SOCR\r\n"));
	spi_addr[2]= 0x01;
	spi_addr[3]= 0x02;
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, 0);
	HAL_SPI_TransmitReceive(&hspi2, (uint8_t *)spi_addr, (uint8_t *)spi_buf, 4, 100);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, 1);
ITM0_Write("\r\n SPI WRITE SOCR\r\n",strlen("\r\n SPI WRITE SOCR\r\n"));



SPI_READ_EN=1;
spi_addr[0]= 0x0F;
spi_addr[1]= 0;
spi_addr[2]= 1;
spi_addr[3]= 0;

////////// PARA EL READ   ///////////////
 *
 * 	  if(SPI_READ_EN)
	  {
	      ITM0_Write("\r\n SPI WRITE FOR READ \r\n",strlen("\r\n SPI WRITE FOR READ \r\n"));
		  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, 0);
		  HAL_SPI_TransmitReceive(&hspi2, (uint8_t *)spi_addr, (uint8_t *)spi_buf, spi_addr[19], 100);
		  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, 1);
		  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, 0);
		  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, 1);
	  }

*/

