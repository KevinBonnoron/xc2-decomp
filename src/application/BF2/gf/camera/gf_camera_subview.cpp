#include "gf/camera/gf_camera_subview.h"

#include "framework/framework.h"
#include "framework/memory/framework_memory.h"

namespace fw {
enum CAMERA_PRIO : int;
} // namespace fw

namespace gf {

static constexpr fw::CAMERA_PRIO CAMERA_PRIO_UNKNOWN_55 = static_cast<fw::CAMERA_PRIO>(55); // Inferred role: camera prio sub view; original name unknown.

static mm::Vec3 unknown001(0.0f, 2.0f, 10.0f); // Inferred role: default camera position; original name unknown.
static mm::Vec3 unknown002(0.0f, 0.5f, 0.0f);  // Inferred role: default camera target; original name unknown.

SubViewCamera::SubViewCamera() : fw::Camera(CAMERA_PRIO_UNKNOWN_55), unknowna8(VIEWCAM_UNKNOWN_1), unknownb0(unknown001), unknownc0(unknown002) {}

SubViewCamera::~SubViewCamera() {}

// __LINE__ must be 44 as in the original file: it is the line argument of the allocation.
mm::mtl::IntrusivePtr<fw::Camera> SubViewCamera::create(VIEWCAM view) {
#line 44
  SubViewCamera *camera = new (fw::Framework::getAllocator(), 16, __FILE__, __LINE__) SubViewCamera;
  camera->unknowna8 = view;
  return camera;
}

void SubViewCamera::onActivate() {}

void SubViewCamera::update(const fw::UpdateInfo &) { setLookAt(unknownb0, unknownc0, 0.0f); }

const mm::mtl::RTTI *SubViewCamera::getRTTI() const { return &m_rtti; }

const char *SubViewCamera::getName() const { return "SubViewCamera"; }

} // namespace gf
