#pragma once
#include "mm_mtl/singleton.h"
#include "types.h"

namespace gf {

class GfBdatItem : public mm::mtl::PtrSingleton<GfBdatItem> {
public:
  u32 getEquipOrbEnhance(u32 orb) const;
};

} // namespace gf
