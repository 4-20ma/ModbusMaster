/*
  ModbusMaster.cpp - library implementing a Modbus RTU Master for Arduino
  
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


/* _____STANDARD INCLUDES____________________________________________________ */


/* _____PROJECT INCLUDES_____________________________________________________ */
#include "ModbusMaster.h"


/* _____GLOBAL VARIABLES_____________________________________________________ */
HardwareSerial MBSerial = Serial;


/* _____PUBLIC FUNCTIONS_____________________________________________________ */
// constructor
ModbusMaster::ModbusMaster(void)
{
  // default to serial port 0, slave ID 1
  _u8SerialPort = 0;
  _u8MBSlave = 1;
}


// constructor
ModbusMaster::ModbusMaster(uint8_t u8MBSlave)
{
  // default to serial port 0, set slave ID
  _u8SerialPort = 0;
  _u8MBSlave = u8MBSlave;
}


// constructor
ModbusMaster::ModbusMaster(uint8_t u8SerialPort, uint8_t u8MBSlave)
{
  // set desired serial port (0..3), slave ID
  _u8SerialPort = (u8SerialPort > 3) ? 0 : u8SerialPort;
  _u8MBSlave = u8MBSlave;
}


// initialize serial port for Modbus communication using default baud rate
void ModbusMaster::begin(void)
{
  // default to 19200
  begin(19200);
}


// initialize serial port for Modbus communication
void ModbusMaster::begin(uint16_t u16BaudRate)
{
  switch(_u8SerialPort)
  {
#if defined(__AVR_ATmega1280__)
    case 1:
      MBSerial = Serial1;
      break;
      
    case 2:
      MBSerial = Serial2;
      break;
      
    case 3:
      MBSerial = Serial3;
      break;
#endif
      
    case 0:
    default:
      MBSerial = Serial;
      break;
  }
  
  MBSerial.begin(u16BaudRate);
#if __MODBUSMASTER_DEBUG__
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
#endif
}


// Modbus function 0x01 Read Coils
uint8_t ModbusMaster::ReadCoils(uint16_t u16ReadAddress, uint16_t u16BitQty)
{
  _u16ReadAddress = u16ReadAddress;
  _u16ReadQty = u16BitQty;
  return ModbusMasterTransaction(ku8MBReadCoils);
}


// Modbus function 0x02 Read Discrete Inputs
uint8_t ModbusMaster::ReadDiscreteInputs(uint16_t u16ReadAddress,
  uint16_t u16BitQty)
{
  _u16ReadAddress = u16ReadAddress;
  _u16ReadQty = u16BitQty;
  return ModbusMasterTransaction(ku8MBReadDiscreteInputs);
}


// Modbus function 0x03 Read Holding Registers
uint8_t ModbusMaster::ReadHoldingRegisters(uint16_t u16ReadAddress,
  uint16_t u16ReadQty)
{
  _u16ReadAddress = u16ReadAddress;
  _u16ReadQty = u16ReadQty;
  return ModbusMasterTransaction(ku8MBReadHoldingRegisters);
}


// Modbus function 0x04 Read Input Registers
uint8_t ModbusMaster::ReadInputRegisters(uint16_t u16ReadAddress,
  uint8_t u16ReadQty)
{
  _u16ReadAddress = u16ReadAddress;
  _u16ReadQty = u16ReadQty;
  return ModbusMasterTransaction(ku8MBReadInputRegisters);
}


// Modbus function 0x05 Write Single Coil
uint8_t ModbusMaster::WriteSingleCoil(uint16_t u16WriteAddress, uint8_t u8State)
{
  _u16WriteAddress = u16WriteAddress;
  _u16WriteQty = (u8State ? 0xFF00 : 0x0000);
  return ModbusMasterTransaction(ku8MBWriteSingleCoil);
}


// Modbus function 0x06 Write Single Register
uint8_t ModbusMaster::WriteSingleRegister(uint16_t u16WriteAddress,
  uint16_t u16WriteValue)
{
  _u16WriteAddress = u16WriteAddress;
  _u16WriteQty = 0;
  _u16WriteRegister[0] = u16WriteValue;
  return ModbusMasterTransaction(ku8MBWriteSingleRegister);
}


// Modbus function 0x0F Write Multiple Coils
uint8_t ModbusMaster::WriteMultipleCoils(uint16_t u16WriteAddress,
  uint16_t u16BitQty)
{
  _u16WriteAddress = u16WriteAddress;
  _u16WriteQty = u16BitQty;
  return ModbusMasterTransaction(ku8MBWriteMultipleCoils);
}


// Modbus function 0x10 Write Multiple Registers
uint8_t ModbusMaster::WriteMultipleRegisters(uint16_t u16WriteAddress,
  uint16_t u16WriteQty)
{
  _u16WriteAddress = u16WriteAddress;
  _u16WriteQty = u16WriteQty;
  return ModbusMasterTransaction(ku8MBWriteMultipleRegisters);
}


// Modbus function 0x16 Mask Write Register
uint8_t ModbusMaster::MaskWriteRegister(uint16_t u16WriteAddress,
  uint16_t u16AndMask, uint16_t u16OrMask)
{
  _u16WriteAddress = u16WriteAddress;
  _u16WriteRegister[0] = u16AndMask;
  _u16WriteRegister[1] = u16OrMask;
  return ModbusMasterTransaction(ku8MBMaskWriteRegister);
}


// Modbus function 0x17 Read Write Multiple Registers
uint8_t ModbusMaster::ReadWriteMultipleRegisters(uint16_t u16ReadAddress,
  uint16_t u16ReadQty, uint16_t u16WriteAddress, uint16_t u16WriteQty)
{
  _u16ReadAddress = u16ReadAddress;
  _u16ReadQty = u16ReadQty;
  _u16WriteAddress = u16WriteAddress;
  _u16WriteQty = u16WriteQty;
  return ModbusMasterTransaction(ku8MBReadWriteMultipleRegisters);
}


// return value of _u16ReadRegister[u8Index]
uint16_t ModbusMaster::RX(uint8_t u8Index)
{
  if (u8Index < ku8MaxArraySize)
  {
    return _u16ReadRegister[u8Index];
  }
  else
  {
    return 0xFFFF;
  }
}



// set value of _u16WriteRegister[u8Index] to u16Value
uint8_t ModbusMaster::TX(uint8_t u8Index, uint16_t u16Value)
{
  if (u8Index < ku8MaxArraySize)
  {
    _u16WriteRegister[u8Index] = u16Value;
    return ku8MBSuccess;
  }
  else
  {
    return ku8MBIllegalDataAddress;
  }
}


/* _____PRIVATE FUNCTIONS____________________________________________________ */
// Modbus master composite function
uint8_t ModbusMaster::ModbusMasterTransaction(uint8_t u8MBFunction)
{
  uint8_t u8ModbusADU[256];
  uint8_t u8ModbusADUSize = 0;
  uint8_t i, u8Qty;
  uint16_t u16CRC;
  uint8_t u8TimeLeft = ku8MBResponseTimeout;
  uint8_t u8BytesLeft = 8;
  uint8_t u8MBStatus = ku8MBSuccess;
  
  // assemble Modbus Request Application Data Unit
  u8ModbusADU[u8ModbusADUSize++] = _u8MBSlave;
  u8ModbusADU[u8ModbusADUSize++] = u8MBFunction;
  
  switch(u8MBFunction)
  {
    case ku8MBReadCoils:
    case ku8MBReadDiscreteInputs:
    case ku8MBReadInputRegisters:
    case ku8MBReadHoldingRegisters:
    case ku8MBReadWriteMultipleRegisters:
      u8ModbusADU[u8ModbusADUSize++] = highByte(_u16ReadAddress);
      u8ModbusADU[u8ModbusADUSize++] = lowByte(_u16ReadAddress);
      u8ModbusADU[u8ModbusADUSize++] = highByte(_u16ReadQty);
      u8ModbusADU[u8ModbusADUSize++] = lowByte(_u16ReadQty);
      break;
  }
  
  switch(u8MBFunction)
  {
    case ku8MBWriteSingleCoil:
    case ku8MBMaskWriteRegister:
    case ku8MBWriteMultipleCoils:
    case ku8MBWriteSingleRegister:
    case ku8MBWriteMultipleRegisters:
    case ku8MBReadWriteMultipleRegisters:
      u8ModbusADU[u8ModbusADUSize++] = highByte(_u16WriteAddress);
      u8ModbusADU[u8ModbusADUSize++] = lowByte(_u16WriteAddress);
      break;
  }
  
  switch(u8MBFunction)
  {
    case ku8MBWriteSingleCoil:
      u8ModbusADU[u8ModbusADUSize++] = highByte(_u16WriteQty);
      u8ModbusADU[u8ModbusADUSize++] = lowByte(_u16WriteQty);
      break;
      
    case ku8MBWriteSingleRegister:
      u8ModbusADU[u8ModbusADUSize++] = highByte(_u16WriteRegister[0]);
      u8ModbusADU[u8ModbusADUSize++] = lowByte(_u16WriteRegister[0]);
      break;
      
    case ku8MBWriteMultipleCoils:
      u8ModbusADU[u8ModbusADUSize++] = highByte(_u16WriteQty);
      u8ModbusADU[u8ModbusADUSize++] = lowByte(_u16WriteQty);
      u8Qty = (_u16WriteQty % 8) ? ((_u16WriteQty >> 3) + 1) : (_u16WriteQty >> 3);
      u8ModbusADU[u8ModbusADUSize++] = u8Qty;
      for (i = 0; i < u8Qty; i++)
      {
        switch(i % 2)
        {
          case 0: // i is even
            u8ModbusADU[u8ModbusADUSize++] = lowByte(_u16WriteRegister[i >> 1]);
            break;
            
          case 1: // i is odd
            u8ModbusADU[u8ModbusADUSize++] = highByte(_u16WriteRegister[i >> 1]);
            break;
        }
      }
      break;
      
    case ku8MBWriteMultipleRegisters:
    case ku8MBReadWriteMultipleRegisters:
      u8ModbusADU[u8ModbusADUSize++] = highByte(_u16WriteQty);
      u8ModbusADU[u8ModbusADUSize++] = lowByte(_u16WriteQty);
      u8ModbusADU[u8ModbusADUSize++] = lowByte(_u16WriteQty << 1);
      
      for (i = 0; i < lowByte(_u16WriteQty); i++)
      {
        u8ModbusADU[u8ModbusADUSize++] = highByte(_u16WriteRegister[i]);
        u8ModbusADU[u8ModbusADUSize++] = lowByte(_u16WriteRegister[i]);
      }
      break;
      
    case ku8MBMaskWriteRegister:
      u8ModbusADU[u8ModbusADUSize++] = highByte(_u16WriteRegister[0]);
      u8ModbusADU[u8ModbusADUSize++] = lowByte(_u16WriteRegister[0]);
      u8ModbusADU[u8ModbusADUSize++] = highByte(_u16WriteRegister[1]);
      u8ModbusADU[u8ModbusADUSize++] = lowByte(_u16WriteRegister[1]);
      break;
  }
  
  
  // append CRC
  u16CRC = 0xFFFF;
  for (i = 0; i < u8ModbusADUSize; i++)
  {
    u16CRC = _crc16_update(u16CRC, u8ModbusADU[i]);
  }
  u8ModbusADU[u8ModbusADUSize++] = lowByte(u16CRC);
  u8ModbusADU[u8ModbusADUSize++] = highByte(u16CRC);
  u8ModbusADU[u8ModbusADUSize] = 0;
  
  // transmit request
  for (i = 0; i < u8ModbusADUSize; i++)
  {
    MBSerial.print(u8ModbusADU[i], BYTE);
  }
  
  u8ModbusADUSize = 0;
  MBSerial.flush();
  
  // loop until we run out of time or bytes, or an error occurs
  while (u8TimeLeft && u8BytesLeft && !u8MBStatus)
  {
    if (MBSerial.available())
    {
#if __MODBUSMASTER_DEBUG__
      digitalWrite(4, true);
#endif
      u8ModbusADU[u8ModbusADUSize++] = MBSerial.read();
      u8BytesLeft--;
#if __MODBUSMASTER_DEBUG__
      digitalWrite(4, false);
#endif
    }
    else
    {
#if __MODBUSMASTER_DEBUG__
      digitalWrite(5, true);
#endif
      delayMicroseconds(1000);
      u8TimeLeft--;
#if __MODBUSMASTER_DEBUG__
      digitalWrite(5, false);
#endif
    }
    
    // evaluate slave ID, function code once enough bytes have been read
    if (u8ModbusADUSize == 5)
    {
      // verify response is for correct Modbus slave
      if (u8ModbusADU[0] != _u8MBSlave)
      {
        u8MBStatus = ku8MBInvalidSlaveID;
        break;
      }
      
      // verify response is for correct Modbus function code (mask exception bit 7)
      if ((u8ModbusADU[1] & 0x7F) != u8MBFunction)
      {
        u8MBStatus = ku8MBInvalidFunction;
        break;
      }
      
      // check whether Modbus exception occurred; return Modbus Exception Code
      if (bitRead(u8ModbusADU[1], 7))
      {
        u8MBStatus = u8ModbusADU[2];
        break;
      }
      
      // evaluate returned Modbus function code
      switch(u8ModbusADU[1])
      {
        case ku8MBReadCoils:
        case ku8MBReadDiscreteInputs:
        case ku8MBReadInputRegisters:
        case ku8MBReadHoldingRegisters:
        case ku8MBReadWriteMultipleRegisters:
          u8BytesLeft = u8ModbusADU[2];
          break;
          
        case ku8MBWriteSingleCoil:
        case ku8MBWriteMultipleCoils:
        case ku8MBWriteSingleRegister:
          u8BytesLeft = 3;
          break;
          
        case ku8MBMaskWriteRegister:
          u8BytesLeft = 5;
          break;
      }
    }
    
    if (u8ModbusADUSize == 6)
    {
      switch(u8ModbusADU[1])
      {
        case ku8MBWriteMultipleRegisters:
          u8BytesLeft = u8ModbusADU[5];
          break;
      }
    }
  }
  
  // verify response is large enough to inspect further
  if (!u8MBStatus && (u8TimeLeft == 0 || u8ModbusADUSize < 5))
  {
    u8MBStatus = ku8MBResponseTimedOut;
  }
  
  // calculate CRC
  u16CRC = 0xFFFF;
  for (i = 0; i < (u8ModbusADUSize - 2); i++)
  {
    u16CRC = _crc16_update(u16CRC, u8ModbusADU[i]);
  }
  
  // verify CRC
  if (!u8MBStatus && (lowByte(u16CRC) != u8ModbusADU[u8ModbusADUSize - 2] ||
    highByte(u16CRC) != u8ModbusADU[u8ModbusADUSize - 1]))
  {
    u8MBStatus = ku8MBInvalidCRC;
  }

  // disassemble ADU into words
  if (!u8MBStatus)
  {
    // evaluate returned Modbus function code
    switch(u8ModbusADU[1])
    {
      case ku8MBReadCoils:
      case ku8MBReadDiscreteInputs:
        // load bytes into word; response bytes are ordered L, H, L, H, ...
        for (i = 0; i < (u8ModbusADU[2] >> 1); i++)
        {
          if (i < ku8MaxArraySize)
          {
            _u16ReadRegister[i] = word(u8ModbusADU[2 * i + 4], u8ModbusADU[2 * i + 3]);
          }
        }
        
        // in the event of an odd number of bytes, load last byte into zero-padded word
        if (u8ModbusADU[2] % 2)
        {
          if (i < ku8MaxArraySize)
          {
            _u16ReadRegister[i] = word(0, u8ModbusADU[2 * i + 3]);
          }
        }
        break;
        
      case ku8MBReadInputRegisters:
      case ku8MBReadHoldingRegisters:
      case ku8MBReadWriteMultipleRegisters:
        // load bytes into word; response bytes are ordered H, L, H, L, ...
        for (i = 0; i < (u8ModbusADU[2] >> 1); i++)
        {
          if (i < ku8MaxArraySize)
          {
            _u16ReadRegister[i] = word(u8ModbusADU[2 * i + 3], u8ModbusADU[2 * i + 4]);
          }
        }
        break;
    }
  }
  
  return u8MBStatus;
}
