#pragma once
#include "types.h"

namespace mm {
struct Col3;
struct Col4;
struct Mat44;
} // namespace mm

namespace layer {

class LayerBase;
class LayerObj;

enum LAYER_SPACE_TYPE {};

enum LayerCenterType {
  LAYER_CENTER_TYPE_TOP_LEFT = 0,
  LAYER_CENTER_TYPE_UNKNOWN_1 = 1,
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
  void setSpace(LAYER_SPACE_TYPE space);
  void setPos(f32 x, f32 y);
  void setRot(f32 rot);
  void setScale(f32 x, f32 y);
  void setAnchor(f32 x, f32 y);
  void setMulCol(const mm::Col4 &color);
  void setAddCol(const mm::Col3 &color);
  void setMatrix(const mm::Mat44 &matrix);
  void setUVParams(f32 u, f32 v, f32 scaleU, f32 scaleV, f32 rot);
  void getUVParams(f32 &u, f32 &v, f32 &scaleU, f32 &scaleV, f32 &rot);
  void getPos(f32 &x, f32 &y) const;
  void getRot(f32 &rot) const;
  void getScale(f32 &x, f32 &y) const;
  void getAnchor(f32 &x, f32 &y) const;
  const mm::Col4 &getMulCol() const;
  const mm::Col3 &getAddCol() const;
  const mm::Mat44 &getMatrix() const;
  void setBlendType(LayerBlendType type);
  LayerBlendType getBlendType() const;
  void setTexFilterType(LayerTexFilterType type);
  LayerTexFilterType getTexFilterType() const;
  void setPriority(u16 priority);
  u16 getPriority() const;
  void setDisp(bool disp);
  bool isDisp() const;
  void setFlip(LayerFlipType type, bool flip);
  bool isFlip(LayerFlipType type) const;
  void setCtrlSpd(f32 speed);
  f32 getCtrlSpd() const;
  u16 getPixelX() const;
  u16 getPixelY() const;
  u16 getPixelWidth() const;
  u16 getPixelHeight() const;
  void setCenterType(LayerCenterType type);
  LayerCenterType getCenterType() const;
  void setMaskObj(const LayerBase *mask);
  void resetMaskObj();
  const void *getResData() const;
  void createAnimObj(u32 id);
  void endAnime();
  void createSecondTex(const void *data);
  void releaseSecondTex();
  u16 getSecondTexIconMax() const;
  void setSecondTexIconNum(u32 num);
  u16 getSecondTexIconNum() const;
  void setSecondTexBlend(f32 blend);
  f32 getSecondTexBlend() const;

  LayerObj *unknown00; // Inferred role: layer; original member name unknown.
};

} // namespace layer
