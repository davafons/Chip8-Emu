#pragma once

#include <cstddef>

class Input {
public:
  virtual ~Input() = default;
  virtual void pollEvents() = 0;

private:
  virtual void keyDown(size_t pos) = 0;
  virtual void keyUp(size_t pos) = 0;
};
