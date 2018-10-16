#include <cstdio>
#include <iostream>

#include "soundSDL.h"

SoundSDL::SoundSDL() {
  std::cout << "- Loading SoundSDL..." << std::endl;

  char *base_path = SDL_GetBasePath();

  try {
    if (SDL_InitSubSystem(SDL_INIT_AUDIO) < 0)
      throw SDL_GetError();

    std::string wav_path = base_path + std::string("../res/beep.wav");

    if (SDL_LoadWAV(wav_path.c_str(), &wav_spec_, &wav_buffer_, &wav_length_) ==
        nullptr)
      throw SDL_GetError();

    device_id_ = SDL_OpenAudioDevice(nullptr, 0, &wav_spec_, nullptr, 0);
    if (device_id_ == 0)
      throw SDL_GetError();

    if (SDL_QueueAudio(device_id_, wav_buffer_, wav_length_) < 0)
      throw SDL_GetError();

    initialized_ = true;
    std::cout << "- SoundSDL loaded." << std::endl;

  } catch (const char *msg) {
    std::cerr << "-- SoundSDL Error: " << msg << std::endl;
    std::cerr << "\t- Sound will not be played." << std::endl;

    initialized_ = false;
  }

  SDL_free(base_path);
}

SoundSDL::~SoundSDL() {
  SDL_CloseAudioDevice(device_id_);
  SDL_FreeWAV(wav_buffer_);
  SDL_QuitSubSystem(SDL_INIT_AUDIO);
  std::cout << "- SoundSDL closed." << std::endl;
}

void SoundSDL::playPitch() const {
  if (initialized_)
    SDL_PauseAudioDevice(device_id_, 0);
  else
    std::cout << "---- SOOOUNNDDDD ----" << std::endl;
}
