/*
  Basic.pde - example using ModbusMaster library
  
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

// instantiate ModbusMaster object as slave ID 2
// defaults to serial port 0 since no port was specified
ModbusMaster node(2);


void setup()
{
  // initialize Modbus communication baud rate
  node.begin(19200);
}


void loop()
{
  static uint32_t i;
  uint8_t result;
  
  i++;
  
  node.TX(0, lowWord(i));
  node.TX(1, highWord(i));
  
  // slave 1: write TX to (2) 16-bit registers starting at register 0
  result = node.WriteMultipleRegisters(0, 2);
  
  // slave 1: read (6) 16-bit registers starting at register 2 to RX
  result = node.ReadHoldingRegisters(2, 6);
}

