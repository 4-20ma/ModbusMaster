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

// instantiate ModbusMaster object as slave ID 1
ModbusMaster nanoLC(1);


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
  
  nanoLC.SetSource(0, lowWord(u32ShiftRegister));
  nanoLC.SetSource(1, highWord(u32ShiftRegister));
  nanoLC.SetSource(2, lowWord(i));
  nanoLC.SetSource(3, highWord(i));
  
  // write source to (4) 16-bit registers starting at NANO_REG(1)
  // read (4) 16-bit registers starting at NANO_REG(0) to result
  nanoLC.ReadWriteMultipleRegisters(NANO_REG(0), 4, NANO_REG(1), 4);
  
  // write lowWord(u32ShiftRegister) to single 16-bit register starting at NANO_REG(3)
  nanoLC.WriteSingleRegister(NANO_REG(3), lowWord(u32ShiftRegister));
  
  // write highWord(u32ShiftRegister) to single 16-bit register starting at NANO_REG(3) + 1
  nanoLC.WriteSingleRegister(NANO_REG(3) + 1, highWord(u32ShiftRegister));
  
  // write source to (2) 16-bit registers starting at NANO_REG(4)
  nanoLC.SetSource(0, nanoLC.u16GetResult(0));
  nanoLC.SetSource(1, nanoLC.u16GetResult(1));
  nanoLC.WriteMultipleRegisters(NANO_REG(4), 2);
  
  // read 17 coils starting at NANO_FLAG(0) to result
  nanoLC.ReadCoils(NANO_FLAG(0), 17);
  
  // read (66) 16-bit registers starting at NANO_REG(0) to result
  // generates Modbus exception ku8MBIllegalDataAddress (0x02)
  u8Status = nanoLC.ReadHoldingRegisters(NANO_REG(0), 66);
  if (u8Status == nanoLC.ku8MBIllegalDataAddress)
  {
    // read (64) 16-bit registers starting at NANO_REG(0) to result
    u8Status = nanoLC.ReadHoldingRegisters(NANO_REG(0), 64);
  }
  
  // read (8) 16-bit registers starting at NANO_AO(0) to result
  nanoLC.ReadHoldingRegisters(NANO_AO(0), 8);
  
  // read (64) 16-bit registers starting at NANO_TCP(0) to result
  nanoLC.ReadHoldingRegisters(NANO_TCP(0), 64);
  
  // read (64) 16-bit registers starting at NANO_OTP(0) to result
  nanoLC.ReadHoldingRegisters(NANO_OTP(0), 64);
  
  // read (64) 16-bit registers starting at NANO_TCA(0) to result
  nanoLC.ReadHoldingRegisters(NANO_TCA(0), 64);
  
  // read (64) 16-bit registers starting at NANO_OTA(0) to result
  nanoLC.ReadHoldingRegisters(NANO_OTA(0), 64);
  
  // read (8) 16-bit registers starting at NANO_AI(0) to result
  nanoLC.ReadInputRegisters(NANO_AI(0), 8);
}
