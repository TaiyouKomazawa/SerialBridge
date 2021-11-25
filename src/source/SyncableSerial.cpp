/**
* @file SyncableSerial.cpp
* @brief Serial communication library for Synchronous serial.
* @author Taiyou Komazawa
* @date 2021/11/25
*/

#include "../SyncableSerial.hpp"

SyncableSerial::SyncableSerial(SyncSerialDev *dev)
:	_dev(dev),
	_rx_buffer(new uint8_t(dev->size())),
	_tx_buffer(new uint8_t(dev->size()))
{
    _data_updated = true;
}

SyncableSerial::~SyncableSerial()
{
    delete [] _rx_buffer;
    delete [] _tx_buffer;
}

int SyncableSerial::read(uint8_t *data)
{
    memcpy(data,(_rx_buffer+1),_rx_buffer[0]);
    _data_updated = false;
    return _rx_buffer[0];
}

int SyncableSerial::write(uint8_t *data, const unsigned int len)
{
    if(_dev->size() >= len+1){
        _tx_buffer[0] = (uint8_t)len;
        memcpy((_tx_buffer+1),data,len);
        _data_updated = false;
        return len+1;
    }
    return 0;
}

void SyncableSerial::update()
{
    if(!_data_updated){
        _dev->update(_rx_buffer, _tx_buffer);
        _data_updated = true;
    }
}
