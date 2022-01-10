/**
* @file MCP2210Linux.cpp
* @brief Define the class required for SPI communication using SerialBridge in MCP2210 with linux environment.
* @author Taiyou Komazawa
* @date 2021/11/26
*/

#ifdef __linux__

#include "../MCP2210Linux.hpp"

#include <stdio.h>

hid_device *MCP2210Linux::_handle = NULL;

MCP2210Linux::MCP2210Linux(wchar_t* serial_number, MCP2210Linux::cs_pin_t active_cs, uint8_t buffer_size, uint32_t spi_speed, uint8_t spi_mode)
:   _active_cs(active_cs),
    _buffer_size(buffer_size),
    _spi_speed(spi_speed),
    _spi_mode(spi_mode)
{
    int rlt = 0; 
    if(_handle == NULL){
        _handle = InitMCP2210(serial_number);

        ChipSettingsDef chipDef;
 
        chipDef = GetChipSettings(_handle);
 
        for (int i = 0; i < 9; i++) {
            chipDef.GP[i].PinDesignation = GP_PIN_DESIGNATION_CS;
            chipDef.GP[i].GPIODirection = GPIO_DIRECTION_OUTPUT;
            chipDef.GP[i].GPIOOutput = 1;
        }
        rlt = SetChipSettings(_handle, chipDef);
        rlt &= _spi_trx_setting(true);
    }else{
        rlt &= _spi_trx_setting(false);
    }
 
    if (rlt != 0) {
        printf("Errror setting SPI parameters.\n");
        exit(EXIT_FAILURE);
    }
}

MCP2210Linux::~MCP2210Linux()
{
    ReleaseMCP2210(_handle);
}

int MCP2210Linux::update(unsigned char *rx_data, unsigned char *tx_data)
{
    //if(_spi_trx_setting(false) != 0)
    //    return -2;
    SPIDataTransferStatusDef def1 = SPISendReceive(_handle, tx_data, _buffer_size);
    if(def1.NumberOfBytesReceived == _buffer_size){
        for(int i = 0; i < _buffer_size; i++){
            rx_data[i] = def1.DataReceived[i];
        }
        return def1.ErrorCode;
    }
    return -1;
}

unsigned int MCP2210Linux::size()
{
    return _buffer_size;
}

int MCP2210Linux::_spi_trx_setting(bool is_init)
{
    static SPITransferSettingsDef def;
    def = GetSPITransferSettings(_handle);
    if(is_init){
        def.ActiveChipSelectValue = 0x1ff & ~(1 << (int)_active_cs);
        def.IdleChipSelectValue = 0xffff;
        def.BitRate = _spi_speed;
        def.BytesPerSPITransfer = _buffer_size;
        def.SPIMode = _spi_mode;
        def.CSToDataDelay = 0;
        def.LastDataByteToCSDelay = 0;
        def.SubsequentDataByteDelay = 0;
    }else{
        def.ActiveChipSelectValue = def.ActiveChipSelectValue & ~(1 << (int)_active_cs);
        def.BitRate = _spi_speed;
        def.BytesPerSPITransfer = _buffer_size;
        def.SPIMode = _spi_mode;
    }
    return SetSPITransferSettings(_handle, def);
}

#endif //#ifdef __linux__
