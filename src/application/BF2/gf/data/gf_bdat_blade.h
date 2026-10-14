#pragma once
#include "mm_mtl/singleton.h"
#include "types.h"

namespace gf {

class GfBdatBlade : public mm::mtl::PtrSingleton<GfBdatBlade> {
public:
  u32 getBLD_IdeaNeedPoint(u32 level) const;
};

} // namespace gf
