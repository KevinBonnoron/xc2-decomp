#include "gf/game/gf_game_camera.h"

#include "gf/event/gf_event.h"

namespace gf {

void GfGameCamera::clear() {}

void GfGameCamera::setCameraControlType(int type) { GfEvent::callCameraControl(type); }

} // namespace gf

template mm::mtl::PtrSingleton<gf::GfGameCamera>::~PtrSingleton();
