#include "chip8Facade.h"
#include "input/inputSDL.h"
#include "memory.h"

#include <iostream>

Chip8Facade::Chip8Facade(const std::string &path)
    : input_(new InputSDL(memory_, quit_)) {
  if (!path.empty())
    loadROM(path);
}

Chip8Facade::~Chip8Facade() { delete input_; }

void Chip8Facade::loadROM(const std::string &path) {
  try {
    std::string extension = path.substr(path.find_last_of(".") + 1);
    if (extension != "ch8" && extension != "rom")
      throw std::runtime_error(
          "Chip-8 ROMs must have a valid .ch8  or .rom extension!");

    memory_.loadRom(path);
    loaded_ = true;

  } catch (const std::runtime_error &e) {
    std::cerr << " - || Chip-8 error: " << e.what() << std::endl;

  } catch (const std::exception &e) {
    std::cout << "Description: " << e.what() << std::endl;
  }
}

void Chip8Facade::execute() {
  while (!quit_) {
    // Handle input
    input_->pollEvents();

    if (loaded_) {
      // Emulate one cpu cycle
      /* cpu_.cycle(); */

      /* // Update screen */
      /* if (cpu_.mustDraw()) */
      /*   display_.render(); */
    }
  }
}
