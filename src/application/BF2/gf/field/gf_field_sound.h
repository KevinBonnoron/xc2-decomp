#pragma once
#include "mm_mtl/fixstr.h"
#include "mm_mtl/singleton.h"
#include "types.h"
#include <stddef.h>

namespace gf {

class GfFieldSound : public mm::mtl::PtrSingleton<GfFieldSound> {
public:
  u8 _08[0xc4 - 0x08];
  mm::mtl::FixStr<64> mapSePackName;
};

static_assert(offsetof(GfFieldSound, mapSePackName) == 0xc4, "");

} // namespace gf
