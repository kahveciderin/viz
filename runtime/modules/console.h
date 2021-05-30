#include "../datatypes.h"
class console:device{
    uint16_t out() override;
    void in(uint16_t data) override;
};