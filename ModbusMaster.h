/*
  ModbusMaster.h - library implementing a Modbus Master for Arduino
  Written by Doc Walker (Rx)
  Copyright (c) 2009-2010 WVFans.net
  All rights reserved.
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


/* _____CLASS DEFINITIONS____________________________________________________ */
// library interface description
class ModbusMaster
{
  // user-accessible "public" interface
  public:
    ModbusMaster(void);
    ModbusMaster(uint16_t u16BaudRate);
    void begin(void);
    void begin(uint16_t u16BaudRate);
    
    uint8_t u8ReadCoils(uint8_t u8MBSlave, uint16_t u16ReadAddress,
      uint16_t u16BitQty, uint16_t *u16ReadRegister);
    uint8_t u8ReadDiscreteInputs(uint8_t u8MBSlave, uint16_t u16ReadAddress,
      uint16_t u16BitQty, uint16_t *u16ReadRegister);
    uint8_t u8ReadHoldingRegisters(uint8_t u8MBSlave, uint16_t u16ReadAddress,
      uint16_t u16QtyRead, uint16_t *u16ReadRegister);
    uint8_t u8ReadInputRegisters(uint8_t u8MBSlave, uint16_t u16ReadAddress,
      uint8_t u16QtyRead, uint16_t *u16ReadRegister);
    uint8_t u8WriteSingleCoil(uint8_t u8MBSlave, uint16_t u16WriteAddress,
      uint8_t u8State);
    uint8_t u8WriteSingleRegister(uint8_t u8MBSlave, uint16_t u16WriteAddress,
      uint16_t u16WriteValue);
    uint8_t u8WriteMultipleCoils(uint8_t u8MBSlave, uint16_t u16WriteAddress,
      uint16_t u16BitQty, uint16_t *u16WriteRegister);
    uint8_t u8WriteMultipleRegisters(uint8_t u8MBSlave, uint16_t u16WriteAddress,
      uint16_t u16QtyWrite, uint16_t *u16WriteRegister);
    uint8_t u8MaskWriteRegister(uint8_t u8MBSlave, uint16_t u16WriteAddress,
      uint16_t u16AndMask, uint16_t u16OrMask);
    uint8_t u8ReadWriteMultipleRegisters(uint8_t u8MBSlave,
      uint16_t u16ReadAddress, uint16_t u16QtyRead, uint16_t *u16ReadRegister,
      uint16_t u16WriteAddress, uint16_t u16QtyWrite, uint16_t *u16WriteRegister);
    
  // library-accessible "private" interface
  private:
    uint16_t _u16BaudRate;
    uint8_t u8ModbusMaster(uint8_t u8MBSlave, uint8_t u8MBFunction,
      uint16_t u16ReadAddress, uint16_t u16QtyRead, uint16_t *u16ReadRegister,
      uint16_t u16WriteAddress, uint16_t u16QtyWrite, uint16_t *u16WriteRegister);
};
#endif


/*
|| @changelog
|| | 2010-01-24 - Doc Walker : Initial Release
|| #
*/