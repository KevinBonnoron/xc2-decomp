#pragma once
#include <stddef.h>

#include "types.h"

namespace mtl {
class ALLOC_HANDLE;
} // namespace mtl

namespace ml {

class ClockLap {
public:
  virtual ~ClockLap();
  void setup(mtl::ALLOC_HANDLE handle, u32 lapMax);
  void begin();
  bool lapS(u32 color);
  void lapE();
  const s64 &getLapS(u32 index) const;
  const s64 &getLapE(u32 index) const;
  u32 getLapCol(u32 index) const;

  s64 m_beginClock;
  s64 *m_lapStarts;
  s64 *m_lapEnds;
  u32 *m_lapColors;
  u32 m_lapMax;
  u32 m_lapIndex;
  void *m_buffer;
};

static_assert(offsetof(ClockLap, m_beginClock) == 0x08, "");
static_assert(offsetof(ClockLap, m_lapMax) == 0x28, "");
static_assert(offsetof(ClockLap, m_buffer) == 0x30, "");

} // namespace ml
