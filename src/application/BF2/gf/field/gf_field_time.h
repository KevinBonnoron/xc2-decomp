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

struct GameTime;

class GfFieldTime : public mm::mtl::PtrSingleton<GfFieldTime> {
public:
  u32 getTimeRangeDN() const;
  const GameTime &getGameTime() const;
  const ElapseTime &getElapseTime() const;
  void setTimeRangeBit(u32 timeRangeBits);
  u32 getTimeRangeBits() const;
};

} // namespace gf
