#pragma once
#include "types.h"

namespace mm {
struct Col3;
struct Col4;
struct Mat44;
} // namespace mm

namespace layer {

class LayerBase;

enum LayerCenterType {
  LAYER_CENTER_TYPE_TOP_LEFT = 0,
  LAYER_CENTER_TYPE_CENTER = 2,
};

enum LayerBlendType {
  LAYER_BLEND_TYPE_NORMAL = 0,
  LAYER_BLEND_TYPE_ADD = 1,
};
enum LayerTexFilterType {
  LAYER_TEX_FILTER_TYPE_NEAREST = 0,
  LAYER_TEX_FILTER_TYPE_LINEAR = 1,
};
enum LayerFlipType {
  LAYER_FLIP_TYPE_HORIZONTAL = 0,
  LAYER_FLIP_TYPE_VERTICAL = 1,
};

class LayerAccObjBase {
public:
  LayerAccObjBase(LayerBase *layer);
  void setPos(f32 x, f32 y);
  void setRot(f32 rot);
  void setScale(f32 x, f32 y);
  void setMulCol(const mm::Col4 &color);
  void setAddCol(const mm::Col3 &color);
  void setMatrix(const mm::Mat44 &matrix);
  void getPos(f32 &x, f32 &y) const;
  void getRot(f32 &rot) const;
  void getScale(f32 &x, f32 &y) const;
  const mm::Col4 &getMulCol() const;
  const mm::Col3 &getAddCol() const;
  const mm::Mat44 &getMatrix() const;
  void setBlendType(LayerBlendType type);
  void setTexFilterType(LayerTexFilterType type);
  void setPriority(u16 priority);
  void setDisp(bool disp);
  bool isDisp() const;
  void setFlip(LayerFlipType type, bool flip);
  u16 getPixelWidth() const;
  u16 getPixelHeight() const;
  void setCenterType(LayerCenterType type);
  LayerCenterType getCenterType() const;
  void setMaskObj(const LayerBase *mask);
  void resetMaskObj();
  const void *getResData() const;

  LayerBase *layer;
};

} // namespace layer
