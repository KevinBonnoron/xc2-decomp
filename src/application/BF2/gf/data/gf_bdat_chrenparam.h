#pragma once
#include "mm_mtl/singleton.h"
#include "types.h"

namespace gf {

class GfBdatChrEnParam : public mm::mtl::PtrSingleton<GfBdatChrEnParam> {
public:
  u32 getChrEnParamResourceID(u32 param) const;
};

} // namespace gf
