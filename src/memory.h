#pragma once

#include <array>
#include <string>
#include <cstdint>

class Memory {
public:
  Memory();
  void loadRom(const std::string &path);
  void reset();

  uint8_t readFromRam(size_t pos) const { return ram_[pos]; }
  uint8_t &writeToRam(size_t pos) { return ram_[pos]; }

  uint8_t readFromDisplay(size_t pos) const { return display_[pos]; }
  uint8_t &writeToDisplay(size_t pos) { return display_[pos]; }
  void clearDisplay() { std::fill(display_.begin(), display_.end(), 0x00); }

  uint8_t readFromKeys(size_t pos) const { return keys_[pos]; }
  uint8_t &writeToKeys(size_t pos) { return keys_[pos]; }

private:
  std::ifstream openFileWithExceptions(const std::string &path) const;
  void copyRomtoMemory(std::ifstream &file);

  std::array<uint8_t, 4096> ram_;
  std::array<uint8_t, 64 * 32> display_;
  std::array<uint8_t, 16> keys_;

  static const std::array<uint8_t, 16 * 5> hex_sprites;
};
