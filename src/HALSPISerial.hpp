/**
* @file HALSPISerial.hpp
* @brief Define the class required for SPI communication using SerialBridge in STM32 HAL environment.
* @author Taiyou Komazawa
* @date 2021/11/25
*/

#ifdef __arm__

#include <stdint.h>
#include <main.h>

#include "SyncSerialDev.hpp"

class HALSPISerial : public SyncSerialDev
{
public:
    HALSPISerial(SPI_HandleTypeDef *pspi, uint8_t buffer_size = DEFAULRT_BUFFER_SIZE);

    virtual int update(unsigned char *rx_data, unsigned char *tx_data);

    virtual unsigned int size();

    enum{
    	DEFAULRT_BUFFER_SIZE = 32,
    };

private:
    SPI_HandleTypeDef *_pspi;

    uint8_t _buffer_size;
};

#endif //#ifdef __arm__
