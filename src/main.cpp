#include "Cpu.hpp"
#include <cstring>
#include <string>

using namespace Nestun;

int main() {
  Cpu cpu;

  cpu.load_rom(std::string("file.nes"));
  cpu.run();
}
