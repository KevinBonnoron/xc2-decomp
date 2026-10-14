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

  const char *getRSC_PcWpnModel(u32 weapon) const;
  const char *getRSC_PcWpnMotion(u32 weapon) const;

  const char *getRscEnVoice(u32 resource) const;
  const char *getRscEnRefMotion(u32 resource) const;
  const char *getRscEnModel(u32 resource) const;
  const char *getRscEnMotion(u32 resource) const;
  const char *getRscEnSePack(u32 resource) const;
  const char *getRscEnLoopEffect(u32 resource) const;
  u32 getRscEnExtraParts(u32 resource, u32 part) const;
  u32 getRscEnDrType(u32 resource) const;
};

} // namespace gf
