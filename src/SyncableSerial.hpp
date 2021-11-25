/**
* @file SyncableSerial.hpp
* @brief Serial communication library for Synchronous serial.
* @author Taiyou Komazawa
* @date 2021/11/25
*/

#ifndef _SYNCABLE_SERIAL_HPP_
#define _SYNCABLE_SERIAL_HPP_

#include <stdint.h>
#include <string.h>

#include "SyncSerialDev.hpp"
#include "SerialInterface.hpp"

/**
* @brief Serial communication class for Synchronous serial.
*/
class SyncableSerial : public SerialInterface
{
public:

    SyncableSerial(SyncSerialDev *dev);
    virtual ~SyncableSerial();

    virtual int read(uint8_t *data);

    virtual int write(uint8_t *data, const unsigned int len);

    virtual void update();

private:
    SyncSerialDev *_dev;
    uint8_t *_rx_buffer, *_tx_buffer;
    bool _data_updated;
};

#endif //#ifndef _SYNCABLE_SERIAL_HPP_
