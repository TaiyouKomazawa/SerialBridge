/**
* @file MCP2210Linux.cpp
* @brief Define the class required for SPI communication using SerialBridge in MCP2210 with linux environment.
* @author Taiyou Komazawa
* @date 2021/11/26
*/

#ifdef __linux__

#include "../MCP2210Linux.hpp"

#include <stdio.h>

bool MCP2210Linux::_is_opened = false;

MCP2210Linux::MCP2210Linux(wchar_t* serial_number, MCP2210Linux::cs_pin_t active_cs, int spi_mode, int spi_speed, uint8_t buffer_size)
:   _buffer_size(buffer_size)
{
 
    _handle = InitMCP2210(serial_number);

    ChipSettingsDef chipDef;
 
    chipDef = GetChipSettings(_handle);
 
    for (int i = 0; i < 9; i++) {
        chipDef.GP[i].PinDesignation = GP_PIN_DESIGNATION_CS;
        chipDef.GP[i].GPIODirection = GPIO_DIRECTION_OUTPUT;
        chipDef.GP[i].GPIOOutput = 1;
    }
    int r = SetChipSettings(_handle, chipDef);
    
    SPITransferSettingsDef def;
    def = GetSPITransferSettings(_handle);
 
    def.ActiveChipSelectValue = ~(1 << (int)active_cs);
    def.IdleChipSelectValue = 0xffff;
    def.BitRate = spi_speed;
    def.BytesPerSPITransfer = _buffer_size;
    def.SPIMode = spi_mode;
    def.CSToDataDelay = 0;
    def.LastDataByteToCSDelay = 0;
    def.SubsequentDataByteDelay = 0;
 
    r &= SetSPITransferSettings(_handle, def);
 
    if (r != 0) {
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

#endif //#ifdef __linux__
