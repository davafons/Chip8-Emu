#include <iostream>

#include <SDL2/SDL.h>

#include "factorySDL.h"

class Memory;
class Commander;

FactorySDL::FactorySDL() {
  std::cout << "-- Initializing SDL..." << std::endl;
  if (SDL_Init(0) < 0)
    throw SDL_GetError();
  std::cout << "-- SDL initialized!\n" << std::endl;
}

FactorySDL::~FactorySDL() {
  SDL_Quit();
  std::cout << "-- SDL Library completely closed!" << std::endl;
}

DisplaySDL *FactorySDL::createDisplay(Memory &memory) const {
  return new DisplaySDL(memory);
}

InputSDL *FactorySDL::createInput(Commander &commander) const {
  return new InputSDL(commander);
}

SoundSDL *FactorySDL::createSound() const { return new SoundSDL; }
