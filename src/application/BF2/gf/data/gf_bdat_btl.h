#pragma once
#include "mm_mtl/singleton.h"
#include "types.h"

namespace gf {

class GfBdatBtl : public mm::mtl::PtrSingleton<GfBdatBtl> {
public:
  u32 getArtsDrStart() const;
  u32 getArtsDrEnd() const;
  u32 getArtsDrDriver(u32 arts) const;
  u32 getArtsDrWpnType(u32 arts) const;
  bool isArtsDrFlagNormal(u32 arts) const;
  u32 getArtsDrNeedWP(u32 arts, u32 level) const;
  u32 getArtsDrReleaseLv(u32 arts, u32 level) const;
  u32 getArtsDrName(u32 arts) const;
  u32 getArtsDrCaption(u32 arts) const;
  u32 getArtsDrUI(u32 arts) const;
  const char *getArtsDrDebugName(u32 arts) const;
  u32 getArtsDrRangeType(u32 arts) const;
  u32 getArtsDrReAct(u32 arts, u32 level) const;
  u32 getArtsDrDmgMgn(u32 arts, u32 level) const;
  u32 getArtsDrRecast(u32 arts, u32 level) const;
  u32 getArtsDrEnhance(u32 arts, u32 level) const;
  u32 getArtsDrArtsType(u32 arts) const;
};

} // namespace gf
