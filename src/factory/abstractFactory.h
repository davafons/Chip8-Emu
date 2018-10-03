#pragma once

class Display;
class Input;
class Memory;
class Sound;

class AbstractFactory {
public:
  virtual ~AbstractFactory() = default;

  virtual Display *createDisplay(Memory &memory) const = 0;
  virtual Input *createInput(Memory &memory, bool &quit) const = 0;
  virtual Sound *createSound() const = 0;
};
