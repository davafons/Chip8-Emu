#include <iostream>
#include <memory>
#include <string>

#include "chip8.h"
#include "factory/factorySDL.h"
#include "factory/factoryOpenGL.h"

int main(int argc, char *argv[]) {
  std::string rom_path = "";
  if (argc > 1) {
    rom_path = argv[1];
  }

  // Factories will be expanded when adding more graphic libraries
  std::unique_ptr<AbstractFactory> factory;

  try
  {
    factory = std::make_unique<FactoryOpenGL>();

    Chip8 c8(factory, rom_path);
    c8.execute();
  }
  catch(const char *msg)
  {
    std::cout << "ERROR: " << msg << std::endl;
  }
  catch(const std::string & msg)
  {
    std::cout << "ERROR: " << msg << std::endl;
  }

  return 0;
}
