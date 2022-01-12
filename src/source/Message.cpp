/**
* @file Message.cpp
* @brief The data format handled by SerialBridge is defined here.
* @author Taiyou Komazawa
* @date 2021/8/18
*/

#include "../Message.hpp"

/**
* @brief Stores the data structure in a packet.
* This function is used internally by SerialBridge when sending.
* @param[in] id Message ID assigned when sending.
* @param[out] send_packet Array pointer to put the data after packing.
* @param [out] data_size Integer pointer to the length of data to pack.
* @return None
*/
void sb::MessageInterface::packing(uint8_t id, uint8_t *send_packet, int *data_size)
{
    int size = _pk_size();
    uint32_t sum = 0;

    *data_size = size;
    send_packet[0] = id;
    memcpy(send_packet+1, _pk_data_ptr(), size-CTRL_DATA_LEN);
    for (int i = 0; i < size - 1; i++)
    {
        sum += send_packet[i];
    }
    send_packet[size-1] = (uint8_t)(sum & 0xFF);
}

/**
* @brief Extract the data structure from the packet.
* This function is used internally by SerialBridge on reception.
* @param[in] received_packet Array pointer to unpack.
* @return None
*/
void sb::MessageInterface::unpacking(uint8_t *received_packet)
{
    int size = _upk_size();

    memcpy(_upk_data_ptr(), received_packet+1, size-CTRL_DATA_LEN);
    _unpacked = true;
}
