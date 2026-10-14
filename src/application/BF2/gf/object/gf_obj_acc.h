#pragma once
#include "types.h"

namespace gf {

struct GF_OBJ_HANDLE;

class GfObjAcc {
public:
  GfObjAcc(GF_OBJ_HANDLE *handle);
  u32 getDriverId() const;
  u32 getBladeId() const;
  u32 getPcWeaponId() const;

  u8 _00[0x10];
};

} // namespace gf
