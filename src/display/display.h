#pragma once

class Display {
public:
  virtual ~Display() = default;

  virtual void toggleFullScreen() = 0;

  virtual void render() = 0;
};
