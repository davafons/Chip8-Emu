#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "display/display.h"

class Memory;

class DisplayOpenGL : public Display
{
public:
  explicit DisplayOpenGL(Memory &memory);
  ~DisplayOpenGL();

  void toggleFullScreen() override;

  void saveScreenshot() const override;

  void render() override;

private:
  Memory &memory_;

  GLFWwindow *window_;

  const int width_{512};
  const int height_{512};

  bool isFullScreen_{false};
};
