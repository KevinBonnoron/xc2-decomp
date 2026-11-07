#include "gf/game/gf_game_camera.h"

#include "fw/fw_camera.h" // IWYU pragma: keep
#include "gf/event/gf_event.h"
#include "mm_mtl/fixed_array.h"   // IWYU pragma: keep
#include "mm_mtl/intrusive_ptr.h" // IWYU pragma: keep

namespace gf {

void GfGameCamera::clear() {}

void GfGameCamera::setCameraControlType(int type) { GfEvent::callCameraControl(type); }

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
