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
  f32 unknown00; // Inferred role: x; original member name unknown.
  f32 unknown04; // Inferred role: y; original member name unknown.
  u8 unknown08;  // Inferred role: r; original member name unknown.
  u8 unknown09;  // Inferred role: g; original member name unknown.
  u8 unknown0a;  // Inferred role: b; original member name unknown.
  u8 unknown0b;  // Inferred role: a; original member name unknown.
  f32 unknown0c; // Inferred role: u; original member name unknown.
  f32 unknown10; // Inferred role: v; original member name unknown.
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
