#include <iostream>

#include "implChip8.h"
#include "memory/memory.h"

#define DEBUG(x) std::cerr << x << std::endl

ImplChip8::ImplChip8(Memory &memory) : mem_(memory) { reset(); }

void ImplChip8::fetch() {
  opcode_ = mem_.readFromRam(PC_) << 8 | mem_.readFromRam(PC_ + 1);
  PC_ += 2;
}

void ImplChip8::execute() {
  Opcode opc; // Only used to determine the instruction
  switch (opcode_.masked(0xF000)) {
  case 0x0000:
    opc = opcode_.masked(0x00FF);
    break;

  case 0x8000:
    opc = opcode_.masked(0xF00F);
    break;

  case 0xE000:
  case 0xF000:
    opc = opcode_.masked(0xF0FF);
    break;

  default:
    opc = opcode_.masked(0xF000);
    break;
  }

  try {
    table_.at(opc)(*this);

  } catch (const std::out_of_range &e) {
    std::cout << "ERROR: Opcode not found: [" << int(opcode_) << "]."
              << std::endl;
    reset();
  }
}

void ImplChip8::reset() {
  std::cerr << " -> Resetting ImplChip8 state..." << std::endl;

  // Clear registers
  PC_ = 0x0200;
  I_ = 0x0000;
  SP_ = 0x00;
  DT_ = 0x00;
  ST_ = 0x00;

  // Clear flags
  draw_ = true;
  sound_ = false;

  // Reset memory
  mem_.reset();
}

void ImplChip8::updateTimers() {
  if (DT_ > 0x00)
    --DT_;

  if (ST_ > 0x00) {
    if (ST_ == 1)
      sound_ = true;
    --ST_;
  }
}

/////////////////////////////////////////////////
//////// Standard Chip-8 Instruction set ////////
/////////////////////////////////////////////////

// 00E0 - CLS - Clear the display.
void ImplChip8::CLS() {
  DEBUG("CLS");
  mem_.clearDisplay();
  draw_ = true;
}

// 00EE - RET - Return from a subroutine.
void ImplChip8::RET() {
  DEBUG("RET");
  --SP_;
  PC_ = stack_[SP_];
}

// 1nnn - JP addr - Jump to location nnn.
void ImplChip8::JP_addr() {
  DEBUG("JP_addr");
  PC_ = opcode_.nnn();
}

// 2nnn - CALL addr - Call subroutine at nnn.
void ImplChip8::CALL() {
  DEBUG("CALL");
  stack_[SP_] = PC_;
  ++SP_;
  PC_ = opcode_.nnn();
}

// 3xkk - SE Vx, byte - Skip next instruction if Vx = kk.
void ImplChip8::SE_byte() {
  DEBUG("SE_byte");
  if (V_[opcode_.x()] == opcode_.kk())
    PC_ += 2;
}

// 4xkk - SNE Vx, byte - Skip next instruction if Vx != kk.
void ImplChip8::SNE_byte() {
  DEBUG("SNE_byte");
  if (V_[opcode_.x()] != opcode_.kk())
    PC_ += 2;
}

// 5xy0 - SE Vx, Vy - Skip next instruction if Vx = Vy.
void ImplChip8::SE_reg() {
  DEBUG("SE_reg");
  if (V_[opcode_.x()] == V_[opcode_.y()])
    PC_ += 2;
}

// 6xkk - LD Vx, byte - Set Vx = kk.
void ImplChip8::LD_byte() {
  DEBUG("LD_byte");
  V_[opcode_.x()] = opcode_.kk();
}

// 7xkk - ADD Vx, byte - Set Vx = Vx + kk.
void ImplChip8::ADD_byte() {
  DEBUG("ADD_byte");
  V_[opcode_.x()] += opcode_.kk();
}

// 8xy0 - LD Vx, Vy - Set Vx = Vy.
void ImplChip8::LD_reg() {
  DEBUG("LD_reg");
  V_[opcode_.x()] = V_[opcode_.y()];
}

// 8xy1 - OR Vx, Vy - Set Vx = Vx OR Vy.
void ImplChip8::OR() {
  DEBUG("OR");
  V_[opcode_.x()] |= V_[opcode_.y()];
}

// 8xy2 - AND Vx, Vy - Set Vx = Vx AND Vy.
void ImplChip8::AND() {
  DEBUG("AND");
  V_[opcode_.x()] &= V_[opcode_.y()];
}

// 8xy3 - XOR Vx, Vy - Set Vx = Vx XOR Vy.
void ImplChip8::XOR() {
  DEBUG("XOR");
  V_[opcode_.x()] ^= V_[opcode_.y()];
}

// 8xy4 - ADD Vx, Vy - Set Vx = Vx + Vy, set VF = carry.
void ImplChip8::ADD_reg() {
  DEBUG("ADD_reg");
  V_[0xF] = (V_[opcode_.y()] > (0xFF - V_[opcode_.x()])) ? 1 : 0;
  V_[opcode_.x()] += V_[opcode_.y()];
}

// 8xy5 - SUB Vx, Vy - Set Vx = Vx - Vy, set VF = NOT borrow.
void ImplChip8::SUB() {
  DEBUG("SUB");
  V_[0xF] = V_[opcode_.y()] > V_[opcode_.x()] ? 0 : 1;
  V_[opcode_.x()] -= V_[opcode_.y()];
}

// 8xy6 - SHR Vx {, Vy} - Set Vx = Vy SHR 1.
void ImplChip8::SHR() {
  DEBUG("SHR");
  V_[0xF] = V_[opcode_.y()] & 0x0001;
  V_[opcode_.x()] = V_[opcode_.y()] >> 1;
}

// 8xy7 - SUBN Vx, Vy - Set Vx = Vy - Vx, set VF = NOT borrow.
void ImplChip8::SUBN() {
  DEBUG("SUBN");
  V_[0xF] = V_[opcode_.x()] > V_[opcode_.y()] ? 0 : 1;
  V_[opcode_.x()] = V_[opcode_.y()] - V_[opcode_.x()];
}

// 8xyE - SHL Vx {, Vy} - Set Vx = Vx SHL 1.
void ImplChip8::SHL() {
  DEBUG("SHL");
  V_[0xF] = V_[opcode_.y()] >> 7;
  V_[opcode_.x()] = V_[opcode_.y()] << 1;
}

// 9xy0 - SNE Vx, Vy - Skip next instruction if Vx != Vy.
void ImplChip8::SNE_reg() {
  DEBUG("SNE_reg");
  if (V_[opcode_.x()] != V_[opcode_.y()])
    PC_ += 2;
}

// Annn - LD I, addr - Set I = nnn.
void ImplChip8::LD_I() {
  DEBUG("LD_I");
  I_ = opcode_.nnn();
}

// Bnnn - JP V0, addr - Jump to location nnn + V0.
void ImplChip8::JP_reg() {
  DEBUG("JP_reg");
  PC_ = opcode_.nnn() + V_[0x0];
}

// Cxkk - RND Vx, byte - Set Vx = random byte AND kk.
void ImplChip8::RND() {
  DEBUG("RND");
  V_[opcode_.x()] = opcode_.kk() & rand();
}

// Dxyn - DRW Vx, Vy, nibble - Display n-byte sprite starting at memory location
// I at {Vx, Vy}, set VF = collision
void ImplChip8::DRW() {
  DEBUG("DRW");
  uint8_t x = V_[opcode_.x()];
  uint8_t y = V_[opcode_.y()];
  uint16_t height = opcode_.n();

  V_[0xF] = 0;
  for (uint8_t yline = 0; yline < height; ++yline) {
    uint8_t pixel = mem_.readFromDisplay(I_ + yline);
    for (uint8_t xline = 0; xline < 8; ++xline) {
      if ((pixel & (0x80 >> xline)) != 0) {
        if (mem_.readFromDisplay((x + xline + ((y + yline) * 64))) == 1)
          V_[0xF] = 1;
        mem_.writeToDisplay((x + xline + ((y + yline) * 64))) ^= 1;
      }
    }
  }
  draw_ = true;
}

// Ex9E - SKP Vx - Skip next instruction if key with the value of Vx is pressed.
void ImplChip8::SKP() {
  DEBUG("SKP");
  if (mem_.readFromKeys(V_[opcode_.x()]) != 0)
    PC_ += 2;
}

// ExA1 - SKNP Vx - Skip next instruction if key with the value of Vx is not
// pressed.
void ImplChip8::SKNP() {
  DEBUG("SKNP");
  if (mem_.readFromKeys(V_[opcode_.x()]) == 0)
    PC_ += 2;
}

// Fx07 - LD Vx, DT - Set Vx = Delay timer value.
void ImplChip8::LD_reg_dt() {
  DEBUG("LD_reg_dt");
  V_[opcode_.x()] = DT_;
}

// Fx0A - LD Vx, K - Wait for a key press, store the value of the key in Vx.
void ImplChip8::LD_key() {
  DEBUG("LD_key");
  bool key_pressed = false;
  for (uint16_t i = 0; i < 16; ++i) {
    if (mem_.readFromKeys(i) != 0) {
      V_[opcode_.x()] = i;
      key_pressed = true;
      break;
    }
  }
  if (!key_pressed)
    PC_ -= 2; // Return to the same instruction
}

// Fx15 - LD DT, Vx - Set delay timer = Vx.
void ImplChip8::LD_dt_reg() {
  DEBUG("LD_dt_reg");
  DT_ = V_[opcode_.x()];
}

// Fx18 - LD ST, Vx - Set sound timer = Vx.
void ImplChip8::LD_st_reg() {
  DEBUG("LD_st_reg");
  ST_ = V_[opcode_.x()];
}

// Fx1E - ADD I, Vx - Set I = I + Vx.
void ImplChip8::ADD_I_reg() {
  DEBUG("ADD_I_reg");
  I_ += V_[opcode_.x()];
}

// Fx29 - LD F, Vx - Set I = location of sprite for digit Vx.
void ImplChip8::LD_sprite() {
  DEBUG("LD_sprite");
  I_ = V_[opcode_.x()] * 0x05;
}

// Fx33 - LD B, Vx - Store BCD representation of Vx in memory locations I, I+1,
// and I+2.
void ImplChip8::LD_B_reg() {
  DEBUG("LD_B_reg");
  mem_.writeToRam(I_) = V_[opcode_.x()] / 100;
  mem_.writeToRam(I_ + 1) = (V_[opcode_.x()] / 10) % 10;
  mem_.writeToRam(I_ + 2) = (V_[opcode_.x()] % 100) % 10;
}

// Fx55 - LD [I], Vx - Store registers V0 through Vx in memory starting at
// location I.
void ImplChip8::LD_ram_reg() {
  DEBUG("LD_ram_reg");
  for (uint16_t i = 0x0000; i <= opcode_.x(); ++i)
    mem_.writeToRam(I_ + i) = V_[i];
}

// Fx65 - LD Vx, [I] - Read registers V0 through Vx from memory starting at
// location I.
void ImplChip8::LD_reg_ram() {
  DEBUG("LD_reg_ram");
  for (uint16_t i = 0x0000; i <= opcode_.x(); ++i)
    V_[i] = mem_.readFromRam(I_ + i);
}

///////// Function pointer table /////////
const std::unordered_map<uint16_t, ImplChip8::InstructionPtr_t>
    ImplChip8::table_ = {
        {0x00E0, &ImplChip8::CLS},        {0x8003, &ImplChip8::XOR},
        {0xE0A1, &ImplChip8::SKNP},       {0x00EE, &ImplChip8::RET},
        {0x8004, &ImplChip8::ADD_reg},    {0xF007, &ImplChip8::LD_reg_dt},
        {0x1000, &ImplChip8::JP_addr},    {0x8005, &ImplChip8::SUB},
        {0xF00A, &ImplChip8::LD_key},     {0x2000, &ImplChip8::CALL},
        {0x8006, &ImplChip8::SHR},        {0xF015, &ImplChip8::LD_dt_reg},
        {0x3000, &ImplChip8::SE_byte},    {0x8007, &ImplChip8::SUBN},
        {0xF018, &ImplChip8::LD_st_reg},  {0x4000, &ImplChip8::SNE_byte},
        {0x800E, &ImplChip8::SHL},        {0xF01E, &ImplChip8::ADD_I_reg},
        {0x5000, &ImplChip8::SE_reg},     {0x9000, &ImplChip8::SNE_reg},
        {0xF029, &ImplChip8::LD_sprite},  {0x6000, &ImplChip8::LD_byte},
        {0xA000, &ImplChip8::LD_I},       {0xF033, &ImplChip8::LD_B_reg},
        {0x7000, &ImplChip8::ADD_byte},   {0xB000, &ImplChip8::JP_reg},
        {0xF055, &ImplChip8::LD_ram_reg}, {0x8000, &ImplChip8::LD_reg},
        {0xC000, &ImplChip8::RND},        {0xF065, &ImplChip8::LD_reg_ram},
        {0x8001, &ImplChip8::OR},         {0xD000, &ImplChip8::DRW},
        {0x8002, &ImplChip8::AND},        {0xE09E, &ImplChip8::SKP},
};
