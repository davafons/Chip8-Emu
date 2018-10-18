#include "saveStateManager.h"

#include "cpu/cpu.h"
#include "memento/memento.h"
#include "memory/memory.h"

SaveStateManager::SaveStateManager(Cpu &active_cpu, Memory &active_memory)
    : active_cpu_(active_cpu), active_memory_(active_memory) {}

void SaveStateManager::saveState(size_t i) {
  save_states_.erase(i);
  save_states_.emplace(i, Memento(active_cpu_, active_memory_));
}

void SaveStateManager::loadState(size_t i) {
  active_cpu_ = save_states_.at(i).getCpu();
  active_memory_ = save_states_.at(i).getMemory();
}

std::unordered_map<size_t, Memento> SaveStateManager::save_states_;
