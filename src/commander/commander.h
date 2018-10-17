#pragma once

#include <cstddef>
#include <string>

#include "memento/saveStateManager.h"

class Cpu;
class Memory;

class Commander {
public:
  Commander(Cpu &cpu, Memory &memory, bool &quit);

  // General
  void exit();
  void reset();

  // Memory
  void loadRom(const std::string &rom_path);
  void keyDown(size_t i);
  void keyUp(size_t i);

  // Cpu
  void togglePause();
  void doubleSpeed();
  void halfSpeed();

  // Save States
  void saveState(size_t i);
  void loadState(size_t i);

private:
  Cpu &cpu_;
  Memory &memory_;

  bool &quit_;

  SaveStateManager ssmanager_{memory_};
};
