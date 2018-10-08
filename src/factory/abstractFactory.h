#pragma once

class Display;
class Input;
class Memory;
class Sound;
class Chip8Facade;

class AbstractFactory {
public:
  virtual ~AbstractFactory() = default;

  virtual Display *createDisplay(Memory &memory) const = 0;
  virtual Input *createInput(Chip8Facade & facade, Memory &memory) const = 0;
  virtual Sound *createSound() const = 0;
};
