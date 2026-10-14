#pragma once
#include "types.h"

namespace gf {

struct SDataDriver;

class GfEquipUtil {
public:
  static u32 getEquipAcceResult(const SDataDriver &dataDriver, u32 slot, u32 accessory);
};

} // namespace gf
