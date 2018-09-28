#pragma once

#include <array>

#include "input.h"

class Memory;

class InputSDL : public Input {
public:
  InputSDL(Memory &memory, bool &quit);

  void pollEvents() override;

private:
  void exit() override;

  void keyDown(size_t pos) override;
  void keyUp(size_t pos) override;

private:
  // Components
  Memory &memory_;
  bool &quit_;

  // Attributes
  static std::array<uint8_t, 16> keymap_;
};
