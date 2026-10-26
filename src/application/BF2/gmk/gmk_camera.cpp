#include "gmk/gmk_camera.h"

#include "fw/fw_camera.h"
#include "fw/fw_transform.h"
#include "gf/camera/gimmick/gf_camera_gimmick.h"
#include "gf/field/gf_field_lod.h"
#include "gf/game/gf_game_manager.h"
#include "gf/game/gf_game_party.h"
#include "gf/game/sequential_play/gf_play_factory.h"
#include "gf/object/gf_obj_acc.h"
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_math.h"
#include <math.h>

namespace gmk {

GmkCamera::GmkCamera(const CreateInfo *info) : unknown10(), unknown140(), unknown148(nullptr) {
  if (info != nullptr) {
    create(*info);
  }
}

bool GmkCamera::CreateInfo::validateTransform(gf::GF_OBJ_HANDLE *handle) {
  gf::GfObjAcc acc(handle);
  if (!acc.isValidTransform()) {
    return false;
  }
  const fw::Transform &transform = acc.getWorldTransformNoSync();
  mm::Mat44 matrix;
  mm::quatToMatrix(matrix, transform.unknown10);
  f32 rotation = atan2f(matrix.rows[2][0], matrix.rows[2][2]);
  unknown107 = true;
  unknown110.x = transform.unknown00.x;
  unknown110.y = transform.unknown00.y;
  unknown110.z = transform.unknown00.z;
  unknown120 = rotation;
  return true;
}

bool GmkCamera::CreateInfo::validateTransform(u16 lodId) {
  mm::Mat44 matrix;
  if (!gf::GfFieldLod::get()->findTransform(matrix, lodId)) {
    return false;
  }
  mm::Vec3 position = matrix.unknown004();
  f32 rotation = atan2f(matrix.rows[2][0], matrix.rows[2][2]);
  unknown107 = true;
  unknown110 = position;
  unknown120 = rotation;
  return true;
}

void GmkCamera::create(const CreateInfo &info) {
  dispose();
  unknown10 = info;
  unknown140 = info.unknown107 ? gf::GimmickCamera::create(info.unknown00.c_str(), info.unknown110, info.unknown120) : gf::GimmickCamera::create(info.unknown00.c_str());
  static_cast<gf::GimmickCamera *>(unknown140.get())->setAuto(info.unknown105);
  unknown148 = &GmkCamera::seqWaitToLoaded;
  gf::GfGameManager::setStopMainMenuOpenForGimmick(true);
}

bool GmkCamera::isLoaded() const { return static_cast<gf::GimmickCamera *>(unknown140.get())->isLoaded(); }

bool GmkCamera::isEnd() const {
  if (unknown140.get() != nullptr) {
    return static_cast<gf::GimmickCamera *>(unknown140.get())->isPlayEnd();
  }
  return true;
}

void GmkCamera::dispose() {
  gf::GfGameManager::setStopMainMenuOpenForGimmick(false);
  unknown148 = nullptr;
  if (unknown140.get() != nullptr) {
    if (unknown140.get()->intoNode()) {
      fw::CameraManager::get()->unknown20[0].pop(unknown140, 0.0f);
    }
    unknown140 = nullptr;
  }
  unknown10 = CreateInfo();
}

void GmkCamera::update(f32 deltaTime) {
  if (unknown10.unknown00.length() > 0 && unknown148) {
    (this->*unknown148)(deltaTime);
  }
}

void GmkCamera::play() { unknown148 = &GmkCamera::seqWaitToPlay; }

void GmkCamera::applyInvisibleParty() {
  if (unknown10.unknown104 == 1) {
    setDispOfParty(false, false);
  } else if (unknown10.unknown104 == 2) {
    setDispOfParty(false, true);
  }
}

void GmkCamera::setDispOfParty(bool isDisp, bool isExceptMover) {
  gf::GF_OBJ_HANDLE *mover = gf::GfGameManager::getControlMover();
  for (u32 i = 0; i < 3; i++) {
    gf::GF_OBJ_HANDLE *driver = gf::GfGameParty::getHandleDriver(i);
    if (!isExceptMover || mover != driver) {
      gf::GfObjAcc(driver).setDisp(gf::OBJDISP_UNKNOWN10, isDisp);
    }
    gf::GF_OBJ_HANDLE *blade = gf::GfGameParty::getHandleBlade(i, -1);
    if (!isExceptMover || mover != blade) {
      gf::GfObjAcc(blade).setDisp(gf::OBJDISP_UNKNOWN10, isDisp);
    }
  }
}

void GmkCamera::seqWaitToLoaded(f32 deltaTime) {
  if (!isLoaded()) {
    return;
  }
  if (unknown10.unknown105) {
    if (unknown10.unknown106 && !gf::GfPlayFactory::createGmkCamera(unknown140)) {
      return;
    }
    fw::CameraManager::get()->unknown20[0].push(unknown140, 0.0f);
    applyInvisibleParty();
  }
  unknown148 = &GmkCamera::seqWaitToEnd;
}

void GmkCamera::seqWaitToPlay(f32 deltaTime) {
  if (unknown10.unknown106 && !gf::GfPlayFactory::createGmkCamera(unknown140)) {
    return;
  }
  fw::CameraManager::get()->unknown20[0].push(unknown140, 0.0f);
  static_cast<gf::GimmickCamera *>(unknown140.get())->play();
  applyInvisibleParty();
  unknown148 = &GmkCamera::seqWaitToEnd;
}

void GmkCamera::seqWaitToEnd(f32 deltaTime) {
  if (!static_cast<gf::GimmickCamera *>(unknown140.get())->isPlayEnd()) {
    return;
  }
  if (unknown10.unknown104 == 1) {
    setDispOfParty(true, false);
  } else if (unknown10.unknown104 == 2) {
    setDispOfParty(true, true);
  }
  unknown148 = nullptr;
  if (unknown140.get() != nullptr) {
    fw::CameraManager::get()->unknown20[0].pop(unknown140, 0.0f);
    unknown140 = nullptr;
  }
  gf::GfGameManager::setStopMainMenuOpenForGimmick(false);
}

} // namespace gmk
