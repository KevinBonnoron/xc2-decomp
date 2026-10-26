#pragma once
#include <stddef.h>

#include "grlib/cglib_depth_target.h"
#include "types.h"

namespace ml {

class DrPixlShadowCacheObj : public grlib::CGLibDepthTarget {
public:
  void release();
  void end();
  void setClear();
  void setNewGrid();
  void setBigMode(bool isBig);
  void setID(int id);

  u8 _128[0x808 - 0x128];
  u32 unknown808; // Inferred role: flags; original member name unknown.
  u8 _80c[0x8e8 - 0x80c];
  u64 unknown8e8; // Inferred role: id mask; original member name unknown.
  u16 unknown8f0; // Inferred role: id; original member name unknown.
  u16 unknown8f2; // Inferred role: id; original member name unknown.
};

static_assert(offsetof(DrPixlShadowCacheObj, unknown808) == 0x808, "");
static_assert(offsetof(DrPixlShadowCacheObj, unknown8e8) == 0x8e8, "");
static_assert(offsetof(DrPixlShadowCacheObj, unknown8f2) == 0x8f2, "");

} // namespace ml
