#pragma once

#include <memory>

class Memory;

class Cpu {
public:
  explicit Cpu(Memory &memory);
  ~Cpu();
  Cpu(const Cpu &) = delete;
  Cpu &operator=(const Cpu &) = delete;

  void cycle();

  bool mustDraw() const;
  bool mustSound() const;

private:
  class ImplChip8;
  ImplChip8 * impl_;
};
