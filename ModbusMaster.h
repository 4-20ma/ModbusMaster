/**
@file
Arduino library for communicating with Modbus slaves over RS232/485 (via RTU protocol).

@defgroup setup ModbusMaster Object Instantiation/Initialization
@defgroup buffer ModbusMaster Buffer Management
@defgroup discrete Modbus Function Codes for Discrete Coils/Inputs
@defgroup register Modbus Function Codes for Holding/Input Registers
@defgroup constant Modbus Function Codes, Exception Codes
*/
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

/**
@def __MODBUSMASTER_DEBUG__ (1).
Set to 1 to enable debugging features within class:
  - pin 4 cycles for each byte read in the Modbus response
  - pin 5 cycles for each millisecond timeout during the Modbus response
*/
#define __MODBUSMASTER_DEBUG__ (1)


/* _____STANDARD INCLUDES____________________________________________________ */
// include types & constants of Wiring core API
#include "WProgram.h"


/* _____UTILITY MACROS_______________________________________________________ */
#ifndef lowWord(ww)
/// @def lowWord(ww) ((uint16_t) ((ww) & 0xFFFF)).
/// Macro to return low word of a 32-bit integer
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
/**
Arduino class library for communicating with Modbus slaves over 
RS232/485 (via RTU protocol).
*/
class ModbusMaster
{
  public:
    ModbusMaster();
    ModbusMaster(uint8_t);
    ModbusMaster(uint8_t, uint8_t);
    void begin();
    void begin(uint16_t);
    
    // Modbus exception codes
    /**
    Modbus protocol illegal function exception.
    
    The function code received in the query is not an allowable action for
    the server (or slave). This may be because the function code is only
    applicable to newer devices, and was not implemented in the unit
    selected. It could also indicate that the server (or slave) is in the
    wrong state to process a request of this type, for example because it is
    unconfigured and is being asked to return register values.
    
    @ingroup constant
    */
    static const uint8_t ku8MBIllegalFunction            = 0x01;

    /**
    Modbus protocol illegal data address exception.
    
    The data address received in the query is not an allowable address for 
    the server (or slave). More specifically, the combination of reference 
    number and transfer length is invalid. For a controller with 100 
    registers, the ADU addresses the first register as 0, and the last one 
    as 99. If a request is submitted with a starting register address of 96 
    and a quantity of registers of 4, then this request will successfully 
    operate (address-wise at least) on registers 96, 97, 98, 99. If a 
    request is submitted with a starting register address of 96 and a 
    quantity of registers of 5, then this request will fail with Exception 
    Code 0x02 "Illegal Data Address" since it attempts to operate on 
    registers 96, 97, 98, 99 and 100, and there is no register with address 
    100. 
    
    @ingroup constant
    */
    static const uint8_t ku8MBIllegalDataAddress         = 0x02;
    
    /**
    Modbus protocol illegal data value exception.
    
    A value contained in the query data field is not an allowable value for 
    server (or slave). This indicates a fault in the structure of the 
    remainder of a complex request, such as that the implied length is 
    incorrect. It specifically does NOT mean that a data item submitted for 
    storage in a register has a value outside the expectation of the 
    application program, since the MODBUS protocol is unaware of the 
    significance of any particular value of any particular register.
    
    @ingroup constant
    */
    static const uint8_t ku8MBIllegalDataValue           = 0x03;
    
    /**
    Modbus protocol slave device failure exception.
    
    An unrecoverable error occurred while the server (or slave) was
    attempting to perform the requested action.
    
    @ingroup constant
    */
    static const uint8_t ku8MBSlaveDeviceFailure         = 0x04;

    // Class-defined success/exception codes
    /**
    ModbusMaster success.
    
    Modbus transaction was successful; the following checks were valid:
      - slave ID
      - function code
      - response code
      - data
      - CRC
      
    @ingroup constant
    */
    static const uint8_t ku8MBSuccess                    = 0x00;
    
    /**
    ModbusMaster invalid response slave ID exception.
    
    The slave ID in the response does not match that of the request.
    
    @ingroup constant
    */
    static const uint8_t ku8MBInvalidSlaveID             = 0xE0;
    
    /**
    ModbusMaster invalid response function exception.
    
    The function code in the response does not match that of the request.
    
    @ingroup constant
    */
    static const uint8_t ku8MBInvalidFunction            = 0xE1;
    
    /**
    ModbusMaster response timed out exception.
    
    The entire response was not received within the timeout period, 
    ModbusMaster::ku8MBResponseTimeout. 
    
    @ingroup constant
    */
    static const uint8_t ku8MBResponseTimedOut           = 0xE2;
    
    /**
    ModbusMaster invalid response CRC exception.
    
    The CRC in the response does not match the one calculated.
    
    @ingroup constant
    */
    static const uint8_t ku8MBInvalidCRC                 = 0xE3;
    
    uint16_t GetResponseBuffer(uint8_t);
    void ClearResponseBuffer();
    uint8_t SetTransmitBuffer(uint8_t, uint16_t);
    void ClearTransmitBuffer();
    
    uint8_t ReadCoils(uint16_t, uint16_t);
    uint8_t ReadDiscreteInputs(uint16_t, uint16_t);
    uint8_t ReadHoldingRegisters(uint16_t, uint16_t);
    uint8_t ReadInputRegisters(uint16_t, uint8_t);
    uint8_t WriteSingleCoil(uint16_t, uint8_t);
    uint8_t WriteSingleRegister(uint16_t, uint16_t);
    uint8_t WriteMultipleCoils(uint16_t, uint16_t);
    uint8_t WriteMultipleRegisters(uint16_t, uint16_t);
    uint8_t MaskWriteRegister(uint16_t, uint16_t, uint16_t);
    uint8_t ReadWriteMultipleRegisters(uint16_t, uint16_t, uint16_t, uint16_t);
      
    
  private:
    uint8_t  _u8SerialPort;                                      ///< serial port (0..3) initialized in constructor
    uint8_t  _u8MBSlave;                                         ///< Modbus slave (1..255) initialized in constructor
    uint16_t _u16BaudRate;                                       ///< baud rate (300..115200) initialized in begin()
    static const uint8_t ku8MaxBufferSize                = 64;   ///< size of response/transmit buffers    
    uint16_t _u16ReadAddress;                                    ///< slave register from which to read
    uint16_t _u16ReadQty;                                        ///< quantity of words to read
    uint16_t _u16ResponseBuffer[ku8MaxBufferSize];               ///< buffer to store Modbus slave response; read via GetResponseBuffer()
    uint16_t _u16WriteAddress;                                   ///< slave register to which to write
    uint16_t _u16WriteQty;                                       ///< quantity of words to write
    uint16_t _u16TransmitBuffer[ku8MaxBufferSize];               ///< buffer containing data to transmit to Modbus slave; set via SetTransmitBuffer()
    
    // Modbus function codes for bit access
    static const uint8_t ku8MBReadCoils                  = 0x01; ///< Modbus function 0x01 Read Coils
    static const uint8_t ku8MBReadDiscreteInputs         = 0x02; ///< Modbus function 0x02 Read Discrete Inputs
    static const uint8_t ku8MBWriteSingleCoil            = 0x05; ///< Modbus function 0x05 Write Single Coil
    static const uint8_t ku8MBWriteMultipleCoils         = 0x0F; ///< Modbus function 0x0F Write Multiple Coils

    // Modbus function codes for 16 bit access
    static const uint8_t ku8MBReadHoldingRegisters       = 0x03; ///< Modbus function 0x03 Read Holding Registers
    static const uint8_t ku8MBReadInputRegisters         = 0x04; ///< Modbus function 0x04 Read Input Registers
    static const uint8_t ku8MBWriteSingleRegister        = 0x06; ///< Modbus function 0x06 Write Single Register
    static const uint8_t ku8MBWriteMultipleRegisters     = 0x10; ///< Modbus function 0x10 Write Multiple Registers
    static const uint8_t ku8MBMaskWriteRegister          = 0x16; ///< Modbus function 0x16 Mask Write Register
    static const uint8_t ku8MBReadWriteMultipleRegisters = 0x17; ///< Modbus function 0x17 Read Write Multiple Registers
    
    // Modbus timeout [milliseconds]
    static const uint8_t ku8MBResponseTimeout            = 200;  ///< Modbus timeout [milliseconds]
    
    // master function that conducts Modbus transactions
    uint8_t ModbusMasterTransaction(uint8_t u8MBFunction);
};
#endif

/**
@example examples/Basic/Basic.pde
@example examples/PhoenixContact_nanoLC/PhoenixContact_nanoLC.pde
*/
