#include "Bus.hpp"
#include <cstdint>
#include <cstdlib>
#include <iostream>

using namespace Nestun;
using namespace std;

[[nodiscard]] uint8_t Bus::read(const uint16_t address) const {
  return mem.at(address);
}

void Bus::write(const uint16_t address, const uint8_t value) {
  if (address > 0X1000) {
    std::cerr << "memory read is out of bounds";
    quick_exit(-1);
  }

  // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-constant-array-index)
  mem[address] = value;
}
