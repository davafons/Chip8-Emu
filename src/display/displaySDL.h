#pragma once

#include <SDL2/SDL.h>

#include "display.h"

class Memory;

class DisplaySDL : public Display {
public:
  explicit DisplaySDL(Memory &memory);
  ~DisplaySDL();

  void render() override;

private:
  Memory &memory_;

  SDL_Window *window_;
  SDL_Renderer *renderer_;

  SDL_Color bg_;
  SDL_Color fg_;
};
