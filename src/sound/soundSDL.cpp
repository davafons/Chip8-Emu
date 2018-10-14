#include <cstdio>
#include <iostream>

#include "soundSDL.h"

SoundSDL::SoundSDL() {
  if (SDL_InitSubSystem(SDL_INIT_AUDIO) < 0)
    throw SDL_GetError();

  char *base_path = SDL_GetBasePath();
  std::string wav_path = base_path + std::string("../res/beep.wav");

  if (SDL_LoadWAV(wav_path.c_str(), &wav_spec_, &wav_buffer_, &wav_length_) ==
      nullptr)
    throw SDL_GetError();

  SDL_free(base_path);

  device_id_ = SDL_OpenAudioDevice(nullptr, 0, &wav_spec_, nullptr, 0);
  if(device_id_ == 0)
    throw SDL_GetError();
}

SoundSDL::~SoundSDL() {
  SDL_CloseAudioDevice(device_id_);
  SDL_FreeWAV(wav_buffer_);
  SDL_QuitSubSystem(SDL_INIT_AUDIO);
}

void SoundSDL::playPitch() const {
  try
  {
    if(SDL_QueueAudio(device_id_, wav_buffer_, wav_length_) < 0)
      throw SDL_GetError();

    SDL_PauseAudioDevice(device_id_, 0);
  }
  catch(const char* msg)
  {
    std::cerr << "SoundSDL::SDL_Error: " << msg << std::endl;
  }
}
