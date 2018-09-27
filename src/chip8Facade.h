#pragma once

#include <string>

#include "input.h"
#include "memory.h"

class Chip8Facade {
public:
  explicit Chip8Facade(const std::string &path = "");
  void loadROM(const std::string &path);
  void execute();

private:
  bool quit_{false};
  bool loaded_{false};

  Memory memory_;
  Input input_{memory_, quit_};
};
