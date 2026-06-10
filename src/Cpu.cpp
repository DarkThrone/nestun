#include "../include/Cpu.hpp"

#include <cstdint>
#include <format>
#include <print>

using namespace Nestun;
using namespace std;

pair<uint16_t, bool> Cpu::resolve(AddressingMode mode) {
  switch (mode) {
    case AddressingMode::Immediate:
      return make_pair(PC++, false);
    case AddressingMode::ZeroPage:
      return make_pair(bus_->read(PC++) & 0xFF, false);
    case AddressingMode::Absolute: {
      uint8_t lo = bus_->read(PC++);
      uint8_t hi = bus_->read(PC++);

      auto value = static_cast<uint16_t>(lo | (hi << 8));
      return make_pair(value, false);
    }
    case AddressingMode::Indirect: {
      // The 6502's memory indirect jump instruction, JMP (<address>), has a nonintuitive limitation
      // which many users consider a defect. If <address> is hex xxFF (i.e., any word ending in FF),
      // the processor will not jump to the address stored in xxFF and xxFF+1 as expected, but
      // rather the one defined by xxFF and xx00 (for example, JMP ($10FF) would jump to the address
      // stored in 10FF and 1000, instead of the one stored in 10FF and 1100). This can be avoided
      // simply by not placing any indirect jump target address across a page boundary, and the MOS
      // Technology MCS6500 Programming Manual gives reason to believe that this was the intention
      // of the designers of the 6502, in order to save space on the chip that would have been used
      // to implement the more complex behavior of conditionally adding 1 clock cycle to propagate
      // the carry when necessary. This ostensible defect continued through the entire NMOS line but
      // was corrected in the CMOS derivatives.
      uint8_t lo = bus_->read(PC++);
      uint8_t hi = bus_->read(PC++);

      auto ptr = static_cast<uint16_t>(lo | (hi << 8));
      auto value = bus_->read(ptr);
      return make_pair(value, false);
    }
    case AddressingMode::Relative: {
      uint16_t address = bus_->read(PC++);
      return make_pair(address + PC, false);
    }
    case AddressingMode::ZeroPageX:
    case AddressingMode::ZeroPageY:
    case AddressingMode::AbsoluteX:
    case AddressingMode::AbsoluteY:
    case AddressingMode::IndirectX:
    case AddressingMode::IndirectY:

    case AddressingMode::Implicit:
    case AddressingMode::Accumulator:
      return make_pair(0, false);
  }
  return make_pair(0, false);
};

uint8_t Cpu::getA() const { return A; }
uint8_t Cpu::getX() const { return A; }
uint8_t Cpu::getY() const { return A; }
uint8_t Cpu::getSP() const { return A; }
uint16_t Cpu::getPC() const { return A; }

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
