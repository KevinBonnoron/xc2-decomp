#pragma once
#include <stddef.h>

#include "layer/layer_act_base.h"
#include "types.h"

namespace grlib {
class CGLibTextureBuffer;
} // namespace grlib

namespace layer {

class LayerObjWork : public LayerActBase {
public:
  f32 getMaxSecond() const;
  f32 getSecond() const;
  void setSecond(f32 second);
  void setAddTexture(const void *data, u32 index);
  void resetAddTexutre(u32 index);
  void setAddTexture(grlib::CGLibTextureBuffer &texture, u32 index);
  void resetAddAllTexutre();

  u8 _258[0x288 - 0x258];
  u32 unknown288; // Inferred role: texture max; original member name unknown.
  u8 _28c[0x2a0 - 0x28c];
  f32 unknown2a0; // Inferred role: parm; original member name unknown.
  u16 unknown2a4; // Inferred role: icon num; original member name unknown.
  u16 unknown2a6; // Inferred role: icon max; original member name unknown.
  u16 unknown2a8; // Inferred role: gauge; original member name unknown.
  u8 _2aa[0x2ac - 0x2aa];
  u32 unknown2ac; // Inferred role: data type; original member name unknown.
};

static_assert(offsetof(LayerObjWork, unknown288) == 0x288, "");
static_assert(offsetof(LayerObjWork, unknown2a0) == 0x2a0, "");
static_assert(offsetof(LayerObjWork, unknown2a8) == 0x2a8, "");
static_assert(offsetof(LayerObjWork, unknown2ac) == 0x2ac, "");

} // namespace layer
