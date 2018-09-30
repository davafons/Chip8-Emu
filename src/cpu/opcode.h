#pragma once

#include <cstdint>

class Opcode {
public:
  Opcode(uint16_t opcode = 0x0000) : opc_(opcode) {} // Implicit on purpose
  Opcode(const Opcode &rhs) : opc_(rhs.opc_) {}
  Opcode &operator=(const Opcode &rhs) {
    opc_ = rhs.opc_;
    return *this;
  }

  operator uint16_t() const { return opc_; }
  explicit operator int() const { return int(opc_); }

  uint16_t masked(uint16_t mask) const { return opc_ & mask; }
  uint16_t n() const { return opc_ & 0x000F; }
  uint16_t nnn() const { return opc_ & 0x0FFF; }
  uint16_t kk() const { return opc_ & 0x00FF; }
  uint16_t x() const { return (opc_ & 0x0F00) >> 8; }
  uint16_t y() const { return (opc_ & 0x00F0) >> 4; }

private:
  uint16_t opc_;
};
