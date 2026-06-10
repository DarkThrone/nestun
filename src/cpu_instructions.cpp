#include <sys/types.h>

#include <array>
#include <cstddef>
#include <cstdint>

#include "../include/Cpu.hpp"

// using Nestun::Cpu;

namespace {

using namespace Nestun;

constexpr auto buildTable() {
  std::array<Instruction, 256> t{};

  for (auto& i : t) {
    i = {.mode = AddressingMode::Implicit,
         .shape = OpShape::Implied,
         .op = "ILL",
         .opcode = 0x04,
         .cycles = 2,
         .execute = nullptr};
  }

  // LDA
  t[0xA9] = {
      .mode = AddressingMode::Immediate,
      .shape = OpShape::Write,
      .op = "LDA",
      .opcode = 0xA9,
      .cycles = 2,
      .execute = [](Cpu& cpu, uint16_t v) { cpu.lda(v); },
  };

  t[0xA5] = {.mode = AddressingMode::ZeroPage,
             .shape = OpShape::Write,
             .op = "LDA",
             .opcode = 0xA5,
             .cycles = 3,
             .execute = [](Cpu& c, uint16_t a) { c.lda(static_cast<uint8_t>(a)); }};

  t[0xB5] = {.mode = AddressingMode::ZeroPageX,
             .shape = OpShape::Write,
             .op = "LDA",
             .opcode = 0xB5,
             .cycles = 4,
             .execute = [](Cpu& c, uint16_t a) {}};

  t[0xAD] = {.mode = AddressingMode::Absolute,
             .shape = OpShape::Write,
             .op = "LDA",
             .opcode = 0xAD,
             .cycles = 4,
             .execute = [](Cpu& c, uint16_t a) {}};

  t[0xBD] = {.mode = AddressingMode::AbsoluteX,
             .shape = OpShape::Write,
             .op = "LDA",
             .opcode = 0xBD,
             .cycles = 4,
             .execute = [](Cpu& c, uint16_t a) {}};

  t[0xB9] = {.mode = AddressingMode::AbsoluteY,
             .shape = OpShape::Write,
             .op = "LDA",
             .opcode = 0xB9,
             .cycles = 4,
             .execute = [](Cpu& c, uint16_t a) {}};

  t[0xA1] = {.mode = AddressingMode::IndirectX,
             .shape = OpShape::Write,
             .op = "LDA",
             .opcode = 0xA1,
             .cycles = 6,
             .execute = [](Cpu& c, uint16_t a) {}};

  t[0xB1] = {.mode = AddressingMode::IndirectY,
             .shape = OpShape::Write,
             .op = "LDA",
             .opcode = 0xB1,
             .cycles = 5,
             .execute = [](Cpu& c, uint16_t a) {}};
  // NOP
  t[0xEA] = {.mode = AddressingMode::Implicit,
             .shape = OpShape::Implied,
             .op = "NOP",
             .opcode = 0xEA,
             .cycles = 2,
             .execute = [](Cpu& c, uint16_t a) {}};

  return t;
};
}  // namespace

namespace Nestun {
void Cpu::lda(uint8_t value) {
  A = value;
  set_nz(value);
};

const std::array<Instruction, 256> Cpu::TABLE = buildTable();
}  // namespace Nestun
