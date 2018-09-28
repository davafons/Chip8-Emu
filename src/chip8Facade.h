#pragma once

#include <string>

#include "memory/memory.h"

class Input;
class Display;

// INLINE

class Chip8Facade {
public:
  explicit Chip8Facade(const std::string &path = "");
  ~Chip8Facade();
  Chip8Facade(Chip8Facade &) = delete;
  Chip8Facade &operator=(Chip8Facade &) = delete;

  void loadROM(const std::string &path);
  void execute();

private:
  bool quit_{false};
  bool loaded_{false};

  Memory memory_;
  Input *input_;
  Display *display_;
};
