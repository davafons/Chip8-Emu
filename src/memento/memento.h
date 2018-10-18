#pragma once

#include "cpu/cpu.h"
#include "memory/memory.h"

class Memento {
private:
  friend class SaveStateManager;

  explicit Memento(const Cpu &cpu, const Memory &memory)
      : cpu_(cpu), memory_(memory) {}

  void setCpu(const Cpu &cpu) { cpu_ = cpu; }
  Cpu getCpu() const { return cpu_; }
  void setMemory(const Memory &memory) { memory_ = memory; }
  Memory getMemory() const { return memory_; }

private:
  Cpu cpu_;
  Memory memory_;
};
