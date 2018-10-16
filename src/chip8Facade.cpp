#include <iostream>

#include "chip8Facade.h"
#include "display/display.h"
#include "factory/abstractFactory.h"
#include "input/input.h"
#include "sound/sound.h"

Chip8Facade::Chip8Facade(std::unique_ptr<AbstractFactory> &factory,
                         const std::string &rom_path)
    : display_(factory->createDisplay(memory_)),
      input_(factory->createInput(commander_)), sound_(factory->createSound()) {

  std::cout << "\n\n |---- CHIP8 Emulator ----|" << std::endl;
  if (!rom_path.empty())
    loadRom(rom_path);
  else {
    std::cout << "Please drop a .rom or .ch8 file to start emulation..."
              << std::endl;
  }
}

Chip8Facade::~Chip8Facade() {
  std::cout << "\n-- Closing the emulator...\n" << std::endl;
}

void Chip8Facade::execute() {
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
