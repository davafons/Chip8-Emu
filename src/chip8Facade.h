#pragma once

#include <memory>
#include <string>

#include "cpu/cpu.h"
#include "memory/memory.h"

class AbstractFactory;
class Display;
class Input;
class Sound;

// INLINE

class Chip8Facade {
public:
  explicit Chip8Facade(std::unique_ptr<AbstractFactory> &factory,
                       const std::string &rom_path = "");
  ~Chip8Facade() = default;
  Chip8Facade(Chip8Facade &) = delete;
  Chip8Facade &operator=(Chip8Facade &) = delete;

  void loadRom(const std::string &rom_path);

  void execute();
  void reset();
  void togglePause();
  void exit() { quit_ = true; }

  void doubleSpeed() { cpu_.doubleSpeed(); }
  void halfSpeed() { cpu_.halfSpeed(); }

private:
  bool quit_{false};
  std::string rom_path_{""};

  Memory memory_;
  Cpu cpu_{memory_};
  std::unique_ptr<Display> display_;
  std::unique_ptr<Input> input_;
  std::unique_ptr<Sound> sound_;
};
