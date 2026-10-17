#pragma once
#include "mm_math/mm_pnt.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace mm {
struct Mat44;
struct Plane;
struct Vec3;
} // namespace mm

namespace gf {

struct GfSetupParam;

class GfInfo : public mm::mtl::PtrSingleton<GfInfo> {
public:
  GfInfo(const GfSetupParam &param);
  void initialize(const GfSetupParam &param);
  ~GfInfo();
  static void build(const GfSetupParam &param);
  static void destroy();
  void finalize();
  static bool isInitialized();
  static void apply();
  static u64 getFrameCount64();
  static u32 getFrameCount32();
  static bool isDebugDisp();
  static bool isNpcMobDispForDebug();
  static void setNpcMobDispForDebug(bool isDisp);

  static const u32 CAMERA_PLANE_COUNT = 6;

  static mm::Plane m_camPlanes[CAMERA_PLANE_COUNT];
  static mm::Mat44 m_frustum;
  static mm::Mat44 m_projection;
  static mm::Mat44 m_viewMat;
  static mm::Mat44 m_viewProj;
  static mm::Vec3 m_camPos;
  static mm::Vec3 m_camRot;
  static mm::Vec3 m_camTgt;
  static mm::Pnt<int> m_camSize;
  static f32 m_camFov;
  static f32 m_camFar;
  static f32 m_camNear;
  static f32 m_camAspect;
  static f32 m_camLength;
  static f32 m_fSecPerFrame;
  static int m_nScreenW;
  static int m_nScreenH;
  static bool m_bDispNpcMobInfo;

private:
  bool initialized;
};

static_assert(sizeof(GfInfo) == 0x10, "");

int GfScreenW();
int GfScreenH();

} // namespace gf
