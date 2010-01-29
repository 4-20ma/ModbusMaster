#include <ModbusMaster.h>

// instantiate ModbusMaster object as slave ID 2
ModbusMaster slave2(2);


void setup()
{
  // initialize Modbus communication baud rate
  slave2.begin(19200);
}


void loop()
{
  static uint32_t i;
  uint8_t result;
  
  i++;
  
  slave2.SetSource(0, lowWord(i));
  slave2.SetSource(1, highWord(i));
  
  // slave 1: write source to (2) 16-bit registers starting at register 0
  result = slave2.WriteMultipleRegisters(0, 2);
  
  // slave 1: read (6) 16-bit registers starting at register 2 to result
  result = slave2.ReadHoldingRegisters(2, 6);
}

