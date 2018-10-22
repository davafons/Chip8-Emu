#include <iostream>

#include <glad/glad.h>
#include <SDL2/SDL.h>

#include "factoryOpenGL.h"

class Memory;
class Commander;

FactoryOpenGL::FactoryOpenGL() {
  std::cout << "-- Initializing OpenGL (SDL/glad)..." << std::endl;
  if (SDL_Init(0) < 0)
    throw SDL_GetError();

  if(!gladLoadGLLoader(SDL_GL_GetProcAddress));
    throw "Failed to initialize GLAD";

  std::cout << "-- OpenGL initialized!\n" << std::endl;
}

FactoryOpenGL::~FactoryOpenGL() {
  SDL_Quit();
  std::cout << "-- SDL Library completely closed!" << std::endl;
}

DisplayOpenGL *FactoryOpenGL::createDisplay(Memory &memory) const {
  return new DisplayOpenGL(memory);
}

InputSDL *FactoryOpenGL::createInput(Commander &commander) const {
  return new InputSDL(commander);
}

SoundSDL *FactoryOpenGL::createSound() const { return new SoundSDL; }
