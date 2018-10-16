#pragma once

class Input {
public:
  virtual ~Input() = default;

  virtual void pollEvents() = 0;
};
