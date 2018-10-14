#pragma once

#include "abstractFactory.h"

#include "display/displaySDL.h"
#include "input/inputSDL.h"
#include "sound/soundSDL.h"

class Memory;

class FactorySDL : public AbstractFactory {
public:
  explicit FactorySDL();
  ~FactorySDL();
  FactorySDL(const FactorySDL &) = delete;
  FactorySDL &operator=(const FactorySDL &) = delete;

  DisplaySDL *createDisplay(Memory &memory) const override;
  InputSDL *createInput(Chip8Facade &facade, Memory &memory) const override;
  SoundSDL *createSound() const override;
};
