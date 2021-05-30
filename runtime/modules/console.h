#include "../datatypes.hpp"

namespace device_type {
class console : device {
  uint16_t out() override;
  void in(uint16_t data) override;
  uint16_t run() override;
  ~console();
};

} // namespace device_type