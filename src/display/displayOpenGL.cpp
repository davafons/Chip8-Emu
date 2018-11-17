#include <iostream>

#include "displayOpenGL.h"
#include "memory/memory.h"

DisplayOpenGL::DisplayOpenGL(Memory &memory) : memory_(memory)
{
  std::cout << "- Loading DisplayOpenGL.." << std::endl;

  if(SDL_InitSubSystem(SDL_INIT_VIDEO) < 0)
    throw SDL_GetError();

  window_ = SDL_CreateWindow("Chip-8 emulator", SDL_WINDOWPOS_CENTERED,
      SDL_WINDOWPOS_CENTERED, width_, height_, SDL_WINDOW_OPENGL);

  if(!window_)
    throw SDL_GetError();

  context_ = SDL_GL_CreateContext(window_);
  SDL_GL_MakeCurrent(window_, context_);

  if(!gladLoadGLLoader(SDL_GL_GetProcAddress))
    throw SDL_GetError();

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetSwapInterval(1);

  glDisable(GL_DEPTH_TEST);
  glDisable(GL_CULL_FACE);
  glViewport(0, 0, width_, height_);
  glClearColor(0.0f, 0.5f, 1.0f, 1.0f);
}

DisplayOpenGL::~DisplayOpenGL()
{
  SDL_GL_DeleteContext(context_);
  SDL_DestroyWindow(window_);
}

void DisplayOpenGL::toggleFullScreen()
{

}

void DisplayOpenGL::saveScreenshot() const
{

}

void DisplayOpenGL::render()
{
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  SDL_GL_SwapWindow(window_);

}
