// Original file name from the game string C:/Monolithsoft/BF2/prog/application/BF2/gf/camera/gf_camera_player_target.cpp.
#include "gf/camera/gf_camera_player_target.h"

#include "gf/event/gf_event.h"
#include "gf/game/gf_game_manager.h"
#include "gf/game/gf_game_mount.h"
#include "gf/game/gf_game_player_camera.h"
#include "gf/gf_allocator.h"
#include "gf/object/component/property/gf_com_property.h"
#include "gf/object/component/property/gf_env_property.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_manager.h"
#include "gf/object/gf_obj_property.h"
#include "gf/object/gf_obj_util.h"
#include "mm_math/mm_plane.h"
#include "mm_math/mm_quat.h"
#include "mm_mtl/singleton.h" // IWYU pragma: keep
#include "mm_mtl/unique_ptr.h"

namespace gf {

#line 33
PlayerCameraTarget *PlayerCameraTarget::create() { return new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) PlayerCameraTarget; }

PlayerCameraTarget::PlayerCameraTarget()
    : unknown20{mm::Vec3::zero, mm::Quat::identity}, unknown40(false), unknown41(false), unknown42(false), unknown43(false), unknown44(false), unknown45(false), unknown46(false), unknown48(0.0f),
      unknown4c(0.0f), unknown50(mm::Vec3::unitY), unknown60(mm::Vec3::unitZ), unknown70(unknown020), unknown78(true), unknown79(false) {
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

void PlayerCameraTarget::writeTargetInfo() {
  if (!unknown78) {
    unknown70 = unknown020;
    return;
  }

  GF_OBJ_HANDLE *handle = unknown70;
  if (handle == unknown020) {
    handle = GfGameManager::getControlMover();
  }

  GfObjProperty *property = GfObjUtil::getProperty(handle);
  if (property != nullptr && property->unknown18 != nullptr) {
    unknown070 *move = property->unknown18;
    unknown20.unknown00 = move->unknown10;
    unknown20.unknown10 = move->unknown20;
    unknown40 = move->unknown00 == PROPERTY_MOVE_UNKNOWN_3;
    unknown41 = move->unknown00 == PROPERTY_MOVE_UNKNOWN_4 && !move->unknown7d;
    unknown42 = move->unknown00 == PROPERTY_MOVE_UNKNOWN_1;
    unknown43 = move->unknownc0 != unknown020;
    unknown60 = move->unknown90.normal;
  }

  GfObj *obj = GfObjUtil::getObj(handle);
  if (obj == nullptr) {
    return;
  }

  GfComProperty *comProperty = obj->getComponent<GfComProperty>();
  if (comProperty != nullptr) {
    GfEnvProperty *env = comProperty->unknown28.get();
    unknown50 = mm::Vec3::unitY;
    unknown44 = false;
    unknown46 = false;
    if (env->unknown2d0 & 1) {
      unknown48 = env->unknown280.unknown00.x - 1.0f;
      unknown4c = env->unknown280.unknown00.x;
      unknown50 = env->unknown280.unknown10.normal;
      unknown44 = true;
      unknown46 = true;
    }
    const GfEnvProperty::unknown002 *ground = env->unknown004(GfEnvProperty::GROUND_INDEX_UNKNOWN_0);
    if (ground != nullptr) {
      if (unknown44) {
        if (unknown48 < ground->unknown00.y) {
          unknown48 = ground->unknown00.y;
          unknown50 = ground->unknown10.normal;
        }
      } else {
        unknown48 = ground->unknown00.y;
        unknown50 = ground->unknown10.normal;
        unknown44 = true;
      }
    }
  }

  OPTMNT type = GfMountManager::getMountType(handle, GFATTACH_UNKNOWN_0);
  unknown45 = type == OPTMNT_UNKNOWN_0 || type == OPTMNT_UNKNOWN_1 || type == OPTMNT_UNKNOWN_3;
}

} // namespace gf

template mm::mtl::PtrSingleton<gf::PlayerCameraTarget>::~PtrSingleton();
