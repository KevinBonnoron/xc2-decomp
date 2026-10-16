#include "fw/fw_camera.h"
#include "ml/scn.h"
#include "types.h"

namespace fw {

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

} // namespace fw
