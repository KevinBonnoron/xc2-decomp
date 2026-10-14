#pragma once
#include "mm_mtl/singleton.h"
#include "types.h"

namespace gf {

class GfBdatChrEnArrange : public mm::mtl::PtrSingleton<GfBdatChrEnArrange> {
public:
  u32 getChrEnArrangeStart() const;
  u32 getChrEnArrangeEnd() const;
  u32 getChrEnArrangeName(u32 arrange) const;
  u32 getChrEnArrangeParamID(u32 arrange) const;
  u32 getChrEnArrangeBladeID(u32 arrange) const;
  u32 getChrEnArrangeEnemyBladeID(u32 arrange) const;
  u32 getChrEnArrangeBookID(u32 arrange) const;
  bool isChrEnArrangeFlagNamed(u32 arrange) const;
  bool isChrEnArrangeFlagmBoss(u32 arrange) const;
  u32 getChrEnArrangeHpOver(u32 arrange) const;
  u32 getBTL_EnBookBaseEnemyID(u32 book) const;
  u32 getBTL_EnBookBOOK_POP_TIME(u32 book) const;
  u32 getBTL_EnBookBOOK_popWeather(u32 book) const;
};

} // namespace gf
