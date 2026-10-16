#pragma once
#include <stddef.h>

#include "dr/dr_mdo_ctl.h"
#include "mm_math/mm_col3.h"
#include "types.h"

namespace grlib {
class CGLibTextureBuffer;
} // namespace grlib

namespace mm {
struct Mat44;
struct Vec3;
} // namespace mm

namespace ml {
struct MdsMatCharMkTexTbl;
struct MdsMatInfoHeader;
struct MdsMdlInfoHeader;
struct MdsMdlVertexFmt;
struct MdoWrkMatEntry;

struct MdoWrkRimBloom {
  mm::Col3 color;
  f32 power;
  f32 blackRatio;
  f32 emissive;
  u8 _18[0x1c - 0x18];
  u32 flags;
};

static_assert(offsetof(MdoWrkRimBloom, power) == 0x0c, "");
static_assert(offsetof(MdoWrkRimBloom, blackRatio) == 0x10, "");
static_assert(offsetof(MdoWrkRimBloom, emissive) == 0x14, "");
static_assert(offsetof(MdoWrkRimBloom, flags) == 0x1c, "");
static_assert(sizeof(MdoWrkRimBloom) == 0x20, "");

class DrMdlObj : public DrMdoCtl {
public:
  enum DrawFlag {
    DRAW_FLAG_ALWAYS_TEX_STM = 1 << 2,
    DRAW_FLAG_WRITE_STENCIL = 1 << 4,
    DRAW_FLAG_SIMPLE_SHADOW = 1 << 10,
    DRAW_FLAG_SP_ALPHA_MODE = 1 << 14,
    DRAW_FLAG_SP_BLUR_OFF = 1 << 15,
    DRAW_FLAG_GPU_CLIP_OFF = 1 << 16,
    DRAW_FLAG_ALWAYS_MIDDLE_TEX_STM = 1 << 17,
    DRAW_FLAG_OCCLUSION_QUERY_OFF = 1 << 18,
    DRAW_FLAG_EXPRESS_DRAW_MODE = 1 << 20,
    DRAW_FLAG_CAM_CHECK_MODE = 1 << 28,
    DRAW_FLAG_CAM_CHECK_RESL = 1 << 29,
    DRAW_FLAG_DEBUG_DELETE = 1 << 30,
    DRAW_FLAG_DEBUG_WINDOW = 1u << 31,
  };

  enum AlphaFlag {
    ALPHA_FLAG_UPDATED = 1 << 16,
    ALPHA_FLAG_SINGLE_BUFFER = 1 << 18,
  };

  void setDblBuffAlpha(bool isEnable);
  DrMdlObj(int viewNum);
  void chageShadowObject(DrMdoSmlShadowMan *shadowMan) override;
  void setFrame(f32 frame);
  void setMatrix(const mm::Mat44 &matrix);
  void setOffsetPos(const mm::Vec3 &position);
  int getNodeMax() const;
  MdoWrkRimBloom *getRimBloomWrk(u32 bufferIndex);
  int getNodeIdx(const char *name) const;
  const char *getNodeName(int index) const;
  void setResBoneMat(int index, const mm::Mat44 &matrix);
  const mm::Mat44 &getResBoneMat(int index) const;
  mm::Mat44 *getResBoneMatPtr(int index);
  void setResBoneExMode(int index, bool isEnable);
  bool getModelInfoHeader(int index, const MdsMdlInfoHeader **header);
  bool getModelTexture(int index, const grlib::CGLibTextureBuffer **texture);
  void getMaterialHeader(int *count, const MdsMatInfoHeader **header);
  void getCharMkTextureList(int *count, const MdsMatCharMkTexTbl **table);
  int getTextureResMax() const;
  int getTextureResIdx(const char *name);
  grlib::CGLibTextureBuffer *getTextureRes(const char *name);
  grlib::CGLibTextureBuffer *getTextureRes(int index);
  void getNowTextureRes(grlib::CGLibTextureBuffer **&textures, int &count);
  void setTextureRes(const char *name, grlib::CGLibTextureBuffer *texture);
  void setTextureRes(int index, grlib::CGLibTextureBuffer *texture);
  int getMaterialResIdx(const char *name) const;
  const char *getMaterialIdxName(int index) const;
  MdoWrkMatEntry *getMaterialRes(const char *name);
  MdoWrkMatEntry *getMaterialRes(int index);
  bool getVertexInfo(int index, const MdsMdlVertexFmt **format, int *count);
  void setAlpha(f32 alpha);
  f32 getAlpha() const;
  void setWriteStencil(bool isEnable);
  void setAlwaysMiddleTexStm(bool isEnable);
  void setSpBlurOff(bool isEnable);
  void setGpuClip(bool isEnable);
  void setOcclusionQuery(bool isEnable);
  void setAlwaysTexStm(bool isEnable);
  bool isMdlTexStm() const;
  bool isMemTexStm() const;
  bool isMemMiddleTexStm() const;
  void setCreateDisplayList();
  void setExpressDrawMode(bool isEnable);
  const mm::Vec3 &getAABBMax() const;
  const mm::Vec3 &getAABBMin() const;
  void getInitialVertexAABBMax(mm::Vec3 &max, bool isScaled) const;
  void getInitialVertexAABBMin(mm::Vec3 &min, bool isScaled) const;
  void setSimpleShadow(bool isEnable);
  bool isGpuRender() const;
  void setSpAlphaMode(bool isEnable);
  void setCamCheckMode(bool isEnable);
  bool isCamCheckResl() const;
  bool isAce() const;
  void setAceColor(int index, const mm::Col3 &color);
  void setAceVal(int index, f32 value);
  const mm::Col3 &getAceColor(int index) const;
  f32 getAceVal(int index) const;
  void setDebugWindow(bool isEnable);
  u32 isDebugWindow();
  u32 isDebugDelete();
  void OnCloseAttriMenu();
};

} // namespace ml
