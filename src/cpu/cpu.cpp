#include "cpu.h"
#include "impl/implChip8.h"
#include "memory/memory.h"

Cpu::Cpu(Memory &memory) : impl_(std::make_unique<ImplChip8>(memory)) {}
Cpu::~Cpu() = default;

void Cpu::cycle() {
  impl_->resetFlags();
  impl_->fetch();
  impl_->execute();
  impl_->updateTimers();
  impl_->delay();
}

bool Cpu::mustDraw() const { return impl_->mustDraw(); }
bool Cpu::mustSound() const { return impl_->mustSound(); }
