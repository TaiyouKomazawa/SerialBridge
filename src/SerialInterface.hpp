/**
* @file SerialInterface.hpp
* @brief Serial communication library using "Consistent Overhead Byte Stuffing".
* @author Taiyou Komazawa
* @date 2021/11/25
*/

#ifndef _SERIAL_INTERFACE_HPP_
#define _SERIAL_INTERFACE_HPP_

/**
* @brief Serial communication interface for SerialBridge class.
*/
class SerialInterface
{
public:
    virtual ~SerialInterface() {};

    virtual int read(uint8_t *data) = 0;

    virtual int write(uint8_t *data, const unsigned int len) = 0;

    virtual int update() = 0;
};

#endif //#ifndef _SERIAL_INTERFACE_HPP_
