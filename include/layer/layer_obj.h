#pragma once
#include <stddef.h>

#include "layer/layer_acc_obj_base.h"
#include "layer/layer_base.h"
#include "layer/layer_manager.h"
#include "mm_math/mm_col3.h"
#include "mm_math/mm_col4.h"
#include "mm_math/mm_mat44.h"
#include "types.h"

namespace grlib {
class CGLibDblUniformBlock;
} // namespace grlib

namespace layer {

class LayerAnimeObj;
class LayerResSecTexture;

struct LayerResMatrix {
  f32 posX;
  f32 posY;
  f32 rot;
  f32 sclX;
  f32 sclY;
  f32 anchorX;
  f32 anchorY;
};

static_assert(sizeof(LayerResMatrix) == 0x1c, "");

struct LayerResColor {
  mm::Col4 mulCol;
  mm::Col3 addCol;
};

static_assert(sizeof(LayerResColor) == 0x1c, "");

struct LayerResParmInfo {
  LayerResMatrix matrix;
  LayerResColor color;
};

static_assert(sizeof(LayerResParmInfo) == 0x38, "");

struct LayerResUvParam {
  f32 u;
  f32 v;
  f32 scaleU;
  f32 scaleV;
  f32 rot;
};

static_assert(sizeof(LayerResUvParam) == 0x14, "");

class LayerObj : public LayerBase {
public:
  void setInitPos(f32 x, f32 y);
  void setInitRot(f32 rot);
  void setInitScl(f32 x, f32 y);
  void setInitPosScl(f32 x, f32 y, f32 sclX, f32 sclY);
  void setInitMulCol(const mm::Col4 &color);
  void setInitAddCol(const mm::Col3 &color);
  void updateCtrlSpd(f32 speed);
  void updateAnimObj();
  void updateSecondTex();
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
  const mm::Col4 *getMulCol() const;
  const mm::Col3 *getAddCol() const;
  const mm::Mat44 *getMatrix() const;
  void setDisp(bool disp);
  bool isDisp() const;
  void setFlip(LayerFlipType type, bool flip);
  bool isFlip(LayerFlipType type) const;
  void createAnimObj(u32 id);
  void endAnime();
  void createSecondTex(const void *data);
  void releaseSecondTex();
  const LayerResSecTexture *getSecondTexObj() const;
  u16 getSecondTexIconMax() const;
  void setSecondTexIconNum(u32 num);
  u16 getSecondTexIconNum() const;
  void setSecondTexBlend(f32 blend);
  f32 getSecondTexBlend() const;
  u32 getStateFlags(u32 index) const { return m_stateFlags[index]; }
  void onStateFlags(u32 flags) {
    u32 index = LayerManager::s_nStkIdx;
    m_stateFlags[index] |= flags;
  }
  void offStateFlags(u32 flags) {
    u32 index = LayerManager::s_nStkIdx;
    m_stateFlags[index] &= ~flags;
  }

  u8 _1c[0x20 - 0x1c];
  mm::Mat44 m_matrices[2];
  u32 m_stateFlags[2];
  u32 m_flags;
  u8 _ac[0xb8 - 0xac];
  const void *m_resData;
  u16 m_priority;
  u8 m_matrixIdx;
  u8 m_space;
  u8 m_blendType;
  u8 _c5[0xc6 - 0xc5];
  u8 m_texFilterType;
  LayerResParmInfo m_parms[3];
  u8 _170[0x190 - 0x170];
  u16 m_pixelX;
  u16 m_pixelY;
  u16 m_pixelWidth;
  u16 m_pixelHeight;
  u8 m_centerType;
  LayerResUvParam m_uvParams[3];
  u16 m_actionIdx[2];
  u8 _1dc[0x1f4 - 0x1dc];
  f32 m_ctrlSpd;
  f32 m_frameCtrlSpd;
  u8 _1fc[0x208 - 0x1fc];
  LayerAnimeObj *m_animObjs[3];
  LayerResSecTexture *m_secondTexs[3];
  grlib::CGLibDblUniformBlock *m_worldMatrixUniform;
  const LayerBase *m_maskObj;
  u8 _248[0x250 - 0x248];
};

static_assert(offsetof(LayerObj, m_matrices) == 0x20, "");
static_assert(offsetof(LayerObj, m_stateFlags) == 0xa0, "");
static_assert(offsetof(LayerObj, m_flags) == 0xa8, "");
static_assert(offsetof(LayerObj, m_resData) == 0xb8, "");
static_assert(offsetof(LayerObj, m_priority) == 0xc0, "");
static_assert(offsetof(LayerObj, m_matrixIdx) == 0xc2, "");
static_assert(offsetof(LayerObj, m_space) == 0xc3, "");
static_assert(offsetof(LayerObj, m_blendType) == 0xc4, "");
static_assert(offsetof(LayerObj, m_texFilterType) == 0xc6, "");
static_assert(offsetof(LayerObj, m_parms) == 0xc8, "");
static_assert(offsetof(LayerObj, m_pixelX) == 0x190, "");
static_assert(offsetof(LayerObj, m_centerType) == 0x198, "");
static_assert(offsetof(LayerObj, m_uvParams) == 0x19c, "");
static_assert(offsetof(LayerObj, m_actionIdx) == 0x1d8, "");
static_assert(offsetof(LayerObj, m_ctrlSpd) == 0x1f4, "");
static_assert(offsetof(LayerObj, m_animObjs) == 0x208, "");
static_assert(offsetof(LayerObj, m_secondTexs) == 0x220, "");
static_assert(offsetof(LayerObj, m_worldMatrixUniform) == 0x238, "");
static_assert(offsetof(LayerObj, m_maskObj) == 0x240, "");
static_assert(sizeof(LayerObj) == 0x250, "");

} // namespace layer
