#include "memory.h"

#include <fstream>

Memory::Memory() { reset(); }

void Memory::loadRom(const std::string &path) {
  std::ifstream rom = openFileWithExceptions(path);
  copyRomtoMemory(rom);
  rom.close();
}

void Memory::reset() {
  // Wipe memory
  std::fill(ram_.begin(), ram_.end(), 0);
  std::fill(display_.begin(), display_.end(), 0);
  std::fill(keys_.begin(), keys_.end(), 0);

  // Load hex sprites
  std::copy(hex_sprites.begin(), hex_sprites.end(), ram_.begin());
}

std::ifstream Memory::openFileWithExceptions(const std::string &path) const {
  std::ifstream file;
  file.exceptions(std::ifstream::failbit);
  file.open(path,
            std::ifstream::in | std::ifstream::binary | std::ifstream::ate);
  return file;
}

void Memory::copyRomtoMemory(std::ifstream &file) {
  std::streampos size = file.tellg();
  file.seekg(0, std::ifstream::beg);
  file.read(reinterpret_cast<char *>(ram_.data()) + 0x0200, size);
}

const std::array<uint8_t, 16 * 5> Memory::hex_sprites = {
    0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
    0x20, 0x60, 0x20, 0x20, 0x70, // 1
    0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
    0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
    0x90, 0x90, 0xF0, 0x10, 0x10, // 4
    0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
    0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
    0xF0, 0X10, 0x20, 0x40, 0x40, // 7
    0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
    0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
    0xF0, 0x90, 0xF0, 0x90, 0x90, // A
    0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
    0xF0, 0x80, 0x80, 0x80, 0xF0, // C
    0xE0, 0x90, 0x90, 0x90, 0xE0, // D
    0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
    0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};
