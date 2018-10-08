#pragma once

#include <array>

#include "input.h"

class Memory;
class Chip8Facade;

class InputSDL : public Input {
public:
  explicit InputSDL(Chip8Facade &facade, Memory &memory);
  InputSDL(const InputSDL &) = delete;
  InputSDL &operator=(const InputSDL &) = delete;

  void pollEvents() override;

private:
  void keyDown(size_t pos) override;
  void keyUp(size_t pos) override;

private:
  // Components
  Chip8Facade &facade_;
  Memory &memory_;

  // Attributes
  static std::array<uint8_t, 16> keymap_;
};
