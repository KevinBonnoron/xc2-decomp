#pragma once
#include "layer/layer_acc_obj_base.h"
#include "types.h"

namespace grlib {
class CGLibTextureBuffer;
} // namespace grlib

namespace layer {

class LayerBase;
class LayerObjTopPolyObj;
struct LayerPolyVertex {
  f32 x;
  f32 y;
  u8 r;
  u8 g;
  u8 b;
  u8 a;
  f32 u;
  f32 v;
};

static_assert(sizeof(LayerPolyVertex) == 0x14, "");

class LayerAccPolyObj : public LayerAccObjBase {
public:
  LayerAccPolyObj(LayerBase *layer);
  void LockVertex();
  void setVertex(u32 index, const LayerPolyVertex &vertex);
  void UnlockVertex();
  void LockIndex();
  void setIndex(u32 index, u16 vertexIndex);
  void UnlockIndex();
  void setIndexInfo(u16 start, u16 num);
  void setTexutre(const void *data);
  void setTexutre(grlib::CGLibTextureBuffer &texture);
  void resetTexutre();

  LayerObjTopPolyObj *m_polyObj;
};

} // namespace layer
