/**
* @file HALSPISerial.cpp
* @brief Define the class required for SPI communication using SerialBridge in STM32 HAL environment.
* @author Taiyou Komazawa
* @date 2021/11/25
*/

#ifdef __arm__

#include "../HALSPISerial.hpp"

HALSPISerial::HALSPISerial(SPI_HandleTypeDef *pspi, uint8_t buffer_size)
:   _pspi(pspi), _buffer_size(buffer_size)
{}

/**
* @brief Update data synchronization.
* @param[out] rx_data Data received.
* @param[in]  tx_data Data to send. 
* @return int Synchronous state.
* @retval 0 : No error.
*/
int HALSPISerial::update(unsigned char *rx_data, unsigned char *tx_data)
{
    return HAL_SPI_TransmitReceive_DMA(_pspi, (uint8_t*)tx_data, (uint8_t*)rx_data, _buffer_size);
}

/**
* @brief Returns the size of rxtx buffer.  
* @return unsigned int 
*/
unsigned int HALSPISerial::size()
{
    return _buffer_size;
}

#endif //#ifdef __arm__
