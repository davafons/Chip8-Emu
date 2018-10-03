#include "chip8Facade.h"
#include "display/display.h"
#include "factory/abstractFactory.h"
#include "input/input.h"
#include "sound/sound.h"

#include <iostream>

Chip8Facade::Chip8Facade(std::unique_ptr<AbstractFactory> factory,
                         const std::string &rom_path)
    : factory_(std::move(factory)),
      input_(factory_->createInput(memory_, quit_)),
      display_(factory_->createDisplay(memory_)),
      sound_(factory_->createSound()) {

  std::cout << "\n\n |---- CHIP8 Emulator ----|" << std::endl;

  if (!rom_path.empty())
    memory_.loadRom(rom_path);
  else {
    std::cout << "Please drop a .ch or .rom file to start emulation..."
              << std::endl;
  }
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

      // Play sound
      if (cpu_.mustSound()) {
        sound_->playPitch();
      }
    }
  }
}
