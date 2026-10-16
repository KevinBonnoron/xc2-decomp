#pragma once
#include "layer/layer_acc_obj_base.h"
#include "types.h"

namespace grlib {
class CGLibTextureBuffer;
} // namespace grlib

namespace layer {

class LayerBase;
class LayerObjTopMemObj;

class LayerAccMemObj : public LayerAccObjBase {
public:
  LayerAccMemObj(LayerBase *layer);
  void *getMemBufer();
  void updateMemBufer();
  u16 getMemWidth() const;
  u16 getMemHeight() const;
  void setRender(bool render);
  bool isRender() const;
  grlib::CGLibTextureBuffer *getTexture();

  LayerObjTopMemObj *m_memObj;
};

} // namespace layer
