#pragma once
#include "mm_mtl/singleton.h"
#include "types.h"

namespace gf {

class GfBdatChrBl : public mm::mtl::PtrSingleton<GfBdatChrBl> {
public:
  u32 getChrBlStart() const;
  u32 getChrBlEnd() const;
};

} // namespace gf
