#include <cstdint>
#include <sys/types.h>

/*
 * Flags go like so
 *  0 0 1 0 0 1 0 0
 *  N V - B D I Z C
 *
 * */
struct StatusFlags {
  uint8_t value = 0x24; // I + U are set

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

  constexpr bool test(uint8_t mask) const { return value & mask; }
  constexpr void set(uint8_t mask, bool on) {
    value = on ? (value | mask) : (value & ~mask);
  }

  constexpr bool c() const { return value & C; }
  constexpr bool z() const { return value & Z; }
  constexpr bool i() const { return value & I; }
  constexpr bool d() const { return value & D; }
  constexpr bool b() const { return value & B; }
  constexpr bool u() const { return value & U; }
  constexpr bool v() const { return value & V; }
  constexpr bool n() const { return value & N; }

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
    set(N, result & 0x80);
  }
};

class Cpu {
public:
  uint8_t A = 0, X = 0, Y = 0;
  uint8_t SP = 0xF0;
  uint16_t PC = 0;

  StatusFlags P;

private:
  void set_nz(uint8_t v) { P.set_nz(v); }
};
