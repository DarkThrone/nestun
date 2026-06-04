#include <cstring>
#include <print>
#include <string>

#include "Cpu.hpp"

using namespace Nestun;
using namespace std;

int main() {
  Bus bus{};
  Cpu cpu(bus);

  bus.load_rom(std::string("file.nes"));

  println("Starting CPU");
  cpu.reset();

  int i = 0;
  while (i++ < 100) {
    cpu.tick();
  }
}
