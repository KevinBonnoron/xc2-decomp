#include "fw/fw_camera.h"
#include "ml/scn.h"
#include "mm_math/mm_mat44.h"
#include "mm_mtl/intrusive_list.h"
#include "mm_mtl/intrusive_ptr.h"
#include "types.h"

namespace fw {

CameraLayer::CameraLayer() : scnCamera(nullptr), blendTime(0.0f), blendRate(1.0f), isBlending(false) {
  previousMatrix = mm::Mat44::identity;
  matrix = mm::Mat44::identity;
}

CameraLayer::~CameraLayer() {}

void CameraLayer::setup(ml::Scn *scn, u32 index) { scnCamera = scn->getCam(index); }

void CameraLayer::onPopCamera(Camera &camera) {
  camera.onPop();
  camera.isActive = false;
}

void CameraLayer::onPushCamera(Camera &camera) {
  camera.onPush();
  camera.isActive = true;
}

void CameraLayer::pushPlugin(mm::mtl::IntrusivePtr<CameraPlugin> &plugin) {
  plugin->addRef();
  plugins.push_front(plugin.get());
}

void CameraLayer::popPlugin(mm::mtl::IntrusivePtr<CameraPlugin> &plugin) {
  plugins.erase(plugin.get());
  plugin->release();
}

} // namespace fw
