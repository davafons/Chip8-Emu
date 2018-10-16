#pragma once

#include <string>

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

private:
  Cpu &cpu_;
  Memory &memory_;

  bool &quit_;
};
