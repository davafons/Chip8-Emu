#pragma once

class Display {
public:
  virtual ~Display() = default;

  virtual void render() = 0;
};
