#include "fw/fw_camera.h"
#include "ml/scn.h"
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_vec3.h"
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

void CameraLayer::cleanup() {
  while (!unknown08.empty()) {
    Camera *camera = unknown08.begin().get();
    onPopCamera(*camera);
    unknown08.pop_front();
    camera->release();
  }
  while (!unknown20.empty()) {
    CameraPlugin *plugin = unknown20.begin().get();
    unknown20.pop_front();
    plugin->release();
  }
}

void CameraLayer::onPopCamera(Camera &camera) {
  camera.onPop();
  camera.unknowna0 = false;
}

void CameraLayer::onPushCamera(Camera &camera) {
  camera.onPush();
  camera.unknowna0 = true;
}

void CameraLayer::pop(mm::mtl::IntrusivePtr<Camera> &camera, f32 time) {
  Camera *front = unknown08.begin().get();
  if (camera.get() == front && time > 0.0f) {
    unknown80 = camera->unknown60;
    unknownc0 = 0.0f;
    unknownc4 = time;
    unknownc8 = true;
  }
  camera->onDeactivate();
  onPopCamera(*camera);
  unknown08.erase(camera.get());
  camera->release();
  if (!unknown08.empty()) {
    unknown08.begin().get()->onActivate();
  }
}

void CameraLayer::pushPlugin(mm::mtl::IntrusivePtr<CameraPlugin> &plugin) {
  plugin->addRef();
  unknown20.push_front(plugin.get());
}

void CameraLayer::popPlugin(mm::mtl::IntrusivePtr<CameraPlugin> &plugin) {
  unknown20.erase(plugin.get());
  plugin->release();
}

mm::Vec3 CameraLayer::getCameraPosition() const {
  mm::Mat44 matrix = unknown40;
  return matrix.unknown003().unknown004();
}

} // namespace fw

template mm::mtl::IntrusivePtr<fw::CameraPlugin>::~IntrusivePtr();
