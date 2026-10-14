#pragma once
#include "types.h"

namespace gf {

struct GF_OBJ_HANDLE;
class GfObj;

class GfObjAcc {
public:
  GfObjAcc(GF_OBJ_HANDLE *handle);

  bool isValid() const { return mObj != nullptr; }
  bool testFlag(u32 flag) const;
  bool isDestroy() const;
  u32 getDriverId() const;
  u32 getBladeId() const;
  u32 getPcWeaponId() const;
  void setExtMeshAlpha(u32 index, f32 alpha);
  int getExtMeshIdx(const char *name) const;
  bool isBattle() const;

private:
  u8 _00[0x08 - 0x00];
  GfObj *mObj;
};

static_assert(sizeof(GfObjAcc) == 0x10, "");

} // namespace gf
