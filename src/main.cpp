#include <memory>
#include <string>

#include "chip8Facade.h"
#include "factory/factorySDL.h"

int main(int argc, char *argv[]) {
  std::string rom_path = "";
  if (argc > 1) {
    rom_path = argv[1];
  }

  Chip8Facade c8(std::make_unique<FactorySDL>(), rom_path);
  c8.execute();

  return 0;
}
