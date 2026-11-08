// Original file name from the game string C:/Monolithsoft/BF2/prog/application/BF2/gf/camera/gf_camera_player_target.cpp.
#include "gf/camera/gf_camera_player_target.h"

#include "gf/event/gf_event.h"
#include "gf/game/gf_game_player_camera.h"
#include "gf/gf_allocator.h"
#include "gf/object/gf_obj_handle.h"
#include "mm_mtl/singleton.h" // IWYU pragma: keep

namespace gf {

#line 33
PlayerCameraTarget *PlayerCameraTarget::create() { return new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) PlayerCameraTarget; }

PlayerCameraTarget::PlayerCameraTarget()
    : unknown20(mm::Vec3::zero), unknown30(mm::Quat::identity), unknown40(false), unknown41(false), unknown42(false), unknown43(false), unknown44(false), unknown45(false), unknown46(false),
      unknown48(0.0f), unknown4c(0.0f), unknown50(mm::Vec3::unitY), unknown60(mm::Vec3::unitZ), unknown70(INVALID_HANDLE), unknown78(true), unknown79(false) {
  writeTargetInfo();
  GfEvent::addEventCallback(this);
}

PlayerCameraTarget::~PlayerCameraTarget() { GfEvent::removeEventCallback(this); }

void PlayerCameraTarget::update(const fw::UpdateInfo &) {
  writeTargetInfo();
  if (unknown79) {
    GfGamePlayerCamera::resetCamera();
    unknown79 = false;
  }
}

const mm::mtl::RTTI *PlayerCameraTarget::getRTTI() const { return &m_rtti; }

void PlayerCameraTarget::requestResetCamera() { unknown79 = true; }

void PlayerCameraTarget::gevPartyMemberOK(bool isOK) { unknown78 = isOK; }

} // namespace gf

template mm::mtl::PtrSingleton<gf::PlayerCameraTarget>::~PtrSingleton();
