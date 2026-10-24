#include "fw/fw_camera.h"
#include "ml/scn.h"
#include "mm_math/mm_mat44.h"
#include "mm_mtl/intrusive_list.h"
#include "mm_mtl/intrusive_ptr.h"
#include "types.h"

namespace fw {

CameraLayer::CameraLayer() : unknown38(nullptr), unknownc0(0.0f), unknownc4(1.0f), unknownc8(false) {
  unknown80 = mm::Mat44::identity;
  unknown40 = mm::Mat44::identity;
}

CameraLayer::~CameraLayer() {}

void CameraLayer::setup(ml::Scn *scn, u32 index) { unknown38 = scn->getCam(index); }

void CameraLayer::onPopCamera(Camera &camera) {
  camera.onPop();
  camera.unknowna0 = false;
}

void CameraLayer::onPushCamera(Camera &camera) {
  camera.onPush();
  camera.unknowna0 = true;
}

void CameraLayer::pushPlugin(mm::mtl::IntrusivePtr<CameraPlugin> &plugin) {
  plugin->addRef();
  unknown20.push_front(plugin.get());
}

void CameraLayer::popPlugin(mm::mtl::IntrusivePtr<CameraPlugin> &plugin) {
  unknown20.erase(plugin.get());
  plugin->release();
}

} // namespace fw
