#pragma once
#include "mm_mtl/singleton.h"
#include "types.h"

namespace gf {

class GfBdatItem : public mm::mtl::PtrSingleton<GfBdatItem> {
public:
  u32 getPcWpnName(u32 weapon) const;
  u32 getPcWpnWpnType(u32 weapon) const;
  u32 getPcWpnChipCreateWpn(u32 chip, u32 weaponType) const;
  u32 getPcWpnDamage(u32 weapon) const;
  u32 getPcWpnGuardRate(u32 weapon) const;
  u32 getPcWpnCriRate(u32 weapon) const;
  u32 getPcWpnStability(u32 weapon) const;
  u32 getPcWpnEnhance1(u32 weapon) const;
  u32 getPcWpnRank(u32 weapon) const;
  u32 getPcWpnTypeName(u32 weaponType) const;
  u32 getPcWpnTypeMotion(u32 weaponType) const;

  u32 getEquipOrbEnhance(u32 orb) const;
};

} // namespace gf
