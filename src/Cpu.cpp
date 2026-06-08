#include "../include/Cpu.hpp"

#include <cstdint>
#include <format>
#include <print>

using namespace Nestun;
using namespace std;

pair<uint16_t, bool> Cpu::resolve(AddressingMode mode) {
  switch (mode) {
    case AddressingMode::Implied:
    case AddressingMode::Accumulator:
    case AddressingMode::Immediate:
    case AddressingMode::ZeroPage:
    case AddressingMode::ZeroPageX:
    case AddressingMode::ZeroPageY:
    case AddressingMode::Absolute:
    case AddressingMode::AbsoluteX:
    case AddressingMode::AbsoluteY:
    case AddressingMode::Indirect:
    case AddressingMode::IndirectX:
    case AddressingMode::IndirectY:
    case AddressingMode::Relative:
  }
  return make_pair(0, false);
};

void Cpu::tick() {
  println("Fetching instruction");
  uint8_t opcode = bus_->read(PC++);

  const auto& inst = TABLE.at(static_cast<std::size_t>(opcode));
  println("Decoding instruction {:x}", opcode);

  auto [addr, crossed] = resolve(inst.mode);

  cycles_ += inst.cycles;

  switch (inst.shape) {
    case OpShape::Write:
    case OpShape::ReadModifyWrite:
      inst.execute(*this, addr);
      break;
    case OpShape::Read:
      inst.execute(*this, bus_->read(addr));
      if (crossed) cycles_++;
      break;
    case OpShape::Implied:
      inst.execute(*this, 0);
      break;
  }

  println("Executing instruction: {} {:02x} cyc={}", inst.op, inst.opcode, cycles_);
}

void Cpu::reset() { println("Resetting PC to {}", 1); }
