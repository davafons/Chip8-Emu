#include <iostream>

#include "displayOpenGL.h"
#include "memory/memory.h"

DisplayOpenGL::DisplayOpenGL(Memory &memory) : memory_(memory)
{
  std::cout << "- Loading DisplayOpenGL.." << std::endl;

  glfwInit();

  window_ = glfwCreateWindow(width_, height_, "Chip8-emulator", NULL, NULL);
  if(window_ == NULL)
    throw "Failed to create GLFW window";

  glfwMakeContextCurrent(window_);

  if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    throw "Failed to initialize GLAD";

  glViewport(0, 0, width_, height_);
}

DisplayOpenGL::~DisplayOpenGL()
{
  glfwTerminate();
}

void DisplayOpenGL::toggleFullScreen()
{

}

void DisplayOpenGL::saveScreenshot() const
{

}

void DisplayOpenGL::render()
{

}
