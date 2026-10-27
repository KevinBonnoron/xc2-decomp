#include "gf/camera/gf_camera_player.h"

#include "gf/gf_allocator.h"

namespace gf {

constexpr int CAMERA_PAD_TYPE = 2;

f32 PlayerCamera::getNearClip() { return 0.4f; }

f32 PlayerCamera::getFarClip() { return 80000.0f; }

bool PlayerCamera::isManual() { return m_manual; }

f32 PlayerCamera::getSaveYaw() const { return m_saveYaw; }

f32 PlayerCamera::getSavePitch() const { return m_savePitch; }

f32 PlayerCamera::getSaveDistance() const { return m_saveDistance; }

f32 PlayerCamera::getSaveHeight() const { return m_saveHeight; }

u32 PlayerCamera::getSaveSide() const { return m_saveSide; }

bool PlayerCamera::isSaveFreeMode() const { return m_manual; }

CameraPadData::CameraPadData() {
  reset();
  bind();
}

void CameraPadData::reset() {
  m_ARX = 0.0f;
  m_ARY = 0.0f;
  unknown40 = false;
  unknown41 = false;
  unknown42 = false;
  unknown43 = false;
  unknown44 = false;
  unknown45 = false;
  unknown46 = false;
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

void CameraPadData::resetAction() { unknown40 = true; }

void CameraPadData::zoomCamera() { unknown42 = true; }

void CameraPadData::heightCamera() { unknown43 = true; }

void CameraPadData::sideLeftCamera() { unknown44 = true; }

void CameraPadData::sideRightCamera() { unknown45 = true; }

void CameraPadData::sideResetCamera() { unknown46 = true; }

void CameraPadData::allResetAction() { unknown41 = true; }

void CameraPadData::setARX(f32 value) { m_ARX = value; }

void CameraPadData::setARY(f32 value) { m_ARY = value; }

} // namespace gf
