#pragma once

#include "sound.h"

class SoundSDL : public Sound {
public:
  void playPitch() const override;
};
