#include <iostream>

#include "chip8.h"
#include "commander.h"
#include "display/display.h"

Commander::Commander(Chip8 &chip8)
    : chip8_(chip8), ssmanager_(chip8_.cpu_, chip8_.memory_) {}

void Commander::exit() { chip8_.quit_ = true; }

void Commander::reset() {
  if (chip8_.memory_.romLoaded()) {
    chip8_.cpu_.reset();
    chip8_.memory_.clearDisplay();
  }
}

void Commander::loadRom(const std::string &rom_path) {
  std::cout << "\n\n |---- Loading Rom ----|" << std::endl;
  chip8_.cpu_.reset();
  chip8_.memory_.reset();
  chip8_.memory_.loadRom(rom_path);
}

void Commander::keyDown(size_t i) { chip8_.memory_.writeToKeys(i) = 1; }
void Commander::keyUp(size_t i) { chip8_.memory_.writeToKeys(i) = 0; }

void Commander::togglePause() { chip8_.cpu_.togglePause(); }
void Commander::doubleSpeed() { chip8_.cpu_.doubleSpeed(); }
void Commander::halfSpeed() { chip8_.cpu_.halfSpeed(); }

void Commander::saveState(size_t i) {
  ssmanager_.saveState(i);
  std::cout << "-- State " << i << " saved!" << std::endl;
}

void Commander::loadState(size_t i) {
  try {
    ssmanager_.loadState(i);
    std::cout << "-- State " << i << " loaded!" << std::endl;
  } catch (std::out_of_range &e) {
    std::cout << " -- State " << i << " is empty." << std::endl;
  }
}

void Commander::toggleFullScreen() { chip8_.display_->toggleFullScreen(); }

void Commander::saveScreenshot() const {
  chip8_.display_->saveScreenshot();
  std::cout << "-- Screenshot saved!" << std::endl;
}
