#pragma once
#include "layer/layer_acc_obj_base.h"
#include "types.h"

namespace grlib {
class CGLibTextureBuffer;
} // namespace grlib

namespace layer {

class LayerBase;
class LayerObjTopPolyObj;
struct LayerPolyVertex;

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
