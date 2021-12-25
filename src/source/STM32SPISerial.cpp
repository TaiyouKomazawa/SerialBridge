/**
* @file STM32SPISerial.cpp
* @brief Define the class required for SPI communication using SerialBridge in STM32 environment.
* @author Taiyou Komazawa
* @date 2021/11/25
*/

#ifdef __arm__

#include "../STM32SPISerial.hpp"

STM32SPISerial::STM32SPISerial(SPI_TypeDef *SPIx, uint8_t buffer_size)
:   _SPIx(SPIx), _buffer_size(buffer_size)
{}

/**
* @brief Update data synchronization.
* @param[out] rx_data Data received.
* @param[in]  tx_data Data to send. 
* @return int Synchronous state.
* @retval 0 : No error.
*/
int STM32SPISerial::update(unsigned char *rx_data, unsigned char *tx_data)
{
	int16_t count = _buffer_size;
	while (count > 0) {
		while (LL_SPI_IsActiveFlag_TXE(_SPIx) == RESET);
		LL_SPI_TransmitData8(_SPIx, (uint8_t)*tx_data++);
		while (LL_SPI_IsActiveFlag_RXNE(_SPIx) == RESET);
		*rx_data++ = (uint8_t)LL_SPI_ReceiveData8(_SPIx);
		count--;
	}

    return 0;
}

/**
* @brief Returns the size of rxtx buffer.  
* @return unsigned int 
*/
unsigned int STM32SPISerial::size()
{
    return _buffer_size;
}

#endif //#ifdef __arm__
