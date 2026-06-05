#include <sys/types.h>

#include <cstdint>

#include "Bus.hpp"

namespace Nestun {

// Forward declaration
class Cpu;

/*
 * Flags go like so
 *  0 0 1 0 0 1 0 0
 *  N V U B D I Z C
 *
 *  C - Carry Flag
 *  Z - Zero flag
 *  I - Interrupt disabled
 *  D - Decimal flag (Unused)
 *  B - Break (not a flag per se)
 *  U - Unused
 *  V - Overflow flag
 *  N - Negative
 * */
struct StatusFlags {
  uint8_t value = 0x24;  // I + U are set

  enum : uint8_t {
    C = 1 << 0,
    Z = 1 << 1,
    I = 1 << 2,
    D = 1 << 3,
    B = 1 << 4,
    U = 1 << 5,
    V = 1 << 6,
    N = 1 << 7,
  };

  [[nodiscard]] constexpr bool test(uint8_t mask) const { return (value & mask) != 0; }
  constexpr void set(uint8_t mask, bool on) { value = on ? (value | mask) : (value & ~mask); }

  [[nodiscard]] constexpr bool c() const { return (value & C) != 0; }
  [[nodiscard]] constexpr bool z() const { return (value & Z) != 0; }
  [[nodiscard]] constexpr bool i() const { return (value & I) != 0; }
  [[nodiscard]] constexpr bool d() const { return (value & D) != 0; }
  [[nodiscard]] constexpr bool b() const { return (value & B) != 0; }
  [[nodiscard]] constexpr bool u() const { return (value & U) != 0; }
  [[nodiscard]] constexpr bool v() const { return (value & V) != 0; }
  [[nodiscard]] constexpr bool n() const { return (value & N) != 0; }

  constexpr void set_c(bool b) { set(C, b); }
  constexpr void set_z(bool b) { set(Z, b); }
  constexpr void set_i(bool b) { set(I, b); }
  constexpr void set_d(bool b) { set(D, b); }
  constexpr void set_b(bool b) { set(B, b); }
  constexpr void set_u(bool b) { set(U, b); }
  constexpr void set_v(bool b) { set(V, b); }
  constexpr void set_n(bool b) { set(N, b); }

  constexpr void set_nz(uint8_t result) {
    set(Z, result == 0);
    set(N, (result & 0x80) != 0);
  }
};

enum class AddressingMode : uint8_t {
  Implied,
  Accumulator,
  Immediate,
  ZeroPage,
  ZeroPageX,
  ZeroPageY,
  Absolute,
  AbsoluteX,
  AbsoluteY,
  Indirect,
  IndirectX,
  IndirectY,
  Relative,
};

/*
 * This is simple
 * Implide -> an instruction that does something specific (CLC, BRK, etc.)
 * Read -> The operation reads from memory or register
 * Write -> The operation writes to memory or register
 * ReadModifyWrite -> This instruction reads a bit, modifies it, and then
 * writes the value back to memory. (I think mostly illegal op codes)
 */
enum class OpShape : uint8_t {
  Implied,
  Read,
  Write,
  ReadModifyWrite,
};

struct Instruction {
  AddressingMode mode;
  OpShape shape;
  uint8_t cycles;
  void (*execute)(Cpu& cpu, uint16_t address);
};

class Cpu {
  uint8_t A = 0, X = 0, Y = 0;
  uint8_t SP = 0xF0;
  uint16_t PC = 0;

  StatusFlags P;
  Bus* bus_;

  [[nodiscard]] uint8_t fetch();
  [[nodiscard]] Instruction decode(uint8_t op);
  uint8_t execute(Instruction instruction);
  void set_nz(uint8_t v) { P.set_nz(v); }

 public:
  static const std::array<Instruction, 256> TABLE;

  Cpu(Bus& bus) : bus_(&bus) {};

  void tick();
  void reset();
};

}  // namespace Nestun
