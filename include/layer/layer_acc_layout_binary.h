#pragma once
#include "types.h"

namespace layer {

class LayerObj;

class LayerAccLayoutBinary {
public:
  LayerAccLayoutBinary(const void *data);
  u32 getPosIdx(const char *name) const;
  void setLayoutPosData(f32 &x, f32 &y, f32 &width, f32 &height, u32 index);
  void setLayoutPosData(f32 &x, f32 &y, f32 &width, f32 &height, const char *name);
  void setLayoutObj(LayerObj *object, const char *name, bool initScale);

  u8 _00[0x28];
};

} // namespace layer
