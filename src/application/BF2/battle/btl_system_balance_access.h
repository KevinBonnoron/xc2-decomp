#pragma once
#include "mm_mtl/singleton.h"
#include "types.h"
#include <stddef.h>

namespace btl {

class BtlSystemBalanceAccess : public mm::mtl::PtrSingleton<BtlSystemBalanceAccess> {
public:
  u8 _08[0x40 - 0x08];
  u8 resistantAttrMaxHP;
  u8 _41[0xdc - 0x41];
  f32 dyingHpRate;
};

static_assert(offsetof(BtlSystemBalanceAccess, resistantAttrMaxHP) == 0x40, "");
static_assert(offsetof(BtlSystemBalanceAccess, dyingHpRate) == 0xdc, "");

} // namespace btl
