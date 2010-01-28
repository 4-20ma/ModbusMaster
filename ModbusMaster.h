/*
  ModbusMaster.h - library implementing a Modbus RTU Master for Arduino
  
  Written by Doc Walker (Rx)
  Copyright © 2009, 2010 Doc Walker
  
  $Author$
  $Date$
  $Id$
  $Rev$
  
  This file is part of ModbusMaster.
  
  ModbusMaster is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.
  
  ModbusMaster is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  
  You should have received a copy of the GNU General Public License
  along with ModbusMaster.  If not, see <http://www.gnu.org/licenses/>.
  This file is part of ModbusMaster.
  
  ModbusMaster is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.
  
  ModbusMaster is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  
  You should have received a copy of the GNU General Public License
  along with ModbusMaster.  If not, see <http://www.gnu.org/licenses/>.
  
  */

// ensure this library description is only included once
#ifndef ModbusMaster_h
#define ModbusMaster_h

// set to 1 to enable class debugging features
#define MODBUSMASTER_DEBUG (1)


/* _____STANDARD INCLUDES____________________________________________________ */
// include types & constants of Wiring core API
#include <WProgram.h>


/* _____UTILITY MACROS_______________________________________________________ */
// Macro to return low word of a 32-bit integer
#ifndef lowWord(ww)
#define lowWord(ww) ((uint16_t) ((ww) & 0xFFFF))
#endif

// Macro to return high word of a 32-bit integer
#ifndef highWord(ww)
#define highWord(ww) ((uint16_t) ((ww) >> 16))
#endif

// Macro to generate 32-bit integer from (2) 16-bit words
#ifndef LONG(hi, low)
#define LONG(hi, lo) ((uint32_t) ((hi) << 16 | (lo)))
#endif


/* _____PROJECT INCLUDES_____________________________________________________ */
// functions to calculate Modbus Application Data Unit CRC
#include <util/crc16.h>


/* _____PROJECT CONSTANTS____________________________________________________ */
// Modbus function codes for bit access
const uint8_t ku8MBReadCoils                  = 0x01;
const uint8_t ku8MBReadDiscreteInputs         = 0x02;
const uint8_t ku8MBWriteSingleCoil            = 0x05;
const uint8_t ku8MBWriteMultipleCoils         = 0x0F;

// Modbus function codes for 16 bit access
const uint8_t ku8MBReadHoldingRegisters       = 0x03;
const uint8_t ku8MBReadInputRegisters         = 0x04;
const uint8_t ku8MBWriteSingleRegister        = 0x06;
const uint8_t ku8MBWriteMultipleRegisters     = 0x10;
const uint8_t ku8MBMaskWriteRegister          = 0x16;
const uint8_t ku8MBReadWriteMultipleRegisters = 0x17;

// Modbus exception codes
const uint8_t ku8MBIllegalFunction            = 0x01;
const uint8_t ku8MBIllegalDataAddress         = 0x02;
const uint8_t ku8MBIllegalDataValue           = 0x03;
const uint8_t ku8MBSlaveDeviceFailure         = 0x04;

// Class-defined success/exception codes
const uint8_t ku8MBSuccess                    = 0x00;
const uint8_t ku8MBInvalidRequestADUSize      = 0xE1;
const uint8_t ku8MBInvalidResponseADUSize     = 0xE2;
const uint8_t ku8MBInvalidSlaveID             = 0xE3;
const uint8_t ku8MBInvalidFunction            = 0xE4;
const uint8_t ku8MBResponseTimedOut           = 0xE5;
const uint8_t ku8MBInvalidCRC                 = 0xE6;

// Modbus timeout [milliseconds]
const uint8_t ku8MBResponseTimeout            = 200;

// Modbus exception codes
enum eStatus_t {kMBIllegalFunction = 0x01, kMBIllegalDataAddress = 0x02,
  kMBIllegalDataValue = 0x03, kMBSlaveDeviceFailure = 0x04,
  kMBSuccess = 0x00, kMBInvalidRequestADUSize = 0xE1,
  kMBInvalidResponseADUSize  = 0xE2, kMBInvalidSlaveID = 0xE3,
  kMBInvalidFunction = 0xE4, kMBResponseTimedOut = 0xE5,
  kMBInvalidCRC = 0xE6};

/* _____CLASS DEFINITIONS____________________________________________________ */
// library interface description
class ModbusMaster
{
  // user-accessible "public" interface
  public:
    ModbusMaster(void);
    ModbusMaster(uint8_t u8MBSlave);
    void begin(void);
    void begin(uint16_t u16BaudRate);
    
    eStatus_t ReadCoils(uint16_t u16ReadAddress, uint16_t u16BitQty,
      uint16_t *u16ReadRegister);
    eStatus_t ReadDiscreteInputs(uint16_t u16ReadAddress, uint16_t u16BitQty,
      uint16_t *u16ReadRegister);
    eStatus_t ReadHoldingRegisters(uint16_t u16ReadAddress, uint16_t u16QtyRead,
      uint16_t *u16ReadRegister);
    eStatus_t ReadInputRegisters(uint16_t u16ReadAddress, uint8_t u16QtyRead,
      uint16_t *u16ReadRegister);
    eStatus_t WriteSingleCoil(uint16_t u16WriteAddress, uint8_t u8State);
    eStatus_t WriteSingleRegister(uint16_t u16WriteAddress, uint16_t u16WriteValue);
    eStatus_t WriteMultipleCoils(uint16_t u16WriteAddress, uint16_t u16BitQty,
      uint16_t *u16WriteRegister);
    eStatus_t WriteMultipleRegisters(uint16_t u16WriteAddress, uint16_t u16QtyWrite,
      uint16_t *u16WriteRegister);
    eStatus_t MaskWriteRegister(uint16_t u16WriteAddress, uint16_t u16AndMask,
      uint16_t u16OrMask);
    eStatus_t ReadWriteMultipleRegisters(uint16_t u16ReadAddress, uint16_t u16QtyRead,
      uint16_t *u16ReadRegister, uint16_t u16WriteAddress, uint16_t u16QtyWrite,
      uint16_t *u16WriteRegister);
    
  // library-accessible "private" interface
  private:
    uint8_t _u8MBSlave;
    uint16_t _u16BaudRate;
    
    // Modbus timeout [milliseconds]
    uint8_t _u8MBResponseTimeout;
    
    // Modbus function codes for bit access
    enum eMBFunction_t {kMBReadCoils = 0x01, kMBReadDiscreteInputs = 0x02,
      kMBWriteSingleCoil = 0x05, kMBWriteMultipleCoils = 0x0F,
      kMBReadHoldingRegisters = 0x03, kMBReadInputRegisters = 0x04,
      kMBWriteSingleRegister = 0x06, kMBWriteMultipleRegisters = 0x10,
      kMBMaskWriteRegister = 0x16, kMBReadWriteMultipleRegisters = 0x17};

    eStatus_t ModbusMasterTransaction(eMBFunction_t eMBFunction, uint16_t u16ReadAddress,
      uint16_t u16QtyRead, uint16_t *u16ReadRegister, uint16_t u16WriteAddress,
      uint16_t u16QtyWrite, uint16_t *u16WriteRegister);
};
#endif
