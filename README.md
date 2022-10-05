# STM32_ETH_W5100
 Desarrollo de biblioteca para modulo WIZNET W5100 conectado por SPI.
## Configuracion del Micro 
El W5100 soporta comunicaciones SPI con un clock de hasta 14 MHZ, para este caso se setea un perscaler de 4 y se obtiene una freceuncia de clock de 9 MHz.
En pruebas realizadas a 18MHz se obervan errores en la lectura de datos.
`$ npm install marked`

![](doc/stm32_conf.PNG)
### Código 
```c
static void MX_SPI2_Init(void)
{

  /* USER CODE BEGIN SPI2_Init 0 */

  /* USER CODE END SPI2_Init 0 */

  /* USER CODE BEGIN SPI2_Init 1 */

  /* USER CODE END SPI2_Init 1 */
  /* SPI2 parameter configuration*/
  hspi2.Instance = SPI2;
  hspi2.Init.Mode = SPI_MODE_MASTER;
  hspi2.Init.Direction = SPI_DIRECTION_2LINES;
  hspi2.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi2.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi2.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi2.Init.NSS = SPI_NSS_SOFT;
  hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;
  hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi2.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI2_Init 2 */

  /* USER CODE END SPI2_Init 2 */

}
```
## Conexion con el dispositivo

![](doc/conexiones.PNG)

## Señales

![](doc/signals.PNG)
![](doc/write_read_op.PNG)
#TCP Server
## Flujo de trabajo 

![](doc/server_mode.PNG)

## Maquina de estados 
![](doc/state_machine.PNG)
### De la libreria de wiznet


```c
------------------------------------------------------------------------------------------------
/**
@brief  This function is an application I/F function which is used to receive the data in TCP mode.
    It continues to wait for data as much as the application wants to receive.

@return received data size for success else -1.
*/
uint16 recv(
  SOCKET s,   /**< socket index */
  uint8 * buf,  /**< a pointer to copy the data to be received */
  uint16 len  /**< the data size to be read */
  )
{
  uint16 ret=0;
#ifdef __DEF_IINCHIP_DBG__
  printf("recv()\r\n");
#endif


  if ( len > 0 )
  {
    recv_data_processing(s, buf, len);    ---->(1)	//LEO
    IINCHIP_WRITE(Sn_CR(s),Sn_CR_RECV);			//LE DIGO QUE RECIBÍ

    /* +20071122[chungs]:wait to process the command... */
    while( IINCHIP_READ(Sn_CR(s)) )   ------->(6)	//ESPERO
      ;
    /* ------- */
    ret = len;
  }
  return ret;
}
------------------------------------------------------------------------------------------------
(1)FUNCION PARA LEER LA DATA RECIBIDA COMPLETA
------------------------------------------------------------------------------------------------
void recv_data_processing(SOCKET s, uint8 *data, uint16 len)
{
	uint16 ptr;
	ptr = IINCHIP_READ(Sn_RX_RD0(s));
	ptr = ((ptr & 0x00ff) << 8) + IINCHIP_READ(Sn_RX_RD0(s) + 1);
#ifdef __DEF_IINCHIP_DBG__
	printf("ISR_RX: rd_ptr : %.4x\r\n", ptr);
#endif
	read_data(s, (uint8 *)ptr, data, len); --> (2) // read data
	ptr += len;  							    //Sn_RX_RD += get_size;
	IINCHIP_WRITE(Sn_RX_RD0(s),(uint8)((ptr & 0xff00) >> 8)); -->(7)	//
	IINCHIP_WRITE((Sn_RX_RD0(s) + 1),(uint8)(ptr & 0x00ff));
}
------------------------------------------------------------------------------------------------
(2) LEE TODA LA DATA DEL BUFFER
------------------------------------------------------------------------------------------------
void read_data(SOCKET s, vuint8 * src, vuint8 * dst, uint16 len)
{
	uint16 size;	//size = Sn_RX_RSR		
	uint16 src_mask;		
	uint8 * src_ptr;

	src_mask = (uint16)src & getIINCHIP_RxMASK(s);		//Sn_RX_MASK & Sn_RX_RD = src_mask = get_offset;
	src_ptr = (uint8 *)(getIINCHIP_RxBASE(s) + src_mask);   //=get_start_address
	
	if( (src_mask + len) > getIINCHIP_RxMAX(s) )            // 
	{
		size = getIINCHIP_RxMAX(s) - src_mask;		
		wiz_read_buf((uint16)src_ptr, (uint8*)dst,size); --->(3)
		dst += size;
		size = len - size;
		src_ptr = (uint8 *)(getIINCHIP_RxBASE(s));
		wiz_read_buf((uint16)src_ptr, (uint8*) dst,size);
	} 
	else
	{
		wiz_read_buf((uint16)src_ptr, (uint8*) dst,len);
	}
}
------------------------------------------------------------------------------------------------
(3) FUNCION PARA LEER BUFFER
------------------------------------------------------------------------------------------------
uint16 wiz_read_buf(uint16 addr, uint8* buf,uint16 len)
{
#if (__DEF_IINCHIP_BUS__ == __DEF_IINCHIP_DIRECT_MODE__)
	IINCHIP_ISR_DISABLE();
	memcpy(buf, (uint8 *)addr, len);
	IINCHIP_ISR_ENABLE();
#elif(__DEF_IINCHIP_BUS__ == __DEF_IINCHIP_INDIRECT_MODE__)
	   uint16 idx = 0;
	   IINCHIP_ISR_DISABLE();
	   *((vuint8*)IDM_AR0) = (uint8)((addr & 0xFF00) >> 8);
	   *((vuint8*)IDM_AR1) = (uint8)(addr & 0x00FF);
	   for (idx = 0; idx < len ; idx++) buf[idx] = *((vuint8*)IDM_DR);
	   IINCHIP_ISR_ENABLE();
#elif (__DEF_IINCHIP_BUS__ == __DEF_IINCHIP_SPI_MODE__)
	uint16 idx = 0;
	   IINCHIP_ISR_DISABLE();

	IINCHIP_SpiInit();
   
	for (idx=0; idx<len; idx++)
      	   {
		IINCHIP_CSoff();                             // CS=0, SPI start 

		IINCHIP_SpiSendData(0x0F); -->(8)
		IINCHIP_SpiSendData(((addr+idx) & 0xFF00) >> 8);
		IINCHIP_SpiSendData((addr+idx) & 0x00FF);


		IINCHIP_SpiSendData(0);
		buf[idx] = IINCHIP_SpiRecvData();

		IINCHIP_CSon();                             // CS=0, SPI end 	   
	   }

	   IINCHIP_ISR_ENABLE();
#else
	#error "unknown bus type"
#endif
	return len;
}
------------------------------------------------------------------------------------------------
ESPERA A QUE TERMINE LE COMANDO
------------------------------------------------------------------------------------------------
// JAJA ESPERAR A QUE TERMINE Y ESTO?
			
		recv_data_processing(0, str, len);
		IINCHIP_WRITE(Sn_CR(0),Sn_CR_RECV);
		/* +20071122[chungs]:wait to process the command... */
		while( IINCHIP_READ(Sn_CR(0)) ) // Se queda esperando el 0 finalizando la función
------------------------------------------------------------------------------------------------
(6) LECTURA
------------------------------------------------------------------------------------------------
uint8 IINCHIP_READ(uint16 addr)
{
	uint8 data;

// DIRECT MODE I/F

#if (__DEF_IINCHIP_BUS__ == __DEF_IINCHIP_DIRECT_MODE__)
	IINCHIP_ISR_DISABLE();
	data = *((vuint8*)(addr));
	IINCHIP_ISR_ENABLE();
#elif(__DEF_IINCHIP_BUS__ == __DEF_IINCHIP_INDIRECT_MODE__)   
	   IINCHIP_ISR_DISABLE();
	   *((vuint8*)IDM_AR0) = (uint8)((addr & 0xFF00) >> 8);
	   *((vuint8*)IDM_AR1) = (uint8)(addr & 0x00FF);
	   data = *((vuint8*)IDM_DR);
	   IINCHIP_ISR_ENABLE();
   
#elif (__DEF_IINCHIP_BUS__ == __DEF_IINCHIP_SPI_MODE__)
	   IINCHIP_ISR_DISABLE();
	IINCHIP_SpiInit();	
	IINCHIP_CSoff();                             // CS=0, SPI start

	IINCHIP_SpiSendData(0x0F);		     //Manda el READ
	IINCHIP_SpiSendData((addr & 0xFF00) >> 8);   //Manda la primera address
	IINCHIP_SpiSendData(addr & 0x00FF);	     //Manda la segunda address
	
	
	IINCHIP_SpiSendData(0);			     //Manda el tercer dato nulo.
	data = IINCHIP_SpiRecvData();

	IINCHIP_CSon();                          	// SPI end
	   IINCHIP_ISR_ENABLE();
#else
	#error "unknown bus type"
#endif
	return data;
}				
------------------------------------------------------------------------------------------------
(7) - Escritura
------------------------------------------------------------------------------------------------
@brief	This function writes the data into W5100 registers.
*/
uint8 IINCHIP_WRITE(uint16 addr,uint8 data)
{
// DIRECT MODE I/F
#if (__DEF_IINCHIP_BUS__ == __DEF_IINCHIP_DIRECT_MODE__)
	IINCHIP_ISR_DISABLE();
	*((vuint8*)(addr)) = data;
	IINCHIP_ISR_ENABLE();
#elif(__DEF_IINCHIP_BUS__ == __DEF_IINCHIP_INDIRECT_MODE__)	/* INDIRECT MODE I/F */
	   IINCHIP_ISR_DISABLE();
	   *((vuint8*)IDM_AR0) = (uint8)((addr & 0xFF00) >> 8);
	   *((vuint8*)IDM_AR1) = (uint8)(addr & 0x00FF);
	   *((vuint8*)IDM_DR)  = data;
	   IINCHIP_ISR_ENABLE();
#elif (__DEF_IINCHIP_BUS__ == __DEF_IINCHIP_SPI_MODE__)
	   IINCHIP_ISR_DISABLE();
	IINCHIP_SpiInit();
	
	//SPI MODE I/F
	IINCHIP_CSoff();                             // CS=0, SPI start

	IINCHIP_SpiSendData(0xF0);
	IINCHIP_SpiSendData((addr & 0xFF00) >> 8);
	IINCHIP_SpiSendData(addr & 0x00FF);
	IINCHIP_SpiSendData(data);

	IINCHIP_CSon();    

	   IINCHIP_ISR_ENABLE();   
#else
	#error "unknown bus type"
#endif
	return 1;
}
------------------------------------------------------------------------------------------------
(8) - Defs
------------------------------------------------------------------------------------------------
#define IINCHIP_SpiInit					SPI0_Init
#define IINCHIP_SpiSendData				SPI0_SendByte	
#define IINCHIP_SpiRecvData				SPI0_RxData

05/10/22 Si el socket permanece en cero mas de 5 segundos luego de iniciar la comunicacon, ejecuto el reinicio, dado que al estar desconectado el cable el socket igual pasa al valor 1 para enviar el mensaje de arp y así luego establecer la conexión.
