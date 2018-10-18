#pragma once

#include <cstddef>
#include <vector>

class Cpu;
class Memory;
class Memento;

class SaveStateManager {
public:
  explicit SaveStateManager(Cpu &active_cpu, Memory &active_memory);

  void saveState(size_t i);
  void loadState(size_t i);

private:
  static std::vector<Memento> save_states_;

  Cpu &active_cpu_;
  Memory &active_memory_;
};
