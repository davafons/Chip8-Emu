#include "input.h"

void Input::pollEvents() {
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
        quit_ = true;

      if (e.key.keysym.sym == SDLK_u) {
        for (size_t i = 0; i < keymap_.size(); ++i) {
          if (e.key.keysym.sym == keymap_[i])
            memory_.writeToKeys(i) = 1;
        }
      }

    case SDL_KEYUP:
      for (size_t i = 0; i < keymap_.size(); ++i) {
        if (e.key.keysym.sym == keymap_[i])
          memory_.writeToKeys(i) = 0;
      }
    }
  }
}

std::array<uint8_t, 16> Input::keymap_ = {
    SDLK_x, SDLK_1, SDLK_2, SDLK_3, SDLK_q, SDLK_w, SDLK_e, SDLK_a,
    SDLK_s, SDLK_d, SDLK_z, SDLK_c, SDLK_4, SDLK_r, SDLK_f, SDLK_v};
