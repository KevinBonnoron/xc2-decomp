#pragma once
#include "mm_mtl/singleton.h"
#include "types.h"

namespace gf {

class GfBdatChrDr : public mm::mtl::PtrSingleton<GfBdatChrDr> {
public:
  u32 getChrDrStart() const;
  u32 getChrDrEnd() const;
  u32 getChrDrDefBlade(u32 driver, u32 slot) const;
  u32 getChrDrDefBlade1(u32 driver) const;
  const char *getChrDrDebugName(u32 driver) const;
  u32 getChrDrRace(u32 driver) const;
  const char *getChrDrModel(u32 driver) const;
  const char *getChrDrMotion(u32 driver) const;
  u32 getChrDrAiID(u32 driver) const;
  u32 getChrDrWpnType(u32 driver, u32 slot) const;
  const char *getChrDrVoice(u32 driver) const;
  u32 getChrDrEyeRot(u32 driver) const;
  u32 getChrDrFootStep(u32 driver) const;
  u32 getChrDrFootStepEffect(u32 driver) const;
  u32 getChrDrFavoriteCategory(u32 driver, u32 favorite) const;
  u32 getChrDrFavoriteItem(u32 driver, u32 favorite) const;
};

} // namespace gf
