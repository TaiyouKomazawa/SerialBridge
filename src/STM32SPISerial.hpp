/**
* @file STM32SPISerial.hpp
* @brief Define the class required for SPI communication using SerialBridge in STM32 environment.
* @author Taiyou Komazawa
* @date 2021/11/25
*/

#ifdef __arm__

#ifndef _STM32_SPI_SERIAL_HPP_
#define _STM32_SPI_SERIAL_HPP_

#include <stdint.h>
#include <main.h>

#include "SyncSerialDev.hpp"

class STM32SPISerial : public SyncSerialDev
{
public:
	STM32SPISerial(SPI_HandleTypeDef  *hspix, uint8_t buffer_size = DEFAULRT_BUFFER_SIZE);

    virtual int update(unsigned char *rx_data, unsigned char *tx_data);

    virtual unsigned int size();

    enum{
    	DEFAULRT_BUFFER_SIZE = 32,
    };

private:
    SPI_HandleTypeDef  *_hspix;

    uint8_t _buffer_size;
};

#endif //#ifndef _STM32_SPI_SERIAL_HPP_

#endif //#ifdef __arm__
