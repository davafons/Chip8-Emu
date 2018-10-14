#include <iostream>

#include <SDL2/SDL.h>

#include "chip8Facade.h"
#include "inputSDL.h"
#include "memory/memory.h"

InputSDL::InputSDL(Chip8Facade &facade, Memory &memory)
    : facade_(facade), memory_(memory) {
  if (SDL_InitSubSystem(SDL_INIT_GAMECONTROLLER) < 0)
    throw SDL_GetError();
}

InputSDL::~InputSDL() { SDL_QuitSubSystem(SDL_INIT_GAMECONTROLLER); }

void InputSDL::pollEvents() {
  SDL_Event e;
  if (SDL_PollEvent(&e) != 0) {
    switch (e.type) {
    case SDL_QUIT:
      facade_.exit();
      break;

    case SDL_DROPFILE:
      facade_.loadRom(e.drop.file);
      break;

    case SDL_KEYDOWN:
      if (e.key.keysym.sym == SDLK_ESCAPE)
        facade_.exit();

      else if (e.key.keysym.sym == SDLK_g)
        facade_.reset();

      else if (e.key.keysym.sym == SDLK_F1) {
        std::cout << "-- Half Cpu speed." << std::endl;
        facade_.halfSpeed();
      }

      else if (e.key.keysym.sym == SDLK_F2) {
        std::cout << "-- Double Cpu speed." << std::endl;
        facade_.doubleSpeed();
      }

      for (size_t i = 0; i < keymap_.size(); ++i) {
        if (e.key.keysym.sym == keymap_[i])
          keyDown(i);
      }
      break;

    case SDL_KEYUP:
      for (size_t i = 0; i < keymap_.size(); ++i) {
        if (e.key.keysym.sym == keymap_[i])
          keyUp(i);
      }
      break;
    }
  }
}

void InputSDL::keyDown(size_t pos) { memory_.writeToKeys(pos) = 1; }
void InputSDL::keyUp(size_t pos) { memory_.writeToKeys(pos) = 0; }

std::array<uint8_t, 16> InputSDL::keymap_ = {
    SDLK_x, SDLK_1, SDLK_2, SDLK_3, SDLK_q, SDLK_w, SDLK_e, SDLK_a,
    SDLK_s, SDLK_d, SDLK_z, SDLK_c, SDLK_4, SDLK_r, SDLK_f, SDLK_v};
