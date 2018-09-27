#pragma once

#include "memory.h"
#include <SDL2/SDL.h>

class Input {
public:
  Input(Memory &memory, bool &quit) : memory_(memory), quit_(quit) {}
  void pollEvents();

private:
  // Components
  Memory &memory_;
  bool &quit_;

  // Attributes
  static std::array<uint8_t, 16> keymap_;
};
