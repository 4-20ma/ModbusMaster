/*
  PhoenixContact_nanoLC.pde - example using ModbusMaster library
  
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

#include <ModbusMaster.h>

// discrete coils
#define NANO_DO(n)   (0x0000 + n)
#define NANO_FLAG(n) (0x1000 + n)

// discrete inputs
#define NANO_DI(n)   (0x0000 + n)

// analog holding registers
#define NANO_REG(n)  (0x0000 + 2 * n)
#define NANO_AO(n)   (0x1000 + 2 * n)
#define NANO_TCP(n)  (0x2000 + 2 * n)
#define NANO_OTP(n)  (0x3000 + 2 * n)
#define NANO_HSP(n)  (0x4000 + 2 * n)
#define NANO_TCA(n)  (0x5000 + 2 * n)
#define NANO_OTA(n)  (0x6000 + 2 * n)
#define NANO_HSA(n)  (0x7000 + 2 * n)

// analog input registers
#define NANO_AI(n)   (0x0000 + 2 * n)

// instantiate ModbusMaster object using serial port 0 and slave ID 1
ModbusMaster nanoLC(0, 1);


void setup()
{
  // initialize Modbus communication baud rate
  nanoLC.begin(19200);
}


void loop()
{
  static uint32_t u32ShiftRegister;
  static uint32_t i;
  uint8_t u8Status;
  
  u32ShiftRegister = ((u32ShiftRegister < 0x01000000) ? (u32ShiftRegister << 4) : 1);
  if (u32ShiftRegister == 0) u32ShiftRegister = 1;
  i++;
  
  // set word 0 of TX to least-significant word of u32ShiftRegister (bits 15..0)
  nanoLC.TX(0, lowWord(u32ShiftRegister));
  
  // set word 1 of TX to most-significant word of u32ShiftRegister (bits 31..16)
  nanoLC.TX(1, highWord(u32ShiftRegister));
  
  // set word 2 of TX to least-significant word of i (bits 15..0)
  nanoLC.TX(2, lowWord(i));
  
  // set word 3 of TX to most-significant word of i (bits 31..16)
  nanoLC.TX(3, highWord(i));
  
  // write TX to (4) 16-bit registers starting at NANO_REG(1)
  // read (4) 16-bit registers starting at NANO_REG(0) to RX
  // data is available via nanoLC.RX(0..3)
  nanoLC.ReadWriteMultipleRegisters(NANO_REG(0), 4, NANO_REG(1), 4);
  
  // write lowWord(u32ShiftRegister) to single 16-bit register starting at NANO_REG(3)
  nanoLC.WriteSingleRegister(NANO_REG(3), lowWord(u32ShiftRegister));
  
  // write highWord(u32ShiftRegister) to single 16-bit register starting at NANO_REG(3) + 1
  nanoLC.WriteSingleRegister(NANO_REG(3) + 1, highWord(u32ShiftRegister));
  
  // set word 0 of TX to nanoLC.RX(0) (bits 15..0)
  nanoLC.TX(0, nanoLC.RX(0));
  
  // set word 1 of TX to nanoLC.RX(1) (bits 31..16)
  nanoLC.TX(1, nanoLC.RX(1));
  
  // write TX to (2) 16-bit registers starting at NANO_REG(4)
  nanoLC.WriteMultipleRegisters(NANO_REG(4), 2);
  
  // read 17 coils starting at NANO_FLAG(0) to RX
  // bits 15..0 are available via nanoLC.RX(0)
  // bit 16 is available via zero-padded nanoLC.RX(1)
  nanoLC.ReadCoils(NANO_FLAG(0), 17);
  
  // read (66) 16-bit registers starting at NANO_REG(0) to RX
  // generates Modbus exception ku8MBIllegalDataAddress (0x02)
  u8Status = nanoLC.ReadHoldingRegisters(NANO_REG(0), 66);
  if (u8Status == nanoLC.ku8MBIllegalDataAddress)
  {
    // read (64) 16-bit registers starting at NANO_REG(0) to RX
    // data is available via nanoLC.RX(0..63)
    u8Status = nanoLC.ReadHoldingRegisters(NANO_REG(0), 64);
  }
  
  // read (8) 16-bit registers starting at NANO_AO(0) to RX
  // data is available via nanoLC.RX(0..7)
  nanoLC.ReadHoldingRegisters(NANO_AO(0), 8);
  
  // read (64) 16-bit registers starting at NANO_TCP(0) to RX
  // data is available via nanoLC.RX(0..63)
  nanoLC.ReadHoldingRegisters(NANO_TCP(0), 64);
  
  // read (64) 16-bit registers starting at NANO_OTP(0) to RX
  // data is available via nanoLC.RX(0..63)
  nanoLC.ReadHoldingRegisters(NANO_OTP(0), 64);
  
  // read (64) 16-bit registers starting at NANO_TCA(0) to RX
  // data is available via nanoLC.RX(0..63)
  nanoLC.ReadHoldingRegisters(NANO_TCA(0), 64);
  
  // read (64) 16-bit registers starting at NANO_OTA(0) to RX
  // data is available via nanoLC.RX(0..63)
  nanoLC.ReadHoldingRegisters(NANO_OTA(0), 64);
  
  // read (8) 16-bit registers starting at NANO_AI(0) to RX
  // data is available via nanoLC.RX(0..7)
  nanoLC.ReadInputRegisters(NANO_AI(0), 8);
}
