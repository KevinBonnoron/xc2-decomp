#pragma once
#include "layer/layer_obj.h"
#include "types.h"

namespace grlib {
class CGLibTextureBuffer;
} // namespace grlib

namespace layer {

struct LayerPolyVertex;

class LayerObjTopPolyObj : public LayerObj {
public:
  void LockVertex();
  void setVertex(u32 index, const LayerPolyVertex &vertex);
  void UnlockVertex();
  void LockIndex();
  void setIndex(u32 index, u16 vertexIndex);
  void UnlockIndex();
  void setTexutre(const void *data);
  void setTexutre(grlib::CGLibTextureBuffer &texture);
  void resetTexutre();
  void setIndexInfo(u16 start, u16 num);
};

} // namespace layer
