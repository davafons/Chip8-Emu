#pragma once

#include "memory/memory.h"

class Memento {
public:
  explicit Memento(const Memory &memory) : memory_(memory) {}

  void setMemory(const Memory &memory) { memory_ = memory; }
  Memory getMemory() const { return memory_; }

private:
  Memory memory_;
};
