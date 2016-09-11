# ModbusMaster
[![Tag](https://img.shields.io/github/tag/4-20ma/ModbusMaster.svg)][Tag]
[![Travis](https://img.shields.io/travis/4-20ma/ModbusMaster.svg)][Travis]
[![License](https://img.shields.io/github/license/4-20ma/ModbusMaster.svg)][License]
[![Code of conduct](https://img.shields.io/badge/%E2%9D%A4-code%20of%20conduct-blue.svg)][Code of conduct]

[Tag]:              https://github.com/4-20ma/ModbusMaster
[Travis]:           https://travis-ci.org/4-20ma/ModbusMaster
[License]:          LICENSE
[Code of conduct]:  https://github.com/4-20ma/ModbusMaster/blob/master/CODE_OF_CONDUCT.md


## Overview
This is an Arduino library for communicating with Modbus slaves over RS232/485 (via RTU protocol). **Updated to support Arduino 1.6.**


## Features
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


## Uploading Sketches
Arduinos prior to the Mega have one serial port which must be connected to USB (FTDI) for uploading sketches and to the RS232/485 device/network for running sketches. You will need to disconnect pin 0 (RX) while uploading sketches. After a successful upload, you can reconnect pin 0.


## Hardware
This library has been tested with an Arduino [Duemilanove](http://www.arduino.cc/en/Main/ArduinoBoardDuemilanove), PHOENIX CONTACT [nanoLine](https://www.phoenixcontact.com/online/portal/us?1dmy&urile=wcm%3apath%3a/usen/web/main/products/subcategory_pages/standard_logic_modules_p-21-03-03/3329dd38-7c6a-46e1-8260-b9208235d6fe/3329dd38-7c6a-46e1-8260-b9208235d6fe) controller, connected via RS485 using a Maxim [MAX488EPA](http://www.maxim-ic.com/quick_view2.cfm/qv_pk/1111) transceiver.


## Installation
* Arduino 17 (or later):

  Determine the location of your sketchbook by selecting _File > Preferences_ from within the Arduino IDE. If you don't already have a _libraries_ folder within your sketchbook, create one and unzip the archive there. See [this](http://arduino.cc/blog/?p=313) for more information.

* Arduino 16 (or earlier):

  Download the zip file, extract and copy the _ModbusMaster_ folder to _ARDUINO\_HOME/hardware/libraries_. If you are upgrading from a previous version, be sure to delete ModbusMaster.o.


## Support
Please [submit an issue](https://github.com/4-20ma/ModbusMaster/issues) for all questions, bug reports, and feature requests. Email requests will be politely redirected to the issue tracker so others may contribute to the discussion and requestors get a more timely response.


## Example
The library contains a few sketches that demonstrate use of the ModbusMaster library. You can find these in the [examples](https://github.com/4-20ma/ModbusMaster/tree/master/examples) folder.

``` cpp
/*

  Basic.pde - example using ModbusMaster library

  Library:: ModbusMaster
  Author:: Doc Walker <4-20ma@wvfans.net>

  Copyright:: 2009-2016 Doc Walker

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

*/

#include <ModbusMaster.h>


// instantiate ModbusMaster object
ModbusMaster node;


void setup()
{
  // use Serial (port 0); initialize Modbus communication baud rate
  Serial.begin(19200);

  // communicate with Modbus slave ID 2 over Serial (port 0)
  node.begin(2, Serial);
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


## License & Authors

- Author:: Doc Walker ([4-20ma@wvfans.net](mailto:4-20ma@wvfans.net))
- Author:: Ag Primatic ([agprimatic@gmail.com](mailto:agprimatic@gmail.com))
- Author:: Marius Kintel ([marius@kintel.net](mailto:marius@kintel.net))

```
Copyright:: 2009-2016 Doc Walker

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
```
