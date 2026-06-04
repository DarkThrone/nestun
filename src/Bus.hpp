#include <array>
#include <cstdint>
#include <cstring>

namespace Nestun {
class Bus {
 private:
  std::array<uint8_t, 0x10000> mem;  // 64Kb of memory

 public:
  Bus() = default;
  [[nodiscard]] uint8_t read(uint16_t address) const;
  void write(uint16_t address, uint8_t value);

  void load_rom(std::string path);
};
}  // namespace Nestun
