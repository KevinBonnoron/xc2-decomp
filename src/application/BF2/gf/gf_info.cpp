#include "gf/gf_info.h"

#include "framework/framework.h"
#include "gf/gf_allocator.h"
#include "gf/gf_manager.h"
#include "ml/dev_graph.h"
#include "ml/micro_thread.h"
#include "ml/proc_desktop.h"
#include "ml/work_cpu.h"
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_plane.h"
#include "mm_math/mm_pnt.h"
#include "mm_math/mm_vec3.h"

namespace gf {

constexpr f32 CAMERA_FOV = 40.0f;
constexpr f32 CAMERA_FAR = 8000.0f;
constexpr f32 CAMERA_NEAR = 0.1f;

mm::Plane GfInfo::m_camPlanes[CAMERA_PLANE_COUNT];
mm::Mat44 GfInfo::m_frustum;
mm::Mat44 GfInfo::m_projection;
mm::Mat44 GfInfo::m_viewMat;
mm::Mat44 GfInfo::m_viewProj;
mm::Vec3 GfInfo::m_camPos;
mm::Vec3 GfInfo::m_camRot;
mm::Vec3 GfInfo::m_camTgt;
mm::Pnt<int> GfInfo::m_camSize;
f32 GfInfo::m_camFov;
f32 GfInfo::m_camFar;
f32 GfInfo::m_camNear;
f32 GfInfo::m_camAspect;
f32 GfInfo::m_camLength;
f32 GfInfo::m_fSecPerFrame;
int GfInfo::m_nScreenW;
int GfInfo::m_nScreenH;
bool GfInfo::m_bDispNpcMobInfo;

GfInfo::GfInfo(const GfSetupParam &param) : unknown08(false) { initialize(param); }

void GfInfo::initialize(const GfSetupParam &) {
  m_nScreenW = ml::DevGraph::getRootWidth();
  m_nScreenH = ml::DevGraph::getRootHeight();
  mm::Plane plane;
  plane.set(mm::Vec3::unitY, mm::Vec3::zero);
  for (u32 i = 0; i < CAMERA_PLANE_COUNT; i++) {
    m_camPlanes[i] = plane;
  }
  m_frustum = mm::Mat44::identity;
  m_projection = mm::Mat44::identity;
  m_viewMat = mm::Mat44::identity;
  m_viewProj = mm::Mat44::identity;
  m_camPos = mm::Vec3::zero;
  m_camRot = mm::Vec3::zero;
  m_camTgt = mm::Vec3::zero;
  m_camSize.x = m_nScreenW;
  m_camSize.y = m_nScreenH;
  m_camFov = CAMERA_FOV;
  m_camFar = CAMERA_FAR;
  m_camNear = CAMERA_NEAR;
  m_camAspect = 1.0f;
  m_camLength = 1.0f;
  m_fSecPerFrame = ml::DevGraph::getFrameSyncSec();
  unknown08 = true;
}

GfInfo::~GfInfo() {}

void GfInfo::build(const GfSetupParam &param) {
  // __LINE__ must be 70 as in the original file: its value changes the instruction order.
#line 70
  new (getAllocator(ALLOCATOR_SYSTEM), __FILE__, __LINE__, 8) GfInfo(param);
}

void GfInfo::destroy() {
  GfInfo *info = get();
  info->finalize();
  delete info;
}

void GfInfo::finalize() { unknown08 = false; }

bool GfInfo::isInitialized() { return get() != nullptr && get()->unknown08; }

u64 GfInfo::getFrameCount64() { return ml::WorkCpu::getFrameCount(); }

u32 GfInfo::getFrameCount32() { return fw::Framework::getFrameCount(); }

bool GfInfo::isDebugDisp() { return ml::ProcDesktop::isDispInfo(); }

bool GfInfo::isNpcMobDispForDebug() { return m_bDispNpcMobInfo && ml::ProcDesktop::isDispInfo(); }

void GfInfo::setNpcMobDispForDebug(bool isDisp) { m_bDispNpcMobInfo = isDisp; }

void GfSleep(u32 frame) { ml::MicroThread::get()->sleep(frame, true); }

int GfScreenW() { return GfInfo::m_nScreenW; }

int GfScreenH() { return GfInfo::m_nScreenH; }

} // namespace gf
