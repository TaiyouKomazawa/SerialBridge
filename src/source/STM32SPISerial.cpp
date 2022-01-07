/**
* @file STM32SPISerial.cpp
* @brief Define the class required for SPI communication using SerialBridge in STM32 environment.
* @author Taiyou Komazawa
* @date 2021/11/25
*/

#ifdef __arm__

#include "../STM32SPISerial.hpp"

STM32SPISerial::STM32SPISerial(SPI_HandleTypeDef  *hspix, uint8_t buffer_size)
:   _hspix(hspix), _buffer_size(buffer_size)
{
	__HAL_SPI_ENABLE(_hspix);
}

/**
* @brief Update data synchronization.
* @param[out] rx_data Data received.
* @param[in]  tx_data Data to send. 
* @return int Synchronous state.
* @retval 0 : No error.
*/
int STM32SPISerial::update(unsigned char *rx_data, unsigned char *tx_data)
{
	return HAL_SPI_TransmitReceive_DMA(_hspix,
											(uint8_t *)tx_data,
											(uint8_t *)rx_data,
											_buffer_size);
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
