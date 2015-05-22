ModbusMaster
============
[![GitHub tag](https://img.shields.io/github/tag/4-20ma/ModbusMaster.svg)][GitHub tag]
[![GitHub license](https://img.shields.io/github/license/4-20ma/ModbusMaster.svg)][GitHub license]

[GitHub tag]:     https://github.com/4-20ma/ModbusMaster
[GitHub license]: COPYING

Overview
--------
This is an Arduino library for communicating with Modbus slaves over RS232/485 (via RTU protocol). **Updated to support Arduino 1.6.**


Features
--------
The following Modbus functions have been implemented:

Discrete Coils/Flags

  * 0x01 - Read Coils
  * 0x02 - Read Discrete Inputs
  * 0x05 - Write Single Coil
  * 0x0F - Write Multiple Coils

Registers

  * 0x03 - Read Holding Registers
  * 0x04 - Read Input Registers
  * 0x06 - Write Single Register
  * 0x10 - Write Multiple Registers
  * 0x16 - Mask Write Register
  * 0x17 - Read Write Multiple Registers


Uploading Sketches
------------------
Arduinos prior to the Mega have one serial port which must be connected to USB (FTDI) for uploading sketches and to the RS232/485 device/network for running sketches. You will need to disconnect pin 0 (RX) while uploading sketches. After a successful upload, you can reconnect pin 0.


Hardware
--------
This library has been tested with an Arduino [Duemilanove](http://www.arduino.cc/en/Main/ArduinoBoardDuemilanove), PHOENIX CONTACT [nanoLine](https://www.phoenixcontact.com/online/portal/us?1dmy&urile=wcm%3apath%3a/usen/web/main/products/subcategory_pages/standard_logic_modules_p-21-03-03/3329dd38-7c6a-46e1-8260-b9208235d6fe/3329dd38-7c6a-46e1-8260-b9208235d6fe) controller, connected via RS485 using a Maxim [MAX488EPA](http://www.maxim-ic.com/quick_view2.cfm/qv_pk/1111) transceiver.


Installation
------------
* Arduino 17 (or later):

  Determine the location of your sketchbook by selecting _File > Preferences_ from within the Arduino IDE. If you don't already have a _libraries_ folder within your sketchbook, create one and unzip the archive there. See [this](http://arduino.cc/blog/?p=313) for more information.

* Arduino 16 (or earlier):

  Download the zip file, extract and copy the _ModbusMaster_ folder to _ARDUINO\_HOME/hardware/libraries_. If you are upgrading from a previous version, be sure to delete ModbusMaster.o.


Support
-------
Please report any bugs on the [Issue Tracker](https://github.com/4-20ma/ModbusMaster/issues).


Questions/Feedback
------------------
I can be contacted at 4-20ma at wvfans dot net.


Example
-------
The library contains a few sketches that demonstrate use of the ModbusMaster library. You can find these in the [examples](https://github.com/4-20ma/ModbusMaster/tree/master/examples) folder.

```c++
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
  Copyright © 2009-2013 Doc Walker <4-20ma at wvfans dot net>

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
  uint8_t j, result;
  uint16_t data[6];

  i++;

  // set word 0 of TX buffer to least-significant word of counter (bits 15..0)
  node.setTransmitBuffer(0, lowWord(i));

  // set word 1 of TX buffer to most-significant word of counter (bits 31..16)
  node.setTransmitBuffer(1, highWord(i));

  // slave: write TX buffer to (2) 16-bit registers starting at register 0
  result = node.writeMultipleRegisters(0, 2);

  // slave: read (6) 16-bit registers starting at register 2 to RX buffer
  result = node.readHoldingRegisters(2, 6);

  // do something with data if read is successful
  if (result == node.ku8MBSuccess)
  {
    for (j = 0; j < 6; j++)
    {
      data[j] = node.getResponseBuffer(j);
    }
  }
}
```

_Project inspired by [Arduino Modbus Master](http://sites.google.com/site/jpmzometa/arduino-mbrt/arduino-modbus-master)._
