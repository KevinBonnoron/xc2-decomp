#pragma once
#include "mm_mtl/singleton.h"
#include "types.h"

namespace gf {

class GfMenuMapInfo : public mm::mtl::PtrSingleton<GfMenuMapInfo> {
public:
  static void setCurrentMap(u32 map);
};

} // namespace gf
