#include <iostream>

#include "cpu.h"
#include "impl/implChip8.h"
#include "memory/memory.h"

Cpu::Cpu(Memory &memory) : impl_(std::make_unique<ImplChip8>(memory)) {}
Cpu::~Cpu() = default;

Cpu::Cpu(const Cpu &rhs)
    : paused_(rhs.paused_), impl_(std::make_unique<ImplChip8>(*rhs.impl_)),
      timer_(rhs.timer_) {}

Cpu &Cpu::operator=(Cpu rhs) {
  swap(*this, rhs);

  return *this;
}

void swap(Cpu &first, Cpu &second) noexcept {
  using std::swap;

  swap(first.paused_, second.paused_);
  swap(first.impl_, second.impl_);
  swap(first.timer_, second.timer_);
}

void Cpu::cycle() {
  impl_->resetFlags();
  impl_->fetch();
  impl_->execute();

  if (timer_.mustUpdateCpuTimers())
    impl_->updateTimers();

  timer_.delayCpu();
}

void Cpu::reset() {
  std::cout << "-- Resetting Cpu..." << std::endl;
  impl_->reset();
  std::cout << "-- Cpu reseted.\n" << std::endl;
}

bool Cpu::mustDraw() const { return impl_->mustDraw(); }
bool Cpu::mustSound() const { return impl_->mustSound(); }

bool Cpu::isPaused() const { return paused_; }
void Cpu::togglePause() { paused_ = !paused_; }

void Cpu::doubleSpeed() { timer_.doubleSpeed(); }
void Cpu::halfSpeed() { timer_.halfSpeed(); }
