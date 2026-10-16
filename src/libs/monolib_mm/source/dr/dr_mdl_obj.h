#pragma once
#include <stddef.h>

#include "dr/dr_mdo_ctl.h"
#include "mm_math/mm_col3.h"
#include "types.h"

namespace mm {
struct Mat44;
struct Vec3;
} // namespace mm

namespace ml {

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
  void setDblBuffAlpha(bool isEnable);
  void setMatrix(const mm::Mat44 &matrix);
  int getNodeMax() const;
  MdoWrkRimBloom *getRimBloomWrk(u32 bufferIndex);
  int getNodeIdx(const char *name) const;
  const char *getNodeName(int index) const;
  void setResBoneMat(int index, const mm::Mat44 &matrix);
  const mm::Mat44 &getResBoneMat(int index) const;
  mm::Mat44 *getResBoneMatPtr(int index);
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
};

} // namespace ml
