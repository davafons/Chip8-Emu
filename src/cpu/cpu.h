#pragma once

#include <memory>

#include "timer.h"

class Memory;

class Cpu {
public:
  explicit Cpu(Memory &memory);
  ~Cpu();

  void cycle();
  void reset();

  bool mustDraw() const;
  bool mustSound() const;

  bool isPaused() const;
  void togglePause();

  void doubleSpeed();
  void halfSpeed();

private:
  bool paused_{false};
  class ImplChip8;
  std::unique_ptr<ImplChip8> impl_;

  Timer timer_;
};
