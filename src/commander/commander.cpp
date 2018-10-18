#include <iostream>

#include "commander.h"

#include "cpu/cpu.h"
#include "memory/memory.h"

Commander::Commander(Cpu &cpu, Memory &memory, bool &quit)
    : cpu_(cpu), memory_(memory), quit_(quit) {}

void Commander::exit() { quit_ = true; }

void Commander::reset() {
  if (memory_.romLoaded()) {
    cpu_.reset();
    memory_.clearDisplay();
  }
}

void Commander::loadRom(const std::string &rom_path) {
  std::cout << "\n\n |---- Loading Rom ----|" << std::endl;
  cpu_.reset();
  memory_.reset();
  memory_.loadRom(rom_path);
}

void Commander::keyDown(size_t i) { memory_.writeToKeys(i) = 1; }
void Commander::keyUp(size_t i) { memory_.writeToKeys(i) = 0; }

void Commander::togglePause() { cpu_.togglePause(); }
void Commander::doubleSpeed() { cpu_.doubleSpeed(); }
void Commander::halfSpeed() { cpu_.halfSpeed(); }

void Commander::saveState(size_t i) {
  ssmanager_.saveState(i);
  std::cout << "-- State saved in " << i << std::endl;
}

void Commander::loadState(size_t i) {
  ssmanager_.loadState(i);
  std::cout << "-- State loaded from " << i << std::endl;
}
