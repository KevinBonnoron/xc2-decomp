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
};

} // namespace gf
