#pragma once

#include <array>
#include <chrono>
#include <functional>
#include <unordered_map>

#include "cpu/cpu.h"
#include "cpu/opcode.h"

class Memory;

class Cpu::ImplChip8 {
public:
  explicit ImplChip8(Memory &memory);
  void reset();

  void fetch();
  void execute();
  void updateTimers();
  void resetFlags();
  void delay();

  bool mustDraw() const { return draw_; }
  bool mustSound() const { return sound_; }

private:
  //// Chip8 Instruction Set
  void CLS();        // 00E0 - CLS
  void RET();        // 00EE - RET
  void JP_addr();    // 1nnn - JP addr
  void CALL();       // 2nnn - CALL addr
  void SE_byte();    // 3xkk - SE Vx, byte
  void SNE_byte();   // 4xkk - SNE Vx, byte
  void SE_reg();     // 5xy0 - SE Vx, Vy
  void LD_byte();    // 6xkk - LD Vx, byte
  void ADD_byte();   // 7xkk - ADD Vx, byte
  void LD_reg();     // 8xy0 - LD Vx, Vy
  void OR();         // 8xy1 - OR Vx, Vy
  void AND();        // 8xy2 - AND Vx, Vy
  void XOR();        // 8xy3 - XOR Vx, Vy
  void ADD_reg();    // 8xy4 - ADD Vx, Vy
  void SUB();        // 8xy5 - SUB Vx, Vy
  void SHR();        // 8xy6 - SHR Vx {, Vy}
  void SUBN();       // 8xy7 - SUBN Vx, Vy
  void SHL();        // 8xyE - SHL Vx {, Vy}
  void SNE_reg();    // 9xy0 - SNE Vx, Vy
  void LD_I();       // Annn - LD I, addr
  void JP_reg();     // Bnnn - JP V0, addr
  void RND();        // Cxkk - RND Vx, byte
  void DRW();        // Dxyn - DRW Vx, Vy, nibble
  void SKP();        // Ex9E - SKP Vx
  void SKNP();       // ExA1 - SKNP Vx
  void LD_reg_dt();  // Fx07 - LD Vx, DT
  void LD_key();     // Fx0A - LD Vx, K
  void LD_dt_reg();  // Fx15 - LD DT, Vx
  void LD_st_reg();  // Fx18 - LD ST, Vx
  void ADD_I_reg();  // Fx1E - ADD I, Vx
  void LD_sprite();  // Fx29 - LD F, Vx
  void LD_B_reg();   // Fx33 - LD B, Vx
  void LD_ram_reg(); // Fx55 - LD [I], Vx
  void LD_reg_ram(); // Fx65 - LD Vx, [I]

private:
  Memory &mem_; // ram, display and keys

  Opcode opcode_; // Current instruction being executed

  std::array<uint8_t, 16> V_; // General-purpose registers

  uint16_t PC_; // Currently executing address
  uint16_t I_;  // Register for memory addresss

  std::array<uint16_t, 16> stack_;
  uint8_t SP_; // Point to the topmost level of the stack

  uint8_t DT_; // Delay timer register
  uint8_t ST_; // Sound timer register

  bool draw_;  // true if the screen must be updated in this cycle
  bool sound_; // true if the program must emit a sound

  std::chrono::system_clock::time_point now_;
  std::chrono::system_clock::time_point lastFrame_;

  //// Function pointer table
  using InstructionPtr_t = std::function<void(ImplChip8 &)>;
  static const std::unordered_map<uint16_t, InstructionPtr_t> table_;
};
