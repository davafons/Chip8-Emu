#include "cpu.h"
#include "impl/implChip8.h"
#include "memory.h"

Cpu::Cpu(Memory &memory) : impl_(new ImplChip8(memory)){}
Cpu::~Cpu() { delete impl_; }

void Cpu::cycle() {
  impl_->fetch();
  impl_->execute();
  impl_->updateTimers();
}

bool Cpu::mustDraw() const { return impl_->mustDraw(); }
bool Cpu::mustSound() const { return impl_->mustSound(); }
