#include "chip8Facade.h"
#include "display/displaySDL.h"
#include "input/inputSDL.h"

#include <iostream>

Chip8Facade::Chip8Facade(const std::string &rom_path)
    : input_(new InputSDL(memory_, quit_)), display_(new DisplaySDL(memory_)) {
  std::cout << "\n\n |---- CHIP8 Emulator ----|" << std::endl;
  if (!rom_path.empty())
    memory_.loadRom(rom_path);
  else
  {
    std::cout << "Please drop a .ch or .rom file to start emulation..." <<
      std::endl;
  }
}

Chip8Facade::~Chip8Facade() {
  delete input_;
  delete display_;
}

void Chip8Facade::execute() {
  while (!quit_) {
    // Handle input
    input_->pollEvents();

    if (memory_.romLoaded()) {
      // Emulate one cpu cycle
      cpu_.cycle();

      // Update screen
      if (cpu_.mustDraw()) {
        display_->render();
      }
    }
  }
}
