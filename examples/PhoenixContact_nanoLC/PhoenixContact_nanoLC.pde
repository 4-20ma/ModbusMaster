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

// instantiate ModbusMaster object
ModbusMaster rs485;


void setup()
{
  // initialize Modbus communication baud rate
  rs485.begin(19200);
}


void loop()
{
  static uint8_t u8NanoLC = 1;
  static uint32_t u32ShiftRegister;
  static uint32_t i;
  static uint16_t u16DataIn[64];
  static uint16_t u16DataOut[64];
  uint8_t result;
  
  u32ShiftRegister = ((u32ShiftRegister < 0x01000000) ? (u32ShiftRegister << 4) : 1);
  if (u32ShiftRegister == 0) u32ShiftRegister = 1;
  i++;
  
  u16DataOut[0] = lowWord(u32ShiftRegister);
  u16DataOut[1] = highWord(u32ShiftRegister);
  u16DataOut[2] = lowWord(i);
  u16DataOut[3] = highWord(i);
  
  // write u16DataOut to (4) 16-bit registers starting at NANO_REG(1)
  // read (4) 16-bit registers starting at NANO_REG(0) to u16DataIn
  rs485.u8ReadWriteMultipleRegisters(u8NanoLC, NANO_REG(0), 4, u16DataIn, NANO_REG(1), 4, u16DataOut);
  
  // write lowWord(u32ShiftRegister) to single 16-bit register starting at NANO_REG(3)
  rs485.u8WriteSingleRegister(u8NanoLC, NANO_REG(3), lowWord(u32ShiftRegister));
  
  // write highWord(u32ShiftRegister) to single 16-bit register starting at NANO_REG(3) + 1
  rs485.u8WriteSingleRegister(u8NanoLC, NANO_REG(3) + 1, highWord(u32ShiftRegister));
  
  // write u16DataIn to (2) 16-bit registers starting at NANO_REG(4)
  rs485.u8WriteMultipleRegisters(u8NanoLC, NANO_REG(4), 2, u16DataIn);
  
  // read 17 coils starting at NANO_FLAG(0) to u16DataIn
  rs485.u8ReadCoils(u8NanoLC, NANO_FLAG(0), 17, u16DataIn);
  
  // read (66) 16-bit registers starting at NANO_REG(0) to u16DataIn
  // generates Modbus exception ku8MBIllegalDataAddress (0x02)
  result = rs485.u8ReadHoldingRegisters(u8NanoLC, NANO_REG(0), 66, u16DataIn);
  if (result == ku8MBIllegalDataAddress)
  {
    // read (64) 16-bit registers starting at NANO_REG(0) to u16DataIn
    result = rs485.u8ReadHoldingRegisters(u8NanoLC, NANO_REG(0), 64, u16DataIn);
  }
  
  // read (8) 16-bit registers starting at NANO_AO(0) to u16DataIn
  rs485.u8ReadHoldingRegisters(u8NanoLC, NANO_AO(0), 8, u16DataIn);
  
  // read (64) 16-bit registers starting at NANO_TCP(0) to u16DataIn
  rs485.u8ReadHoldingRegisters(u8NanoLC, NANO_TCP(0), 64, u16DataIn);
  
  // read (64) 16-bit registers starting at NANO_OTP(0) to u16DataIn
  rs485.u8ReadHoldingRegisters(u8NanoLC, NANO_OTP(0), 64, u16DataIn);
  
  // read (64) 16-bit registers starting at NANO_TCA(0) to u16DataIn
  rs485.u8ReadHoldingRegisters(u8NanoLC, NANO_TCA(0), 64, u16DataIn);
  
  // read (64) 16-bit registers starting at NANO_OTA(0) to u16DataIn
  rs485.u8ReadHoldingRegisters(u8NanoLC, NANO_OTA(0), 64, u16DataIn);
  
  // read (8) 16-bit registers starting at NANO_AI(0) to u16DataIn
  rs485.u8ReadInputRegisters(u8NanoLC, NANO_AI(0), 8, u16DataIn);
}

