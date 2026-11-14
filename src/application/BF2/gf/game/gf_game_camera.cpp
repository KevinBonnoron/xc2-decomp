#include "gf/game/gf_game_camera.h"

#include "fw/fw_camera.h" // IWYU pragma: keep
#include "gf/camera/gf_camera_subview.h"
#include "gf/event/gf_event.h"
#include "gf/object/gf_init_param.h"
#include "mm_mtl/fixed_array.h"   // IWYU pragma: keep
#include "mm_mtl/intrusive_ptr.h" // IWYU pragma: keep
#include "mm_mtl/rtti.h"
#include "types.h"

namespace gf {

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
