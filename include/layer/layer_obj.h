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
struct LayerRenderView;
class LayerResSecTexture;
class LayerSortMan;

struct LayerResMatrix {
  f32 unknown00; // Inferred role: pos x; original member name unknown.
  f32 unknown04; // Inferred role: pos y; original member name unknown.
  f32 unknown08; // Inferred role: rot; original member name unknown.
  f32 unknown0c; // Inferred role: scl x; original member name unknown.
  f32 unknown10; // Inferred role: scl y; original member name unknown.
  f32 unknown14; // Inferred role: anchor x; original member name unknown.
  f32 unknown18; // Inferred role: anchor y; original member name unknown.
};

static_assert(sizeof(LayerResMatrix) == 0x1c, "");

struct LayerResColor {
  mm::Col4 unknown00; // Inferred role: mul col; original member name unknown.
  mm::Col3 unknown10; // Inferred role: add col; original member name unknown.
};

static_assert(sizeof(LayerResColor) == 0x1c, "");

struct LayerResParmInfo {
  LayerResMatrix unknown00; // Inferred role: matrix; original member name unknown.
  LayerResColor unknown1c;  // Inferred role: color; original member name unknown.
};

static_assert(sizeof(LayerResParmInfo) == 0x38, "");

struct LayerResUvParam {
  f32 unknown00; // Inferred role: u; original member name unknown.
  f32 unknown04; // Inferred role: v; original member name unknown.
  f32 unknown08; // Inferred role: scale u; original member name unknown.
  f32 unknown0c; // Inferred role: scale v; original member name unknown.
  f32 unknown10; // Inferred role: rot; original member name unknown.
};

static_assert(sizeof(LayerResUvParam) == 0x14, "");

class LayerObj : public LayerBase {
public:
  virtual void resourceInit();
  virtual void setDrawList(LayerSortMan *sortMan, bool is3D) = 0;
  virtual void applyPartsSetup();
  virtual void applyParams(const LayerRenderView *view, const LayerResMatrix &matrix, const LayerResColor &color);
  void release() override;
  void baseRelease();
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

  u8 unknown1c; // Inferred role: state marker set by release; original member name unknown.
  u8 _1d[0x20 - 0x1d];
  mm::Mat44 unknown20[2]; // Inferred role: matrices; original member name unknown.
  u32 unknowna0[2];       // Inferred role: state flags; original member name unknown.
  u32 unknowna8;          // Inferred role: flags; original member name unknown.
  u8 _ac[0xb8 - 0xac];
  const void *unknownb8; // Inferred role: res data; original member name unknown.
  u16 unknownc0;         // Inferred role: priority; original member name unknown.
  u8 unknownc2;          // Inferred role: matrix idx; original member name unknown.
  u8 unknownc3;          // Inferred role: space; original member name unknown.
  u8 unknownc4;          // Inferred role: blend type; original member name unknown.
  u8 _c5[0xc6 - 0xc5];
  u8 unknownc6;                  // Inferred role: tex filter type; original member name unknown.
  LayerResParmInfo unknownc8[3]; // Inferred role: parms; original member name unknown.
  f32 unknown170;                // Inferred role: clip value; original member name unknown.
  f32 unknown174;                // Inferred role: clip value; original member name unknown.
  f32 unknown178;                // Inferred role: clip value; original member name unknown.
  f32 unknown17c;                // Inferred role: clip value; original member name unknown.
  f32 unknown180;                // Inferred role: width; original member name unknown.
  f32 unknown184;                // Inferred role: height; original member name unknown.
  f32 unknown188;                // Inferred role: scale; original member name unknown.
  f32 unknown18c;                // Inferred role: scale; original member name unknown.
  u16 unknown190;                // Inferred role: pixel x; original member name unknown.
  u16 unknown192;                // Inferred role: pixel y; original member name unknown.
  u16 unknown194;                // Inferred role: pixel width; original member name unknown.
  u16 unknown196;                // Inferred role: pixel height; original member name unknown.
  u8 unknown198;                 // Inferred role: center type; original member name unknown.
  LayerResUvParam unknown19c[3]; // Inferred role: uv params; original member name unknown.
  u16 unknown1d8[2];             // Inferred role: action idx; original member name unknown.
  u8 _1dc[0x1f4 - 0x1dc];
  f32 unknown1f4; // Inferred role: ctrl spd; original member name unknown.
  f32 unknown1f8; // Inferred role: frame ctrl spd; original member name unknown.
  f32 unknown1fc; // Inferred role: uniform block parameter; original member name unknown.
  f32 unknown200; // Inferred role: 3d sort depth; original member name unknown.
  u8 _204[0x208 - 0x204];
  LayerAnimeObj *unknown208[3];            // Inferred role: anim objs; original member name unknown.
  LayerResSecTexture *unknown220[3];       // Inferred role: second texs; original member name unknown.
  grlib::CGLibDblUniformBlock *unknown238; // Inferred role: world matrix uniform; original member name unknown.
  const LayerBase *unknown240;             // Inferred role: mask object; original member name unknown.
  u8 _248[0x250 - 0x248];
};

static_assert(offsetof(LayerObj, unknown1c) == 0x1c, "");
static_assert(offsetof(LayerObj, unknown20) == 0x20, "");
static_assert(offsetof(LayerObj, unknowna0) == 0xa0, "");
static_assert(offsetof(LayerObj, unknowna8) == 0xa8, "");
static_assert(offsetof(LayerObj, unknownb8) == 0xb8, "");
static_assert(offsetof(LayerObj, unknownc0) == 0xc0, "");
static_assert(offsetof(LayerObj, unknownc2) == 0xc2, "");
static_assert(offsetof(LayerObj, unknownc3) == 0xc3, "");
static_assert(offsetof(LayerObj, unknownc4) == 0xc4, "");
static_assert(offsetof(LayerObj, unknownc6) == 0xc6, "");
static_assert(offsetof(LayerObj, unknownc8) == 0xc8, "");
static_assert(offsetof(LayerObj, unknown170) == 0x170, "");
static_assert(offsetof(LayerObj, unknown17c) == 0x17c, "");
static_assert(offsetof(LayerObj, unknown180) == 0x180, "");
static_assert(offsetof(LayerObj, unknown188) == 0x188, "");
static_assert(offsetof(LayerObj, unknown198) == 0x198, "");
static_assert(offsetof(LayerObj, unknown19c) == 0x19c, "");
static_assert(offsetof(LayerObj, unknown1d8) == 0x1d8, "");
static_assert(offsetof(LayerObj, unknown1f4) == 0x1f4, "");
static_assert(offsetof(LayerObj, unknown1fc) == 0x1fc, "");
static_assert(offsetof(LayerObj, unknown200) == 0x200, "");
static_assert(offsetof(LayerObj, unknown208) == 0x208, "");
static_assert(offsetof(LayerObj, unknown220) == 0x220, "");
static_assert(offsetof(LayerObj, unknown238) == 0x238, "");
static_assert(offsetof(LayerObj, unknown240) == 0x240, "");
static_assert(sizeof(LayerObj) == 0x250, "");

} // namespace layer
