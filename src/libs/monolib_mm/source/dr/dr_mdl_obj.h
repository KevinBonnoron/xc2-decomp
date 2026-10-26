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
class DrResMdoMat;

struct MdoWrkRimBloom {
  mm::Col3 unknown00; // Inferred role: color; original member name unknown.
  f32 unknown0c;      // Inferred role: power; original member name unknown.
  f32 unknown10;      // Inferred role: black ratio; original member name unknown.
  f32 unknown14;      // Inferred role: emissive; original member name unknown.
  u8 _18[0x1c - 0x18];
  u32 unknown1c; // Inferred role: flags; original member name unknown.
};

static_assert(offsetof(MdoWrkRimBloom, unknown0c) == 0x0c, "");
static_assert(offsetof(MdoWrkRimBloom, unknown10) == 0x10, "");
static_assert(offsetof(MdoWrkRimBloom, unknown14) == 0x14, "");
static_assert(offsetof(MdoWrkRimBloom, unknown1c) == 0x1c, "");
static_assert(sizeof(MdoWrkRimBloom) == 0x20, "");

class DrMdlObj : public DrMdoCtl {
public:
  void setDblBuffAlpha(bool isEnable);
  void setClipBoxMode(bool isEnable);
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
  DrResMdoMat *getMaterialRes(const char *name);
  DrResMdoMat *getMaterialRes(int index);
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
