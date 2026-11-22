#pragma once
#include <stddef.h>

#include "layer/layer_acc_obj_base.h"
#include "layer/layer_base.h"
#include "layer/layer_manager.h"
#include "layer/layer_obj_util.h"
#include "mm_math/mm_col3.h"
#include "mm_math/mm_col4.h"
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_pnt.h"
#include "types.h"

namespace grlib {
class CGLibDblUniformBlock;
class CGLibRenderTarget;
} // namespace grlib

namespace layer {

class LayerAnimeObj;
class LayerObjTopMaskObj;
struct LayerRenderView;
class LayerResSecTexture;
class LayerSortMan;

// Evidence: LayerObjUtil::calcLayerMatrix and updateMatrixUniformBlock read six floats, and
// LayerObjTopDef::update builds one in six stack floats (0x18 bytes).
struct LayerResMatrix {
  f32 unknown00; // Inferred role: translation x; original member name unknown.
  f32 unknown04; // Inferred role: translation y; original member name unknown.
  f32 unknown08; // Inferred role: matrix row 0 column 0; original member name unknown.
  f32 unknown0c; // Inferred role: matrix row 1 column 1; original member name unknown.
  f32 unknown10; // Inferred role: matrix row 1 column 0; original member name unknown.
  f32 unknown14; // Inferred role: matrix row 0 column 1; original member name unknown.
};

static_assert(sizeof(LayerResMatrix) == 0x18, "");

struct LayerResColor {
  mm::Col4 m_mulCol; // Inferred role: mul col; named after the game accessor layer::LayerObj::getMulCol.
  mm::Col3 m_addCol; // Inferred role: add col; named after the game accessor layer::LayerObj::getAddCol.
};

static_assert(sizeof(LayerResColor) == 0x1c, "");

struct LayerResParmInfo {
  LayerBasePos m_layerBasePos;   // Inferred role: pos, rot, scale and anchor; original member name unknown.
  LayerResColor m_layerResColor; // Inferred role: color; original member name unknown.
};

static_assert(sizeof(LayerResParmInfo) == 0x38, "");

// Inferred layout of the uv parameters of one buffer; original type and member names unknown.
struct unknown023 {
  mm::Pnt<f32> unknown00; // Inferred role: u and v; original member name unknown.
  f32 unknown08;          // Inferred role: scale u; original member name unknown.
  f32 unknown0c;          // Inferred role: scale v; original member name unknown.
  f32 unknown10;          // Inferred role: rot; original member name unknown.
};

static_assert(sizeof(unknown023) == 0x14, "");

// Evidence: LayerObjUtil::updateUvCalcUniformBlock takes it by reference and reads the third buffer at +0x28.
struct LayerResUvParam {
  unknown023 unknown00[3]; // Inferred role: uv params per buffer; original member name unknown.
};

static_assert(sizeof(LayerResUvParam) == 0x3c, "");

// Evidence: LayerObj::applyBegin and applyEnd read it; the layout parents fill it for their children.
struct LayerResUpdateInfo {
  mm::Mat44 unknown00;                            // Inferred role: parent matrix; original member name unknown.
  const LayerResMatrix *m_layerResMatrix;         // Inferred role: parent local matrix; original member name unknown.
  const LayerResColor *m_layerResColor;           // Inferred role: parent color; original member name unknown.
  bool unknown50;                                 // Inferred role: parent is applied; original member name unknown.
  LAYER_SPACE_TYPE unknown54;                     // Inferred role: parent space; original member name unknown.
  u32 unknown58;                                  // Inferred role: parent blend type; original member name unknown.
  LayerResDispInfo m_layerResDispInfo;            // Inferred role: display bounds; original member name unknown.
  const LayerObjTopMaskObj *m_layerObjTopMaskObj; // Inferred role: parent mask object; original member name unknown.
};

static_assert(offsetof(LayerResUpdateInfo, m_layerResMatrix) == 0x40, "");
static_assert(offsetof(LayerResUpdateInfo, m_layerResColor) == 0x48, "");
static_assert(offsetof(LayerResUpdateInfo, unknown50) == 0x50, "");
static_assert(offsetof(LayerResUpdateInfo, unknown54) == 0x54, "");
static_assert(offsetof(LayerResUpdateInfo, unknown58) == 0x58, "");
static_assert(offsetof(LayerResUpdateInfo, m_layerResDispInfo) == 0x5c, "");
static_assert(offsetof(LayerResUpdateInfo, m_layerObjTopMaskObj) == 0x70, "");
static_assert(sizeof(LayerResUpdateInfo) == 0x80, "");

class LayerObj : public LayerBase {
public:
  LayerObj();
  virtual void resourceInit();
  virtual void apply(LayerSortMan *sortMan, const LayerRenderView *view);
  virtual void applyBegin(LayerResUpdateInfo &info, const LayerRenderView *view);
  virtual void applyEnd(LayerResUpdateInfo &info, const LayerRenderView *view);
  virtual void setDrawList(LayerSortMan *sortMan, bool is3D) = 0;
  virtual void applyPartsSetup();
  virtual void applyParams(const LayerRenderView *view, const LayerResMatrix &matrix, const LayerResColor &color);
  void release() override;
  void baseRelease();
  void updateDefSpace(grlib::CGLibDblUniformBlock *&uniform, LAYER_SPACE_TYPE space, const mm::Mat44 &matrix);
  void updateDefUniformBlock(grlib::CGLibDblUniformBlock &uniform, const LayerResMatrix &matrix, const LayerResColor &color, const grlib::CGLibRenderTarget *target);
  void setInitPos(f32 x, f32 y);
  void setInitRot(f32 rot);
  void setInitScl(f32 x, f32 y);
  void setInitPosScl(f32 x, f32 y, f32 sclX, f32 sclY);
  void setInitMulCol(const mm::Col4 &color);
  void setInitAddCol(const mm::Col3 &color);
  void updateCtrlSpd(f32 speed);
  void updateDefPos();
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
  bool isClip() const;
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
  u32 getStateFlags(u32 index) const { return unknowna0[index]; }
  void onStateFlags(u32 flags) {
    u32 index = LayerManager::s_nStkIdx;
    unknowna0[index] |= flags;
  }
  void offStateFlags(u32 flags) {
    u32 index = LayerManager::s_nStkIdx;
    unknowna0[index] &= ~flags;
  }
  // Inferred helper: sets the render info of a work buffer of width x height pixels; original name unknown.
  void unknown005(u32 width, u32 height) {
    f32 sclY = static_cast<f32>(height) / static_cast<f32>(width);
    m_layerResRenderInfo.unknown08 = 1.0f;
    m_layerResRenderInfo.unknown0c = sclY;
    f32 sclX = 1.0f;
    if (width <= height) {
      sclY = 1.0f;
      sclX = static_cast<f32>(width) / static_cast<f32>(height);
    }
    m_layerResRenderInfo.unknown00 = sclX;
    m_layerResRenderInfo.unknown04 = sclY;
    m_layerResRenderInfo.m_pixelX = 0;
    m_layerResRenderInfo.m_pixelY = 0;
    m_layerResRenderInfo.m_pixelWidth = width;
    m_layerResRenderInfo.m_pixelHeight = height;
  }

  mm::Mat44 unknown20[2]; // Inferred role: matrices; original member name unknown.
  u32 unknowna0[2];       // Inferred role: state flags; original member name unknown.
  u32 unknowna8;          // Inferred role: flags; original member name unknown.
  u8 _ac[0xb0 - 0xac];
  u64 unknownb0;                           // Inferred role: cleared by the constructor; original member name unknown.
  const void *m_resData;                   // Inferred role: res data; named after the game accessor layer::LayerAccObjBase::getResData.
  u16 m_priority;                          // Inferred role: priority; named after the game accessor layer::LayerAccObjBase::getPriority.
  u8 unknownc2;                            // Inferred role: matrix idx; original member name unknown.
  u8 m_space;                              // Inferred role: space; named after the game accessor layer::LayerAccObjBase::setSpace.
  u8 m_blendType;                          // Inferred role: blend type; named after the game accessor layer::LayerAccObjBase::getBlendType.
  u8 unknownc5;                            // Inferred role: render blend type, index of s_resDefBlend; original member name unknown.
  u8 m_texFilterType;                      // Inferred role: tex filter type; named after the game accessor layer::LayerAccObjBase::getTexFilterType.
  LayerResParmInfo m_layerResParmInfo[3];  // Inferred role: parms; original member name unknown.
  LayerResDispInfo m_layerResDispInfo;     // Inferred role: display bounds, the clip values; original member name unknown.
  LayerResRenderInfo m_layerResRenderInfo; // Inferred role: render info; original member name unknown.
  LayerResUvParam m_layerResUvParam;       // Inferred role: uv params; original member name unknown.
  u16 unknown1d8[2];                       // Inferred role: action idx; original member name unknown.
  LayerResMatrix m_layerResMatrix;         // Inferred role: local matrix; original member name unknown.
  f32 m_ctrlSpd;                           // Inferred role: ctrl spd; named after the game accessor layer::LayerAccObjBase::getCtrlSpd.
  f32 unknown1f8;                          // Inferred role: frame ctrl spd; original member name unknown.
  f32 unknown1fc;                          // Inferred role: uniform block parameter; original member name unknown.
  f32 unknown200;                          // Inferred role: 3d sort depth; original member name unknown.
  u8 _204[0x208 - 0x204];
  LayerAnimeObj *unknown208[3];                   // Inferred role: anim objs; original member name unknown.
  LayerResSecTexture *unknown220[3];              // Inferred role: second texs; original member name unknown.
  grlib::CGLibDblUniformBlock *unknown238;        // Inferred role: world matrix uniform; original member name unknown.
  const LayerBase *m_maskObj;                     // Inferred role: mask object; named after the game accessor layer::LayerAccObjBase::setMaskObj.
  const LayerObjTopMaskObj *m_layerObjTopMaskObj; // Inferred role: mask object used for rendering; original member name unknown.
};

static_assert(offsetof(LayerObj, unknown20) == 0x20, "");
static_assert(offsetof(LayerObj, unknowna0) == 0xa0, "");
static_assert(offsetof(LayerObj, unknowna8) == 0xa8, "");
static_assert(offsetof(LayerObj, unknownb0) == 0xb0, "");
static_assert(offsetof(LayerObj, m_resData) == 0xb8, "");
static_assert(offsetof(LayerObj, m_priority) == 0xc0, "");
static_assert(offsetof(LayerObj, unknownc2) == 0xc2, "");
static_assert(offsetof(LayerObj, m_space) == 0xc3, "");
static_assert(offsetof(LayerObj, m_blendType) == 0xc4, "");
static_assert(offsetof(LayerObj, unknownc5) == 0xc5, "");
static_assert(offsetof(LayerObj, m_texFilterType) == 0xc6, "");
static_assert(offsetof(LayerObj, m_layerResParmInfo) == 0xc8, "");
static_assert(offsetof(LayerObj, m_layerResDispInfo) == 0x170, "");
static_assert(offsetof(LayerObj, m_layerResRenderInfo) == 0x180, "");
static_assert(offsetof(LayerObj, m_layerResUvParam) == 0x19c, "");
static_assert(offsetof(LayerObj, unknown1d8) == 0x1d8, "");
static_assert(offsetof(LayerObj, m_layerResMatrix) == 0x1dc, "");
static_assert(offsetof(LayerObj, m_ctrlSpd) == 0x1f4, "");
static_assert(offsetof(LayerObj, unknown1fc) == 0x1fc, "");
static_assert(offsetof(LayerObj, unknown200) == 0x200, "");
static_assert(offsetof(LayerObj, unknown208) == 0x208, "");
static_assert(offsetof(LayerObj, unknown220) == 0x220, "");
static_assert(offsetof(LayerObj, unknown238) == 0x238, "");
static_assert(offsetof(LayerObj, m_maskObj) == 0x240, "");
static_assert(offsetof(LayerObj, m_layerObjTopMaskObj) == 0x248, "");
static_assert(sizeof(LayerObj) == 0x250, "");

} // namespace layer
