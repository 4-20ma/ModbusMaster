/*
  ModbusMaster.cpp - library implementing a Modbus RTU Master for Arduino
  
  Written by Doc Walker (Rx)
  Copyright © 2009, 2010 Doc Walker
  
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


/* _____STANDARD INCLUDES____________________________________________________ */


/* _____PROJECT INCLUDES_____________________________________________________ */
#include "ModbusMaster.h"


/* _____PUBLIC FUNCTIONS_____________________________________________________ */
ModbusMaster::ModbusMaster(void)
{
}


// initialize serial port for Modbus communication using default baud rate
void ModbusMaster::begin(void)
{
  begin(19200);
}


// initialize serial port for Modbus communication
void ModbusMaster::begin(uint16_t u16BaudRate)
{
  Serial.begin(u16BaudRate);
#if MODBUSMASTER_DEBUG
  pinMode(4, OUTPUT); // remove me in final version - Rx
  pinMode(5, OUTPUT); // remove me in final version - Rx
#endif
}


// Modbus function 0x01 Read Coils
uint8_t ModbusMaster::u8ReadCoils(uint8_t u8MBSlave, uint16_t u16ReadAddress,
  uint16_t u16BitQty, uint16_t *u16ReadRegister)
{
  return u8ModbusMaster(u8MBSlave, ku8MBReadCoils, u16ReadAddress, u16BitQty,
    u16ReadRegister, 0, 0, 0);
}


// Modbus function 0x02 Read Discrete Inputs
uint8_t ModbusMaster::u8ReadDiscreteInputs(uint8_t u8MBSlave,
  uint16_t u16ReadAddress, uint16_t u16BitQty, uint16_t *u16ReadRegister)
{
  return u8ModbusMaster(u8MBSlave, ku8MBReadDiscreteInputs, u16ReadAddress,
    u16BitQty, u16ReadRegister, 0, 0, 0);
}


// Modbus function 0x03 Read Holding Registers
uint8_t ModbusMaster::u8ReadHoldingRegisters(uint8_t u8MBSlave,
  uint16_t u16ReadAddress, uint16_t u16QtyRead, uint16_t *u16ReadRegister)
{
  return u8ModbusMaster(u8MBSlave, ku8MBReadHoldingRegisters, u16ReadAddress,
    u16QtyRead, u16ReadRegister, 0, 0, 0);
}


// Modbus function 0x04 Read Input Registers
uint8_t ModbusMaster::u8ReadInputRegisters(uint8_t u8MBSlave,
  uint16_t u16ReadAddress, uint8_t u16QtyRead, uint16_t *u16ReadRegister)
{
  return u8ModbusMaster(u8MBSlave, ku8MBReadInputRegisters, u16ReadAddress,
    u16QtyRead, u16ReadRegister, 0, 0, 0);
}


// Modbus function 0x05 Write Single Coil
uint8_t ModbusMaster::u8WriteSingleCoil(uint8_t u8MBSlave,
  uint16_t u16WriteAddress, uint8_t u8State)
{
  return u8ModbusMaster(u8MBSlave, ku8MBWriteSingleCoil, 0, 0, 0,
    u16WriteAddress, (u8State ? 0xFF00 : 0x0000), 0);
}


// Modbus function 0x06 Write Single Register
uint8_t ModbusMaster::u8WriteSingleRegister(uint8_t u8MBSlave,
  uint16_t u16WriteAddress, uint16_t u16WriteValue)
{
  return u8ModbusMaster(u8MBSlave, ku8MBWriteSingleRegister, 0, 0, 0,
    u16WriteAddress, 0, &u16WriteValue);
}


// Modbus function 0x0F Write Multiple Coils
uint8_t ModbusMaster::u8WriteMultipleCoils(uint8_t u8MBSlave,
  uint16_t u16WriteAddress, uint16_t u16BitQty, uint16_t *u16WriteRegister)
{
  return u8ModbusMaster(u8MBSlave, ku8MBWriteMultipleCoils, 0, 0, 0,
    u16WriteAddress, u16BitQty, u16WriteRegister);
}


// Modbus function 0x10 Write Multiple Registers
uint8_t ModbusMaster::u8WriteMultipleRegisters(uint8_t u8MBSlave,
  uint16_t u16WriteAddress, uint16_t u16QtyWrite, uint16_t *u16WriteRegister)
{
  return u8ModbusMaster(u8MBSlave, ku8MBWriteMultipleRegisters, 0, 0, 0,
    u16WriteAddress, u16QtyWrite, u16WriteRegister);
}


// Modbus function 0x16 Mask Write Register
uint8_t ModbusMaster::u8MaskWriteRegister(uint8_t u8MBSlave,
  uint16_t u16WriteAddress, uint16_t u16AndMask, uint16_t u16OrMask)
{
  uint16_t u16WriteRegister[2];
  u16WriteRegister[0] = u16AndMask;
  u16WriteRegister[1] = u16OrMask;
  return u8ModbusMaster(u8MBSlave, ku8MBMaskWriteRegister, 0, 0, 0,
    u16WriteAddress, 0, u16WriteRegister);
}


// Modbus function 0x17 Read Write Multiple Registers
uint8_t ModbusMaster::u8ReadWriteMultipleRegisters(uint8_t u8MBSlave,
  uint16_t u16ReadAddress, uint16_t u16QtyRead, uint16_t *u16ReadRegister,
  uint16_t u16WriteAddress, uint16_t u16QtyWrite, uint16_t *u16WriteRegister)
{
  return u8ModbusMaster(u8MBSlave, ku8MBReadWriteMultipleRegisters,
    u16ReadAddress, u16QtyRead, u16ReadRegister, u16WriteAddress, u16QtyWrite,
    u16WriteRegister);
}


/* _____PRIVATE FUNCTIONS____________________________________________________ */
// Modbus master composite function
uint8_t ModbusMaster::u8ModbusMaster(uint8_t u8MBSlave, uint8_t u8MBFunction,
  uint16_t u16ReadAddress, uint16_t u16QtyRead, uint16_t *u16ReadRegister,
  uint16_t u16WriteAddress, uint16_t u16QtyWrite, uint16_t *u16WriteRegister)
{
  uint8_t u8ModbusADU[256];
  uint8_t u8ModbusADUSize = 0;
  uint8_t i, u8Qty;
  uint16_t u16CRC;
  uint8_t u8TimeLeft = ku8MBResponseTimeout;
  uint8_t u8BytesLeft = 8;
  uint8_t u8Status = ku8MBSuccess;
  
  // assemble Modbus Request Application Data Unit
  u8ModbusADU[u8ModbusADUSize++] = u8MBSlave;
  u8ModbusADU[u8ModbusADUSize++] = u8MBFunction;
  
  switch(u8MBFunction)
  {
    case ku8MBReadCoils:
    case ku8MBReadDiscreteInputs:
    case ku8MBReadInputRegisters:
    case ku8MBReadHoldingRegisters:
    case ku8MBReadWriteMultipleRegisters:
      u8ModbusADU[u8ModbusADUSize++] = highByte(u16ReadAddress);
      u8ModbusADU[u8ModbusADUSize++] = lowByte(u16ReadAddress);
      u8ModbusADU[u8ModbusADUSize++] = highByte(u16QtyRead);
      u8ModbusADU[u8ModbusADUSize++] = lowByte(u16QtyRead);
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
      u8ModbusADU[u8ModbusADUSize++] = highByte(u16WriteAddress);
      u8ModbusADU[u8ModbusADUSize++] = lowByte(u16WriteAddress);
      break;
  }
  
  switch(u8MBFunction)
  {
    case ku8MBWriteSingleCoil:
      u8ModbusADU[u8ModbusADUSize++] = highByte(u16QtyWrite);
      u8ModbusADU[u8ModbusADUSize++] = lowByte(u16QtyWrite);
      break;
      
    case ku8MBWriteSingleRegister:
      u8ModbusADU[u8ModbusADUSize++] = highByte(u16WriteRegister[lowByte(u16QtyWrite)]);
      u8ModbusADU[u8ModbusADUSize++] = lowByte(u16WriteRegister[lowByte(u16QtyWrite)]);
      break;
      
    case ku8MBWriteMultipleCoils:
      u8ModbusADU[u8ModbusADUSize++] = highByte(u16QtyWrite);
      u8ModbusADU[u8ModbusADUSize++] = lowByte(u16QtyWrite);
      u8Qty = (u16QtyWrite % 8) ? ((u16QtyWrite >> 3) + 1) : (u16QtyWrite >> 3);
      u8ModbusADU[u8ModbusADUSize++] = u8Qty;
      for (i = 0; i < u8Qty; i++)
      {
        switch(i % 2)
        {
          case 0: // i is even
            u8ModbusADU[u8ModbusADUSize++] = lowByte(u16WriteRegister[i >> 1]);
            break;
            
          case 1: // i is odd
            u8ModbusADU[u8ModbusADUSize++] = highByte(u16WriteRegister[i >> 1]);
            break;
        }
      }
      break;
      
    case ku8MBWriteMultipleRegisters:
    case ku8MBReadWriteMultipleRegisters:
      u8ModbusADU[u8ModbusADUSize++] = highByte(u16QtyWrite);
      u8ModbusADU[u8ModbusADUSize++] = lowByte(u16QtyWrite);
      u8ModbusADU[u8ModbusADUSize++] = lowByte(u16QtyWrite << 1);
      
      for (i = 0; i < lowByte(u16QtyWrite); i++)
      {
        u8ModbusADU[u8ModbusADUSize++] = highByte(u16WriteRegister[i]);
        u8ModbusADU[u8ModbusADUSize++] = lowByte(u16WriteRegister[i]);
      }
      break;
      
    case ku8MBMaskWriteRegister:
      u8ModbusADU[u8ModbusADUSize++] = highByte(u16WriteRegister[0]);
      u8ModbusADU[u8ModbusADUSize++] = lowByte(u16WriteRegister[0]);
      u8ModbusADU[u8ModbusADUSize++] = highByte(u16WriteRegister[1]);
      u8ModbusADU[u8ModbusADUSize++] = lowByte(u16WriteRegister[1]);
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
  
  // verify correct request size -- is this the correct size???
  if (u8ModbusADUSize > 254)
  {
    u8Status = ku8MBInvalidRequestADUSize;
  }
  
  // transmit request
  for (i = 0; i < u8ModbusADUSize; i++)
  {
    Serial.print(u8ModbusADU[i], BYTE);
  }
  
  u8ModbusADUSize = 0;
  Serial.flush();
  
  while (u8TimeLeft && u8BytesLeft && !u8Status)
  {
    if (Serial.available())
    {
#if MODBUSMASTER_DEBUG
      digitalWrite(4, true);
#endif
      u8ModbusADU[u8ModbusADUSize++] = Serial.read();
      u8BytesLeft--;
#if MODBUSMASTER_DEBUG
      digitalWrite(4, false);
#endif
      
      // will be able to remove this due to u8BytesLeft
      if (u8ModbusADUSize >= 0xFF)
      {
        u8Status = ku8MBInvalidResponseADUSize;
        break;
      }
    }
    else
    {
#if MODBUSMASTER_DEBUG
      digitalWrite(5, true);
#endif
      delayMicroseconds(1000);
      u8TimeLeft--;
#if MODBUSMASTER_DEBUG
      digitalWrite(5, false);
#endif
    }
    
    // evaluate slave ID, function code once enough bytes have been read
    if (u8ModbusADUSize == 5)
    {
      // verify response is for correct Modbus slave
      if (u8ModbusADU[0] != u8MBSlave)
      {
        u8Status = ku8MBInvalidSlaveID;
        break;
      }
      
      // verify response is for correct Modbus function code (mask exception bit 7)
      if ((u8ModbusADU[1] & 0x7F) != u8MBFunction)
      {
        u8Status = ku8MBInvalidFunction;
        break;
      }
      
      // check whether Modbus exception occurred; return Modbus Exception Code
      if (bitRead(u8ModbusADU[1], 7))
      {
        u8Status = u8ModbusADU[2];
        break;
      }
      
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
  if (!u8Status && (u8TimeLeft == 0 || u8ModbusADUSize < 5))
  {
    u8Status = ku8MBResponseTimedOut;
  }
  
  // calculate CRC
  u16CRC = 0xFFFF;
  for (i = 0; i < (u8ModbusADUSize - 2); i++)
  {
    u16CRC = _crc16_update(u16CRC, u8ModbusADU[i]);
  }
  
  // verify CRC
  if (!u8Status && (lowByte(u16CRC) != u8ModbusADU[u8ModbusADUSize - 2] ||
    highByte(u16CRC) != u8ModbusADU[u8ModbusADUSize - 1]))
  {
    u8Status = ku8MBInvalidCRC;
  }

  // disassemble ADU into words
  if (!u8Status)
  {
    switch(u8ModbusADU[1])
    {
      case ku8MBReadCoils:
      case ku8MBReadDiscreteInputs:
        // load bytes into word; response bytes are ordered L, H, L, H, ...
        for (i = 0; i < (u8ModbusADU[2] >> 1); i++)
        {
          u16ReadRegister[i] = word(u8ModbusADU[2 * i + 4], u8ModbusADU[2 * i + 3]);
        }
        
        // in the event of an odd number of bytes, load last byte into zero-padded word
        if (u8ModbusADU[2] % 2)
        {
          u16ReadRegister[i] = word(0, u8ModbusADU[2 * i + 3]);
        }
        break;
        
      case ku8MBReadInputRegisters:
      case ku8MBReadHoldingRegisters:
      case ku8MBReadWriteMultipleRegisters:
        // load bytes into word; response bytes are ordered H, L, H, L, ...
        for (i = 0; i < (u8ModbusADU[2] >> 1); i++)
        {
          u16ReadRegister[i] = word(u8ModbusADU[2 * i + 3], u8ModbusADU[2 * i + 4]);
        }
        break;
    }
  }
  
  return u8Status;
}
