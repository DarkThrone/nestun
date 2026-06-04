#include "Cpu.hpp"

#include <cstdint>
#include <print>

using namespace Nestun;
using namespace std;

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
  Instruction i;
  println("Decoding instruction {:x}", op);
  return i;
};

uint8_t Cpu::execute(Instruction _instruction) {
  println("Executing instruction");
  return 0;
};

void Cpu::reset() { println("Resetting PC to {}", 1); }
