#pragma once
#include <stddef.h>

#include "layer/layer_obj.h"
#include "types.h"

namespace grlib {
class CGLibTextureBuffer;
} // namespace grlib

namespace layer {

class LayerObjTopMemObj : public LayerObj {
public:
  void *getBuffer();
  void updateBufer();
  void setRender(bool render);
  bool isRender() const;

  u8 _250[0x2e8 - 0x250];
  grlib::CGLibTextureBuffer *m_texture;
  u8 _2f0[0x740 - 0x2f0];
  u32 m_width;
  u32 m_height;
};

static_assert(offsetof(LayerObjTopMemObj, m_texture) == 0x2e8, "");
static_assert(offsetof(LayerObjTopMemObj, m_width) == 0x740, "");

} // namespace layer
