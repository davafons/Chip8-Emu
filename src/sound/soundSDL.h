#pragma once

#include <SDL2/SDL.h>

#include "sound.h"

class SoundSDL : public Sound {
public:
  SoundSDL();
  ~SoundSDL();

  void playPitch() const override;

private:
  bool initialized_{false};

  SDL_AudioSpec wav_spec_;
  uint32_t wav_length_{0};
  uint8_t *wav_buffer_{nullptr};

  SDL_AudioDeviceID device_id_;
};
