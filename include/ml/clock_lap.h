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

  s64 unknown08;  // Inferred role: begin clock; original member name unknown.
  s64 *unknown10; // Inferred role: lap starts; original member name unknown.
  s64 *unknown18; // Inferred role: lap ends; original member name unknown.
  u32 *unknown20; // Inferred role: lap colors; original member name unknown.
  u32 unknown28;  // Inferred role: lap max; original member name unknown.
  u32 unknown2c;  // Inferred role: lap index; original member name unknown.
  void *m_buffer;
};

static_assert(offsetof(ClockLap, unknown08) == 0x08, "");
static_assert(offsetof(ClockLap, unknown28) == 0x28, "");
static_assert(offsetof(ClockLap, m_buffer) == 0x30, "");

} // namespace ml
