#pragma once

#include <memory>

#include "timer.h"

class Memory;

class Cpu {
public:
  explicit Cpu(Memory &memory);
  ~Cpu();
  Cpu(const Cpu &rhs);
  Cpu &operator=(Cpu rhs);
  friend void swap(Cpu &first, Cpu& second) noexcept;

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
