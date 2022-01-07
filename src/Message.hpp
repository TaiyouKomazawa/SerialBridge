/**
* @file Message.hpp
* @brief The data format handled by SerialBridge is defined here.
* @author Taiyou Komazawa
* @date 2021/8/11
*
* @details
* @par Example of data format declaration:
*       //Define the structure of the data.
*       typedef struct{
*           int32_t x;
*           int32_t y;
*           int32_t z;
*       } Vector3_t;
*
*       //Put the data format in the message type.
*       //(Since the name is long, you can rename it with typedef as follows.)
*       typedef sb::Message<Vector3_t> Vector3;
*
* @par How to use:
*       Vector3 msg; //Declare a message.
*
*       //Register this message frame in the SerialBridge instance
*       // (assuming you declared it with the name obj this time).
*       //The msg_id passed to the argument together has the role of
*       // associating the data communicated with the msg declared earlier.
*       obj.add_frame(0, &msg); //msg_id = 0
*
*       //The data to be communicated conforms
*       // to the contents of the object member's data structure.
*       msg.data.x;
*       msg.data.y;
*       msg.data.z;
*/

#ifndef _SERIAL_BRIDGE_MESSAGE_HPP_
#define _SERIAL_BRIDGE_MESSAGE_HPP_

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/**
* @namespace sb
* @brief Namespace to indicate SerialBridge messages.
*/
namespace sb
{

/**
* @brief sb::MessageInterface interface class.
* @details
* This is for abstracting various sb::Messages so that they can be handled
*  with a unified interface when used within SerialBridge.
*/
class MessageInterface
{
public:
    void packing(uint8_t id, uint8_t *send_packet, int *data_size);
    void unpacking(uint8_t *received_packet);

    /**
    * @brief Returns whether the message has been updated.
    * 
    * @return true  Message has been updated.
    * @return false Message has not been updated since the last function call.
    */
    virtual bool was_updated() = 0;

protected:
    /**
    * @brief A function that returns a data structure for packing().
    * @return *void Pointer to the data structure of the derived class.
    */
    virtual void *_pk_data_ptr() = 0;

    /**
    * @brief Returns the length of the current packet for packing().
    * @return int Current packet array length.
    */
    virtual int _pk_size() = 0;

    /**
    * @brief A function that returns a data structure for unpacking().
    * @return *void Pointer to the data structure of the derived class.
    */
    virtual void *_upk_data_ptr() = 0;

    /**
    * @brief Returns the length of the current packet for unpacking().
    * @return int Current packet array length.
    */
    virtual int _upk_size() = 0;

    /**
    * @brief The length of the packet used to identify the data.
    */
    enum{
        CTRL_DATA_LEN = 2,
    };

    volatile bool _unpacked;
};

/**
* @brief A class that stores the data processed by the SerialBridge class.
* @tparam DataStruct Specify the type of data structure you want to handle with sb::Message.
*/
template <class DataStruct>
class Message : public MessageInterface
{
public:
    /**
    * @brief Data is exchanged through this member variable.
    * You can specify any structure type here with template parameters.
    */
    DataStruct data;

    /**
    * @brief Message class constructor.
    */
    Message(){}

    /**
    * @brief Message class destructor.
    */
    ~Message(){}

    int size()
    {
        return sizeof(DataStruct) + CTRL_DATA_LEN;
    }

    virtual bool was_updated()
    {
        bool tmp = _unpacked;
        _unpacked = false;
        return tmp;
    }

private:

    virtual void *_pk_data_ptr()
    {
        return &data;
    }

    virtual int _pk_size()
    {
        return size();
    }

    virtual void *_upk_data_ptr()
    {
        return &data;
    }

    virtual int _upk_size()
    {
        return size();
    }
};

/**
* @brief A class that stores the data processed by the SerialBridge class.
* @tparam DataStructIn  Specifies the type of input data structure to process in the sb::DuplexMessage.
* @tparam DataStructOut Specifies the type of output data structure to process in the sb::DuplexMessage.
*/
template <class DataStructIn, class DataStructOut = DataStructIn>
class DuplexMessage : public MessageInterface
{
public:
    /**
    * @brief Tx and Rx data is exchanged through this member variable.
    * You can specify any structure type here with template parameters.
    */
    DataStructOut tx;
    DataStructIn rx;

    /**
    * @brief Message class constructor.
    */
    DuplexMessage(){}

    /**
    * @brief Message class destructor.
    */
    ~DuplexMessage(){}

    int tx_size()
    {
        return sizeof(DataStructOut) + CTRL_DATA_LEN;
    }

    int rx_size()
    {
        return sizeof(DataStructIn) + CTRL_DATA_LEN;
    }

    virtual bool was_updated()
    {
        bool tmp = _unpacked;
        _unpacked = false;
        return tmp;
    }

private:

    virtual void *_pk_data_ptr()
    {
        return &tx;
    }

    virtual int _pk_size()
    {
        return tx_size();
    }

    virtual void *_upk_data_ptr()
    {
        return &rx;
    }

    virtual int _upk_size()
    {
        return rx_size();
    }
};

};

#endif //#ifndef _SERIAL_BRIDGE_MESSAGE_HPP_
