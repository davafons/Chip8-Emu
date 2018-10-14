#include <iostream>
#include <memory>
#include <string>

#include "chip8Facade.h"
#include "factory/factorySDL.h"

int main(int argc, char *argv[]) {
  std::string rom_path = "";
  if (argc > 1) {
    rom_path = argv[1];
  }

  // Factories will be expanded when adding more graphic libraries
  std::unique_ptr<AbstractFactory> factory;
  factory = std::make_unique<FactorySDL>();

  try
  {
    Chip8Facade c8(factory, rom_path);
    c8.execute();
  }
  catch(const char *msg)
  {
    std::cout << "SDL_Error: " << msg << std::endl;
  }

  return 0;
}
