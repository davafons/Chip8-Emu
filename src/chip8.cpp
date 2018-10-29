#include <iostream>

#include "chip8.h"
#include "display/display.h"
#include "factory/abstractFactory.h"
#include "input/input.h"
#include "sound/sound.h"

Chip8::Chip8(std::unique_ptr<AbstractFactory> &factory,
             const std::string &rom_path)
    : display_(factory->createDisplay(memory_)),
      input_(factory->createInput(commander_)), sound_(factory->createSound()) {

  std::cout << "\n\n |---- CHIP8 Emulator ----|" << std::endl;
  if (!rom_path.empty())
    commander_.loadRom(rom_path);
  else {
    std::cout << "Please drop a .rom or .ch8 file to start emulation..."
              << std::endl;
  }
}

Chip8::~Chip8() { std::cout << "\n-- Closing the emulator...\n" << std::endl; }

void Chip8::execute() {
  while (!quit_) {
    // Handle input
    input_->pollEvents();

    if (memory_.romLoaded() && !cpu_.isPaused()) {
      // Emulate one cpu cycle
      cpu_.cycle();

      // Update screen
      if (cpu_.mustDraw()) {
        display_->render();
      }

      // Play sound
      if (cpu_.mustSound()) {
        sound_->playPitch();
      }
    }
  }
}
