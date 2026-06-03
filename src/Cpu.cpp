#include "Cpu.hpp"
#include <cstdint>
#include <print>

using namespace Nestun;
using namespace std;

uint8_t Cpu::run() {
  print("Starting CPU");
  while (true) {
    uint8_t op = fetch();
    Mode mode = resolve_addressing_mode(op);
    Instruction instruction = decode(op, mode);
    execute(instruction);
  }
}

uint8_t Cpu::fetch() { print("Fetching instruction from"); };

Mode Cpu::resolve_addressing_mode(uint8_t op) {
  Mode m;
  print("resolving addressing mode for {:x}", op);
  return m;
};

Instruction Cpu::decode(uint8_t op, Mode mode) {
  Instruction i;
  print("Decoding instruciton {} mode {}", op, mode);
  return i;
};

void Cpu::execute(Instruction instruction) {

};

void Cpu::load_rom(std::string path) { cout << "Loading: " << path; }
