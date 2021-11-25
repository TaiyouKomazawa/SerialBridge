/**
* @file SyncSerialDev.hpp
* @brief The serial device used by SerialBridge complies with this interface class.
* @author Taiyou Komazawa
* @date 2021/11/25
*/

#ifndef _SYNC_SERIAL_DEV_HPP_
#define _SYNC_SERIAL_DEV_HPP_

/**
* @brief Synchronous serial device class used by SerialBridge.
* @note This class is used to solve the difference in serial communication API
*  depending on the execution environment.
*/
class SyncSerialDev
{
public:

    /**
    * @brief Update data synchronization.
    * @param[out] rx_data Data received.
    * @param[in]  tx_data Data to send. 
    * @return int Synchronous state.
    * @retval 0 : No error.
    */
    virtual int update(unsigned char *rx_data, unsigned char *tx_data) = 0;

    /**
    * @brief Returns the size of rxtx buffer.  
    * @return unsigned int 
    */
    virtual unsigned int size() = 0;
};

#endif //#ifndef _SYNC_SERIAL_DEV_HPP_
