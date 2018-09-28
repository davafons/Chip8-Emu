#include <SDL2/SDL.h>

#include "inputSDL.h"
#include "memory/memory.h"

InputSDL::InputSDL(Memory &memory, bool &quit) : memory_(memory), quit_(quit) {}

void InputSDL::pollEvents() {
  SDL_Event e;
  if (SDL_PollEvent(&e) != 0) {
    switch (e.type) {
    case SDL_QUIT:
      quit_ = true;
      break;

    case SDL_DROPFILE:
      memory_.loadRom(e.drop.file);
      break;

    case SDL_KEYDOWN:
      if (e.key.keysym.sym == SDLK_ESCAPE)
        exit();

      if (e.key.keysym.sym == SDLK_u) {
        for (size_t i = 0; i < keymap_.size(); ++i) {
          if (e.key.keysym.sym == keymap_[i])
            keyDown(i);
        }
      }

    case SDL_KEYUP:
      for (size_t i = 0; i < keymap_.size(); ++i) {
        if (e.key.keysym.sym == keymap_[i])
          keyUp(i);
      }
    }
  }
}

void InputSDL::exit() { quit_ = true; }

void InputSDL::keyDown(size_t pos) { memory_.writeToKeys(pos) = 1; }
void InputSDL::keyUp(size_t pos) { memory_.writeToKeys(pos) = 0; }

std::array<uint8_t, 16> InputSDL::keymap_ = {
    SDLK_x, SDLK_1, SDLK_2, SDLK_3, SDLK_q, SDLK_w, SDLK_e, SDLK_a,
    SDLK_s, SDLK_d, SDLK_z, SDLK_c, SDLK_4, SDLK_r, SDLK_f, SDLK_v};
