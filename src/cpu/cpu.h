#pragma once

#include <memory>

class Memory;
class Impl;

class Cpu {
public:
  explicit Cpu(Memory &memory);
  Cpu(const Cpu &) = delete;
  Cpu &operator=(const Cpu &) = delete;
  ~Cpu();

  void cycle();

  bool mustDraw() const;
  bool mustSound() const;

private:
  Impl *impl_;
};
