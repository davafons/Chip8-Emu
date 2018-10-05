#pragma once

#include <memory>

#include "timer.h"

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
  std::unique_ptr<ImplChip8> impl_;

  Timer timer_;
};
