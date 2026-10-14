#pragma once
#include "mm_mtl/singleton.h"
#include "types.h"

namespace gf {

struct ElapseTime {
  u32 second : 6;
  u32 minute : 6;
  u32 hour : 20;
};

static_assert(sizeof(ElapseTime) == 4, "");

class GfFieldTime : public mm::mtl::PtrSingleton<GfFieldTime> {
public:
  void setTimeRangeBit(u32 timeRangeBits);
  u32 getTimeRangeBits() const;
};

} // namespace gf
