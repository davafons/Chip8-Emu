#pragma once

#include "abstractFactory.h"
#include "commander/commander.h"
#include "display/displayOpenGL.h"
#include "input/inputSDL.h"
#include "sound/soundSDL.h"

class Memory;

class FactoryOpenGL : public AbstractFactory {
public:
  explicit FactoryOpenGL();
  ~FactoryOpenGL();
  FactoryOpenGL(const FactoryOpenGL &) = delete;
  FactoryOpenGL &operator=(const FactoryOpenGL &) = delete;

  DisplayOpenGL *createDisplay(Memory &memory) const override;
  InputSDL *createInput(Commander &commander) const override;
  SoundSDL *createSound() const override;
};
