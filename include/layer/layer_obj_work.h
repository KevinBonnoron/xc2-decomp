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
  u32 m_textureMax;
  u8 _28c[0x2a0 - 0x28c];
  f32 m_parm;
  u16 m_iconNum;
  u16 m_iconMax;
  u16 m_gauge;
  u8 _2aa[0x2ac - 0x2aa];
  u32 m_dataType;
};

static_assert(offsetof(LayerObjWork, m_textureMax) == 0x288, "");
static_assert(offsetof(LayerObjWork, m_parm) == 0x2a0, "");
static_assert(offsetof(LayerObjWork, m_gauge) == 0x2a8, "");
static_assert(offsetof(LayerObjWork, m_dataType) == 0x2ac, "");

} // namespace layer
