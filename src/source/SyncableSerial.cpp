/**
* @file SyncableSerial.cpp
* @brief Serial communication library for Synchronous serial.
* @author Taiyou Komazawa
* @date 2021/11/25
*/

#include "../SyncableSerial.hpp"

SyncableSerial::SyncableSerial(SyncSerialDev *dev)
:	_dev(dev)
{
    const int size = _dev->size();
    _rx_buffer = new uint8_t[size];
	_tx_buffer = new uint8_t[size];
    memset(_tx_buffer, 0, size);
	memset(_rx_buffer, 0, size);
}

SyncableSerial::~SyncableSerial()
{
    delete [] _rx_buffer;
    delete [] _tx_buffer;
}

int SyncableSerial::read(uint8_t *data)
{
    unsigned int len = _rx_buffer[0];
    if(0 < len && len <= _dev->size()){
        memcpy(data,(_rx_buffer+1),len);
        return len+1;
    }
    return 0;
}

int SyncableSerial::write(uint8_t *data, const unsigned int len)
{
    if(_dev->size() >= len+1){
        _tx_buffer[0] = (uint8_t)len;
        memcpy((_tx_buffer+1),data,len);
        return len+1;
    }
    return 0;
}

int SyncableSerial::update()
{
	int state = -1;
    state = _dev->update(_rx_buffer, _tx_buffer);
    return state;
}
