/**
* @file MCP2210Linux.hpp
* @brief Define the class required for SPI communication using SerialBridge in MCP2210 with linux environment.
* @author Taiyou Komazawa
* @date 2021/11/26
*/

#ifdef __linux__

#ifndef _MCP2210_LINUX_HPP_
#define _MCP2210_LINUX_HPP_

#include <stdint.h>

#include "SyncSerialDev.hpp"

#include "mcp2210_api.h"

class MCP2210Linux : public SyncSerialDev
{
public:
    typedef enum ChipSelectorPinType
    {
        GP0 = 0, GP1, GP2, GP3, GP4, GP5, GP6, GP7, GP8,
    }cs_pin_t;


    MCP2210Linux(const char *device, cs_pin_t active_cs, 
                    int spi_mode = SPI_MODE, 
                    int spi_speed = SPI_SPEED,
                    uint8_t buffer_size = DEFAULRT_BUFFER_SIZE);
    virtual ~MCP2210Linux();

    virtual int update(unsigned char *rx_data, unsigned char *tx_data);

    virtual unsigned int size();

    enum{
        SPI_MODE = 0,
        SPI_SPEED = 5000000, //bps
    	DEFAULRT_BUFFER_SIZE = 32,
    };

private:
    static int _fd;
    cs_pin_t _active_cs;
    int _spi_mode, _spi_speed;

    uint8_t _buffer_size;
};

#endif //#ifndef _MCP2210_LINUX_HPP_

#endif //#ifdef __linux__
