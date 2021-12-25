/**
* @file MCP2210Linux.hpp
* @brief Define the class required for SPI communication using SerialBridge in MCP2210 with linux environment.
* @author Taiyou Komazawa
* @date 2021/11/26
*/

#ifdef __linux__

#ifndef _MCP2210_LINUX_HPP_
#define _MCP2210_LINUX_HPP_

#include <stdlib.h>
#include <stdint.h>
#include <wchar.h>

#include "../MCP2210-Library/hidapi.h"
#include "../MCP2210-Library/mcp2210.h"
#include "SyncSerialDev.hpp"

class MCP2210Linux : public SyncSerialDev
{
public:
    typedef enum ChipSelectorPinType
    {
        GP0 = 0, GP1, GP2, GP3, GP4, GP5, GP6, GP7, GP8,
    }cs_pin_t;


    MCP2210Linux(wchar_t* serial_number, cs_pin_t active_cs, 
                    int spi_mode = SPI_MODE, 
                    int spi_speed = SPI_SPEED,
                    uint8_t buffer_size = DEFAULRT_BUFFER_SIZE);
    virtual ~MCP2210Linux();

    virtual int update(unsigned char *rx_data, unsigned char *tx_data);

    virtual unsigned int size();

    enum{
        SPI_MODE = 3,
        SPI_SPEED = 8000000, //bps
    	DEFAULRT_BUFFER_SIZE = 32,
    };

private:
    static bool _is_opened;

    uint8_t _buffer_size;

    hid_device *_handle;
};

#endif //#ifndef _MCP2210_LINUX_HPP_

#endif //#ifdef __linux__
