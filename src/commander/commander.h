#pragma once

#include <cstddef>
#include <string>

#include "memento/saveStateManager.h"

class Chip8;

class Commander {
public:
  explicit Commander(Chip8 &chip8);

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

  // Display
  void toggleFullScreen();
  void saveScreenshot() const;

private:
  Chip8 &chip8_;

  SaveStateManager ssmanager_;
};
