#include <SDL2/SDL.h>
#include <iostream>

#include "factorySDL.h"
#include "memory/memory.h"

FactorySDL::FactorySDL() {
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
    throw SDL_GetError();

  std::cout << "-- SDL loaded without erros!!" << std::endl;
}

FactorySDL::~FactorySDL() {
  std::cout << "-- Closing SDL..." << std::endl;
  SDL_Quit();
}

DisplaySDL *FactorySDL::createDisplay(Memory &memory) const {
  return new DisplaySDL(memory);
}

InputSDL *FactorySDL::createInput(Memory &memory, bool &quit) const {
  return new InputSDL(memory, quit);
}

SoundSDL *FactorySDL::createSound() const { return new SoundSDL; }
