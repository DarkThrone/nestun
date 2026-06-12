#include "../include/Bus.hpp"
#include "../include/Cpu.hpp"
#include "doctest.h"

using namespace Nestun;

TEST_CASE("Addressing Modes") {
  Bus bus{};
  Cpu cpu(bus);

  bus.clear();
  cpu.reset();

  SUBCASE("Immediate") {
    bus.write(0x8000, 0xA9);
    bus.write(0x8001, 0x42);

    cpu.setPC(0x8000);
    cpu.tick();

    CHECK(cpu.getA() == 0x42);
  }

  // SUBCASE("Implicit [.]") { CHECK(1 + 1 == 2); }
  // SUBCASE("Accumulator [.]") { CHECK(1 + 1 == 2); }
  // SUBCASE("ZeroPage [.]") { CHECK(1 + 1 == 2); }
  // SUBCASE("ZeroPageX [.]") { CHECK(1 + 1 == 2); }
  // SUBCASE("ZeroPageY [.]") { CHECK(1 + 1 == 2); }
  // SUBCASE("Absolute [.]") { CHECK(1 + 1 == 2); }
  // SUBCASE("AbsoluteX [.]") { CHECK(1 + 1 == 2); }
  // SUBCASE("AbsoluteY [.]") { CHECK(1 + 1 == 2); }
  // SUBCASE("Indirect [.]") { CHECK(1 + 1 == 2); }
  // SUBCASE("IndirectX [.]") { CHECK(1 + 1 == 2); }
  // SUBCASE("IndirectY [.]") { CHECK(1 + 1 == 2); }
  // SUBCASE("Relative [.]") { CHECK(1 + 1 == 2); }
}
