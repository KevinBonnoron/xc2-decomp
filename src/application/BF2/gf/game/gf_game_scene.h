#pragma once
#include "mm_mtl/singleton.h"
#include "types.h"

namespace gf {

struct GF_OBJ_HANDLE;

class GfGameScene : public mm::mtl::PtrSingleton<GfGameScene> {
public:
  void setDamageCharacter(GF_OBJ_HANDLE *handle);
  void setCameraAvtivateOneTime();
  void setRideOn(u32 partyId);
};

} // namespace gf
