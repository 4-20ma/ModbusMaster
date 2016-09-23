# ModbusMaster
[![GitHub release](https://img.shields.io/github/release/4-20ma/ModbusMaster.svg?maxAge=3600)][GitHub release]
[![Travis](https://img.shields.io/travis/4-20ma/ModbusMaster.svg?maxAge=3600)][Travis]
[![license](https://img.shields.io/github/license/4-20ma/ModbusMaster.svg?maxAge=3600)][license]
[![code of conduct](https://img.shields.io/badge/%E2%9D%A4-code%20of%20conduct-blue.svg?maxAge=3600)][code of conduct]

[GitHub release]:   https://github.com/4-20ma/ModbusMaster
[Travis]:           https://travis-ci.org/4-20ma/ModbusMaster
[license]:          LICENSE
[code of conduct]:  CODE_OF_CONDUCT.md


## Overview
This is an Arduino library for communicating with Modbus slaves over RS232/485 (via RTU protocol).


## Features
The following Modbus functions are available:

Discrete Coils/Flags

  - 0x01 - Read Coils
  - 0x02 - Read Discrete Inputs
  - 0x05 - Write Single Coil
  - 0x0F - Write Multiple Coils

Registers

  - 0x03 - Read Holding Registers
  - 0x04 - Read Input Registers
  - 0x06 - Write Single Register
  - 0x10 - Write Multiple Registers
  - 0x16 - Mask Write Register
  - 0x17 - Read Write Multiple Registers

Both full-duplex and half-duplex RS232/485 transceivers are supported. Callback functions are provided to toggle Data Enable (DE) and Receiver Enable (/RE) pins.


## Installation

#### Library Manager
Install the library into your Arduino IDE using the Library Manager (available from IDE version 1.6.2). Open the IDE and click Sketch > Include Library > Manage Libraries&hellip;

Scroll or search for `ModbusMaster`, then select the version of the library you want to install. Quit/re-launch the IDE to refresh the list; new versions are automatically added to the list, once released on GitHub.

Refer to Arduino Tutorials > Libraries [Using the Library Manager](https://www.arduino.cc/en/Guide/Libraries#toc3).

#### Zip Library
Refer to Arduino Tutorials > Libraries [Importing a .zip Library](https://www.arduino.cc/en/Guide/Libraries#toc4).

#### Manual
Refer to Arduino Tutorials > Libraries [Manual Installation](https://www.arduino.cc/en/Guide/Libraries#toc5).


## Hardware
This library has been tested with an Arduino [Duemilanove](http://www.arduino.cc/en/Main/ArduinoBoardDuemilanove), PHOENIX CONTACT [nanoLine](https://www.phoenixcontact.com/online/portal/us?1dmy&urile=wcm%3apath%3a/usen/web/main/products/subcategory_pages/standard_logic_modules_p-21-03-03/3329dd38-7c6a-46e1-8260-b9208235d6fe/3329dd38-7c6a-46e1-8260-b9208235d6fe) controller, connected via RS485 using a Maxim [MAX488EPA](http://www.maxim-ic.com/quick_view2.cfm/qv_pk/1111) transceiver.


## Caveats
Conforms to Arduino IDE 1.5 Library Specification v2.1 which requires Arduino IDE >= 1.5.

Arduinos prior to the Mega have one serial port which must be connected to USB (FTDI) for uploading sketches and to the RS232/485 device/network for running sketches. You will need to disconnect pin 0 (RX) while uploading sketches. After a successful upload, you can reconnect pin 0.


## Support
Please [submit an issue](https://github.com/4-20ma/ModbusMaster/issues) for all questions, bug reports, and feature requests. Email requests will be politely redirected to the issue tracker so others may contribute to the discussion and requestors get a more timely response.


## Example
The library contains a few sketches that demonstrate use of the `ModbusMaster` library. You can find these in the [examples](https://github.com/4-20ma/ModbusMaster/tree/master/examples) folder.

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
