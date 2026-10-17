#pragma once
#include <stddef.h>

#include "mm_mtl/singleton.h"
#include "mtl/alloc_handle.h"
#include "types.h"

namespace mm {
struct Col3;
} // namespace mm

namespace ml {
class DrMdoZSortMan;
class DrResMdoSortCloud;
class IDrDrawWorkInfo;
class Scn;
class WinProc;
} // namespace ml

namespace cloud {

class CloudDataMan;
class CloudObjMan;
class CloudShaderMan;
class CloudTextureMan;
class CloudVertexMan;

class CloudMan : public mm::mtl::PtrSingleton<CloudMan> {
public:
  static int s_nDblDfIdx;
  static int s_nDblStIdx;

  CloudMan(ml::Scn *scn, mtl::ALLOC_HANDLE handle, u32 size);
  ~CloudMan() override;
  void dispOn(bool isOn);
  void planeOn(bool isOn);
  void planeSideOn(bool isOn);
  void skyOn(bool isOn);
  void mdlOn(bool isOn);
  void setHeight(f32 height);
  f32 getHeight() const;
  bool isHole() const;
  void setCldNum(u32 cldNum);
  u32 getCldNum() const;
  void beginSetup();
  void begin(f32 speed);
  void end();
  void apply(const ml::IDrDrawWorkInfo *workInfo, ml::DrMdoZSortMan *sortMan);
  void alphaRender(const ml::IDrDrawWorkInfo *workInfo);
  void finalRender(const ml::IDrDrawWorkInfo *workInfo);
  void tail();
  static void getPixelMem(u32 &size, u32 width, u32 height);
  const mm::Col3 &getPlaneCol(u32 index) const;
  void openDebugWindow(ml::WinProc *window);

  mtl::ALLOC_HANDLE m_memTop;
  mtl::ALLOC_HANDLE m_memData;
  mtl::ALLOC_HANDLE m_memWork;
  ml::Scn *m_scn;
  bool m_isSetupRequest;
  u64 _28;
  CloudDataMan *m_dataMan;
  CloudVertexMan *m_vertexMan;
  CloudTextureMan *m_textureMan;
  CloudShaderMan *m_shaderMan;
  CloudObjMan *m_objMan;
  ml::DrResMdoSortCloud *m_sortCloud;
  f32 m_speed;
  f32 _64;
};

static_assert(offsetof(CloudMan, m_memTop) == 0x08, "");
static_assert(offsetof(CloudMan, m_scn) == 0x18, "");
static_assert(offsetof(CloudMan, m_dataMan) == 0x30, "");
static_assert(offsetof(CloudMan, m_sortCloud) == 0x58, "");
static_assert(offsetof(CloudMan, m_speed) == 0x60, "");

} // namespace cloud
