#pragma once
#include <array>
#include <cstdint>
#include <cstring>

namespace Nestun {
class Bus {
 private:
  std::array<uint8_t, 0x10000> mem;  // 64Kb of memory

 public:
  Bus() = default;
  [[nodiscard]] uint8_t read(uint16_t) const;
  void write(uint16_t, uint8_t);
  void clear();

  void load_rom(const std::string&);
};
}  // namespace Nestun
