#include "saveStateManager.h"

#include "cpu/cpu.h"
#include "memory/memory.h"
#include "memento/memento.h"

SaveStateManager::SaveStateManager(Memory &memory) : memory_(memory) {}

void SaveStateManager::saveState(size_t i) {
  save_states_.at(i) = Memento(memory_);
}


void SaveStateManager::loadState(size_t i) {
  memory_ = save_states_.at(i).getMemory();
}

std::vector<Memento> SaveStateManager::save_states_;