#include <iostream>

#include <SDL2/SDL.h>

#include "commander/commander.h"
#include "inputSDL.h"

InputSDL::InputSDL(Commander &commander) : commander_(commander) {
  std::cout << "- Loading InputSDL..." << std::endl;

  if (SDL_InitSubSystem(SDL_INIT_GAMECONTROLLER) < 0)
    throw SDL_GetError();

  std::cout << "- InputSDL loaded." << std::endl;
}

InputSDL::~InputSDL() {
  SDL_QuitSubSystem(SDL_INIT_GAMECONTROLLER);
  std::cout << "- InputSDL closed." << std::endl;
}

void InputSDL::pollEvents() {
  SDL_Event e;
  if (SDL_PollEvent(&e)) {
    switch (e.type) {
    case SDL_QUIT:
      commander_.exit();
      break;

    case SDL_DROPFILE:
      commander_.loadRom(e.drop.file);
      break;

    case SDL_KEYDOWN:
      switch(e.key.keysym.sym)
      {
        case SDLK_ESCAPE:
          commander_.exit();
          break;

        case SDLK_g:
          commander_.reset();
          break;

        case SDLK_t:
          commander_.togglePause();
          break;

        case SDLK_F1:
          commander_.saveState(0);
          break;

        case SDLK_F2:
          commander_.saveState(1);
          break;

        case SDLK_F3:
          commander_.saveState(2);
          break;

        case SDLK_F4:
          commander_.saveState(3);
          break;

        case SDLK_F5:
          commander_.loadState(0);
          break;

        case SDLK_F6:
          commander_.loadState(1);
          break;

        case SDLK_F7:
          commander_.loadState(2);
          break;

        case SDLK_F8:
          commander_.loadState(3);
          break;

        case SDLK_F11:
          commander_.toggleFullScreen();
      }

      for (size_t i = 0; i < keymap_.size(); ++i) {
        if (e.key.keysym.sym == keymap_[i])
          commander_.keyDown(i);
      }
      break;

    case SDL_KEYUP:
      for (size_t i = 0; i < keymap_.size(); ++i) {
        if (e.key.keysym.sym == keymap_[i])
          commander_.keyUp(i);
      }
      break;
    }
  }
}

const std::array<uint8_t, 16> InputSDL::keymap_ = {
    SDLK_x, SDLK_1, SDLK_2, SDLK_3, SDLK_q, SDLK_w, SDLK_e, SDLK_a,
    SDLK_s, SDLK_d, SDLK_z, SDLK_c, SDLK_4, SDLK_r, SDLK_f, SDLK_v};
