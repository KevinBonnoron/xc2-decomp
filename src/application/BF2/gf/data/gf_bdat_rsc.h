#pragma once
#include "mm_mtl/singleton.h"
#include "types.h"

namespace gf {

class GfBdatRsc : public mm::mtl::PtrSingleton<GfBdatRsc> {
public:
  const char *getRscMobListModel(u32 mob) const;
  u8 getRscMobListRace(u32 mob) const;
  const char *getRscMobListMotion(u32 mob) const;
  const char *getRscMobListAddMotion(u32 mob) const;
  const char *getRscMobListComp_Eff(u32 mob) const;
  u16 getRscMobListFootStep(u32 mob) const;
  u8 getRscMobListFootStepEffect(u32 mob) const;
};

} // namespace gf
