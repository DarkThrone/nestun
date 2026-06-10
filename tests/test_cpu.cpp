#include "doctest.h"

TEST_CASE("Addressing Modes") {
  SUBCASE("Implicit") { CHECK(1 + 1 == 2); }
  SUBCASE("Accumulator") { CHECK(1 + 1 == 2); }
  SUBCASE("Immediate") { CHECK(1 + 1 == 2); }
  SUBCASE("ZeroPage") { CHECK(1 + 1 == 2); }
  SUBCASE("ZeroPageX") { CHECK(1 + 1 == 2); }
  SUBCASE("ZeroPageY") { CHECK(1 + 1 == 2); }
  SUBCASE("Absolute") { CHECK(1 + 1 == 2); }
  SUBCASE("AbsoluteX") { CHECK(1 + 1 == 2); }
  SUBCASE("AbsoluteY") { CHECK(1 + 1 == 2); }
  SUBCASE("Indirect") { CHECK(1 + 1 == 2); }
  SUBCASE("IndirectX") { CHECK(1 + 1 == 2); }
  SUBCASE("IndirectY") { CHECK(1 + 1 == 2); }
  SUBCASE("Relative") { CHECK(1 + 1 == 2); }
}
