/**
* @file MCP2210Linux.cpp
* @brief Define the class required for SPI communication using SerialBridge in MCP2210 with linux environment.
* @author Taiyou Komazawa
* @date 2021/11/26
*/

#ifdef __linux__

#include "../MCP2210Linux.hpp"

MCP2210Linux::MCP2210Linux(const char *device, MCP2210Linux::cs_pin_t active_cs, int spi_mode, int spi_speed, uint8_t buffer_size)
:   _active_cs(active_cs),
    _spi_mode(spi_mode),
    _spi_speed(spi_speed),
    _buffer_size(buffer_size)
{
    if(_fd == -1)
        _fd = open_device(device);
}

MCP2210Linux::~MCP2210Linux()
{
    close_device(_fd);
}

int MCP2210Linux::update(unsigned char *rx_data, unsigned char *tx_data)
{
    const int actcsval = ~(1 << (int)_active_cs);
    const int idlecsval = 511;
    const int gpcsmask = 511;
    return spi_data_xfer(_fd, (unsigned char *)tx_data,(unsigned char *)rx_data, _buffer_size,
				    _spi_mode, _spi_speed, actcsval, idlecsval, gpcsmask,0,0,0);
}

unsigned int MCP2210Linux::size()
{
    return _buffer_size;
}

#endif //#ifdef __linux__
