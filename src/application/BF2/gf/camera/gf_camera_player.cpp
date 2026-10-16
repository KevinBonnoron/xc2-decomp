#include "gf/camera/gf_camera_player.h"

#include "gf/gf_allocator.h"

namespace gf {

constexpr int CAMERA_PAD_TYPE = 2;

CameraPadData::CameraPadData() {
  reset();
  bind();
}

void CameraPadData::reset() {
  arx = 0.0f;
  ary = 0.0f;
  isReset = false;
  isAllReset = false;
  isZoom = false;
  isHeight = false;
  isSideLeft = false;
  isSideRight = false;
  isSideReset = false;
}

void CameraPadData::bind() {
  PadRelay::bind(0, CAMERA_PAD_TYPE, getAllocator(ALLOCATOR_DEFAULT));
  bindAction("reset", this, &CameraPadData::resetAction);
  bindAction("zoom", this, &CameraPadData::zoomCamera);
  bindAction("height", this, &CameraPadData::heightCamera);
  bindAction("side_left", this, &CameraPadData::sideLeftCamera);
  bindAction("side_right", this, &CameraPadData::sideRightCamera);
  bindAction("side_reset", this, &CameraPadData::sideResetCamera);
  bindAction("all_reset", this, &CameraPadData::allResetAction);
  bindAxis("arx", this, &CameraPadData::setARX);
  bindAxis("ary", this, &CameraPadData::setARY);
}

CameraPadData::~CameraPadData() { unbind(); }

void CameraPadData::unbind() { PadRelay::unbind(); }

void CameraPadData::update() {
  reset();
  PadRelay::update();
}

void CameraPadData::resetAction() { isReset = true; }

void CameraPadData::zoomCamera() { isZoom = true; }

void CameraPadData::heightCamera() { isHeight = true; }

void CameraPadData::sideLeftCamera() { isSideLeft = true; }

void CameraPadData::sideRightCamera() { isSideRight = true; }

void CameraPadData::sideResetCamera() { isSideReset = true; }

void CameraPadData::allResetAction() { isAllReset = true; }

void CameraPadData::setARX(f32 value) { arx = value; }

void CameraPadData::setARY(f32 value) { ary = value; }

} // namespace gf
