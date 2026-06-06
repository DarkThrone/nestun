#include "../include/Cpu.hpp"

#include <cstdint>
#include <format>
#include <print>

using namespace Nestun;
using namespace std;

template <>
struct std::formatter<Instruction> : std::formatter<std::string> {
  auto format(const Instruction& inst, auto& ctx) const {
    return std::formatter<std::string>::format(
        std::format("{} {:02x} cyc={}", inst.op, inst.opcode, inst.cycles), ctx);
  }
};

void Cpu::tick() {
  uint8_t op = fetch();
  Instruction instruction = decode(op);
  execute(instruction);
}

uint8_t Cpu::fetch() {
  println("Fetching instruction");
  return 0xea;
};

Instruction Cpu::decode(const uint8_t op) {
  Instruction i = Cpu::TABLE[op];
  println("Decoding instruction {:x}", op);
  return i;
};

uint8_t Cpu::execute(Instruction inst) {
  println("Executing instruction: {}", inst);
  return 0;
};

void Cpu::reset() { println("Resetting PC to {}", 1); }
