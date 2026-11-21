#include "gf/game/gf_game_camera.h"

#include "fw/fw_camera.h" // IWYU pragma: keep
#include "gf/camera/gf_camera_subview.h"
#include "gf/event/gf_event.h"
#include "gf/gf_allocator.h"
#include "gf/object/gf_init_param.h"
#include "mm_mtl/fixed_array.h"   // IWYU pragma: keep
#include "mm_mtl/intrusive_ptr.h" // IWYU pragma: keep
#include "mm_mtl/rtti.h"
#include "types.h"

namespace gf {

GfGameCamera::GfGameCamera(const GfSetupParam &param) : unknown20(false) {
  unknown08.assign(mm::mtl::IntrusivePtr<fw::Camera>());
  initialize(param);
}

void GfGameCamera::initialize(const GfSetupParam &) {
  createSubViewCamera();
  unknown20 = true;
}

void GfGameCamera::build(const GfSetupParam &param) {
  // __LINE__ must be 51 as in the original file: it is the line argument of operator new.
#line 51
  new (getAllocator(ALLOCATOR_UNKNOWN_1), __FILE__, __LINE__, 8) GfGameCamera(param);
}

void GfGameCamera::destroy() {
  GfGameCamera *camera = get();
  camera->finalize();
  delete camera;
}

void GfGameCamera::finalize() {
  destroySubViewCamera();
  unknown20 = false;
}

// Game: 0x7100310df8. The singleton pointer is read into a local (ruling 1/2): with get() written in the guard and again in the access, the load comes
// after the range test and the function is 27 instructions against the game's 29.
SubViewCamera *GfGameCamera::getSubCamera(VIEWCAM view) {
  SubViewCamera *camera = nullptr;
  GfGameCamera *self = get();
  if (static_cast<u32>(view) - 1 < 3 && self != nullptr) {
    fw::Camera *base = self->unknown08[view - 1].get();
    camera = base != nullptr ? mm::mtl::dynamicCast<SubViewCamera>(base) : nullptr;
  }
  return camera;
}

void GfGameCamera::clear() {}

void GfGameCamera::createSubViewCamera() {
  fw::CameraManager *manager = fw::CameraManager::get();
  if (manager != nullptr) {
    for (u32 index = 0; index < 3; index++) {
      unknown08[index] = SubViewCamera::create(static_cast<VIEWCAM>(index + 1));
      manager->unknown20[index + 1].push(unknown08[index], 0.0f);
    }
  }
}

void GfGameCamera::destroySubViewCamera() {
  fw::CameraManager *manager = fw::CameraManager::get();
  if (manager != nullptr) {
    for (u32 index = 0; index < 3; index++) {
      if (unknown08[index].get() != nullptr) {
        manager->unknown20[mm::mtl::dynamicCast<SubViewCamera>(unknown08[index].get())->unknowna8].pop(unknown08[index], 0.0f);
        unknown08[index] = nullptr;
      }
    }
  }
}

void GfGameCamera::setCameraControlType(int type) { GfEvent::callCameraControl(type); }

GfGameCamera::~GfGameCamera() { ; }

bool GfGameCamera::isInitialized() {
  if (get() != nullptr) {
    return get()->unknown20;
  }
  return false;
}

} // namespace gf

template mm::mtl::PtrSingleton<gf::GfGameCamera>::~PtrSingleton();
template void mm::mtl::FixedArray<mm::mtl::IntrusivePtr<fw::Camera>, 3>::assign(const mm::mtl::IntrusivePtr<fw::Camera> &value);
template mm::mtl::FixedArray<mm::mtl::IntrusivePtr<fw::Camera>, 3>::~FixedArray();
