#pragma once

#include <SDL2/SDL.h>

#include "display.h"

class Memory;

class DisplaySDL : public Display {
public:
  explicit DisplaySDL(Memory &memory);
  ~DisplaySDL();

  void toggleFullScreen() override;

  void render() override;

private:
  Memory &memory_;

  SDL_Window *window_{nullptr};
  SDL_Renderer *renderer_{nullptr};

  SDL_Color bg_;
  SDL_Color fg_;

  bool isFullScreen_{false};
};
