#include <ModbusMaster.h>

// instantiate ModbusMaster object
ModbusMaster rs485;


void setup()
{
  // initialize Modbus communication baud rate
  rs485.begin(19200);
}


void loop()
{
  static uint32_t i;
  static uint16_t u16DataIn[6];
  static uint16_t u16DataOut[2];
  uint8_t result;
  
  i++;
  
  u16DataOut[0] = lowWord(i);
  u16DataOut[1] = highWord(i);
  
  // slave 1: write u16DataOut to (2) 16-bit registers starting at register 0
  result = rs485.u8WriteMultipleRegisters(1, 0, 2, u16DataOut);
  
  // slave 1: read (6) 16-bit registers starting at register 2 to u16DataIn
  result = rs485.u8ReadHoldingRegisters(1, 2, 6, u16DataIn);
}

