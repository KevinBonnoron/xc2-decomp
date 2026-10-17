#pragma once
#include "layer/layer_acc_obj_base.h"
#include "layer/layer_obj_manager.h"
#include "types.h"

namespace mm {
struct Col4;
} // namespace mm

namespace grlib {
class CGLibTextureBuffer;
}

namespace layer {

class LayerBase;

enum LAYER_ANCHOR {};

class LayerAccLayoutObj : public LayerAccObjBase {
public:
  LayerAccLayoutObj(LayerBase *layer);
  void setViewPortMode(bool viewPortMode);
  void setViewPort(f32 x, f32 y, f32 width, f32 height);
  void createRenderTarget(f32 x, f32 y, f32 width, f32 height, mm::Col4 clearColor);
  void releaseRenderTarget();
  void createPriorityTbl(u32 num);
  void releasePriorityTbl();
  u16 getPriorityTbl() const;
  void setAutoAnchorMode(LAYER_ANCHOR mode);
  LAYER_ANCHOR getAutoAnchorMode() const;
  grlib::CGLibTextureBuffer *getTexture();
  void setRender(bool render);
  bool isRender() const;
  LayerBase *createObj(const void *data);
  LayerBase *createFontObj();
  LayerBase *createMaskObj(const void *data);
  LayerBase *createTexObj(const grlib::CGLibTextureBuffer &texture);
  LayerBase *createMemObj(u32 width, u32 height, LayerMemType type);
  LayerBase *createPolyObj(u32 width, u32 height, u16 vertexNum, u16 indexNum, LayerPrimitiveType type);

  u8 _08[0x10 - 0x08];
};

static_assert(sizeof(LayerAccLayoutObj) == 0x10, "");

} // namespace layer
