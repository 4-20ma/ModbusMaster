/*
  ModbusMaster.h - library implementing a Modbus RTU Master for Arduino
  
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
  
  Written by Doc Walker (Rx)
  Copyright © 2009, 2010 Doc Walker <dfwmountaineers at gmail dot com>
  $Id$
  
*/

  
#ifndef ModbusMaster_h
#define ModbusMaster_h

// set to 1 to enable debugging features
#define __MODBUSMASTER_DEBUG__ (1)


/* _____STANDARD INCLUDES____________________________________________________ */
// include types & constants of Wiring core API
#include "WProgram.h"


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


/* _____CLASS DEFINITIONS____________________________________________________ */
class ModbusMaster
{
  public:
    // constructor; default serial port 0, slave ID 1
    ModbusMaster(void);
    
    // constructor; default serial port 0, call function with desired slave ID
    ModbusMaster(uint8_t u8MBSlave);
    
    // constructor; call function with desired serial port (0..3), slave ID
    ModbusMaster(uint8_t u8SerialPort, uint8_t u8MBSlave);
    
    // initialize class object, serial port using default baud rate 19200
    void begin(void);
    
    // initialize class object, serial port using desired baud rate
    void begin(uint16_t u16BaudRate);
    
    // Modbus exception codes
    static const uint8_t ku8MBIllegalFunction            = 0x01;
    static const uint8_t ku8MBIllegalDataAddress         = 0x02;
    static const uint8_t ku8MBIllegalDataValue           = 0x03;
    static const uint8_t ku8MBSlaveDeviceFailure         = 0x04;

    // Class-defined success/exception codes
    static const uint8_t ku8MBSuccess                    = 0x00;
    static const uint8_t ku8MBInvalidRequestADUSize      = 0xE1;
    static const uint8_t ku8MBInvalidResponseADUSize     = 0xE2;
    static const uint8_t ku8MBInvalidSlaveID             = 0xE3;
    static const uint8_t ku8MBInvalidFunction            = 0xE4;
    static const uint8_t ku8MBResponseTimedOut           = 0xE5;
    static const uint8_t ku8MBInvalidCRC                 = 0xE6;
    
    // Modbus function 0x01 Read Coils
    uint8_t ReadCoils(uint16_t u16ReadAddress, uint16_t u16BitQty);
    
    // Modbus function 0x02 Read Discrete Inputs
    uint8_t ReadDiscreteInputs(uint16_t u16ReadAddress, uint16_t u16BitQty);
    
    // Modbus function 0x03 Read Holding Registers
    uint8_t ReadHoldingRegisters(uint16_t u16ReadAddress, uint16_t u16ReadQty);
    
    // Modbus function 0x04 Read Input Registers
    uint8_t ReadInputRegisters(uint16_t u16ReadAddress, uint8_t u16ReadQty);
    
    // Modbus function 0x05 Write Single Coil
    uint8_t WriteSingleCoil(uint16_t u16WriteAddress, uint8_t u8State);
    
    // Modbus function 0x06 Write Single Register
    uint8_t WriteSingleRegister(uint16_t u16WriteAddress, uint16_t u16WriteValue);
    
    // Modbus function 0x0F Write Multiple Coils
    uint8_t WriteMultipleCoils(uint16_t u16WriteAddress, uint16_t u16BitQty);
    
    // Modbus function 0x10 Write Multiple Registers
    uint8_t WriteMultipleRegisters(uint16_t u16WriteAddress, uint16_t u16WriteQty);
    
    // Modbus function 0x16 Mask Write Register
    uint8_t MaskWriteRegister(uint16_t u16WriteAddress, uint16_t u16AndMask,
      uint16_t u16OrMask);
      
    // Modbus function 0x17 Read Write Multiple Registers
    uint8_t ReadWriteMultipleRegisters(uint16_t u16ReadAddress, uint16_t u16ReadQty,
      uint16_t u16WriteAddress, uint16_t u16WriteQty);
      
    // method used to retrieve 16-bit words from Modbus queries
    uint16_t RX(uint8_t u8Index);
    
    // method used to set 16-bit words for Modbus queries
    uint8_t TX(uint8_t u8Index, uint16_t u16Value);
    
    
  private:
    // which serial port, Modbus slave ID, baud rate
    uint8_t _u8SerialPort;
    uint8_t _u8MBSlave;
    uint16_t _u16BaudRate;
    
    // size of RX/TX array
    static const uint8_t ku8MaxArraySize                 = 64;
    
    // slave address, quantity to read; store in register
    uint16_t _u16ReadAddress;
    uint16_t _u16ReadQty;
    uint16_t _u16ReadRegister[ku8MaxArraySize];
    
    // slave address, quantity to write; retrieve from register
    uint16_t _u16WriteAddress;
    uint16_t _u16WriteQty;
    uint16_t _u16WriteRegister[ku8MaxArraySize];
    
    // Modbus function codes for bit access
    static const uint8_t ku8MBReadCoils                  = 0x01;
    static const uint8_t ku8MBReadDiscreteInputs         = 0x02;
    static const uint8_t ku8MBWriteSingleCoil            = 0x05;
    static const uint8_t ku8MBWriteMultipleCoils         = 0x0F;

    // Modbus function codes for 16 bit access
    static const uint8_t ku8MBReadHoldingRegisters       = 0x03;
    static const uint8_t ku8MBReadInputRegisters         = 0x04;
    static const uint8_t ku8MBWriteSingleRegister        = 0x06;
    static const uint8_t ku8MBWriteMultipleRegisters     = 0x10;
    static const uint8_t ku8MBMaskWriteRegister          = 0x16;
    static const uint8_t ku8MBReadWriteMultipleRegisters = 0x17;
    
    // Modbus timeout [milliseconds]
    static const uint8_t ku8MBResponseTimeout            = 200;
    
    // master function that conducts Modbus transactions
    uint8_t ModbusMasterTransaction(uint8_t u8MBFunction);
};
#endif
