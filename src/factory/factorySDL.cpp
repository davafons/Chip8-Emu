#include <SDL2/SDL.h>
#include <iostream>

#include "factorySDL.h"
#include "memory/memory.h"
#include "chip8Facade.h"

FactorySDL::FactorySDL() {
  if(SDL_Init(0) < 0)
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

InputSDL *FactorySDL::createInput(Chip8Facade & facade, Memory &memory) const {
  return new InputSDL(facade, memory);
}

SoundSDL *FactorySDL::createSound() const { return new SoundSDL; }
