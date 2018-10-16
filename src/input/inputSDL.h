#pragma once

#include <array>

#include "input.h"

class Commander;

class InputSDL : public Input {
public:
  explicit InputSDL(Commander &commander);
  ~InputSDL();

  void pollEvents() override;

private:
  // Components
  Commander &commander_;

  // Attributes
  static const std::array<uint8_t, 16> keymap_;
};
