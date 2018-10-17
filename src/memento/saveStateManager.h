#pragma once

#include <vector>
#include <cstddef>

class Memory;
class Memento;

class SaveStateManager {
public:
  explicit SaveStateManager(Memory &memory);

  void saveState(size_t i);
  void loadState(size_t i);

private:
  static std::vector<Memento> save_states_;

  Memory &memory_;
};
