#include "event/chara_ik_updater.h"

#include "event/chara_facial_util.h"
#include "gf/game/gf_game_party.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_util.h"

namespace event {

void CharaIKUpdater::create(gf::GF_OBJ_HANDLE *handle) {
  this->handle = handle;
  gf::GfObj *obj = gf::GfObjUtil::getObj(handle);
  if (obj != nullptr) {
    CharaFacialUtil::getLensLimit(mLensTranslateMin, mLensTranslateMax, mLensRotateMin, mLensRotateMax, obj);
  }
  flags.set(FLAG_ALL_IK, true);
  flags.set(FLAG_FOOT_IK_0, true);
  flags.set(FLAG_FOOT_IK_1, true);
  flags.set(FLAG_FOOT_IK_2, true);
  flags.set(FLAG_TARGET_IK, false);
  flags.set(FLAG_LENS_IK, false);
}

void CharaIKUpdater::render(const mm::Vec3 &position, f32 height) { gf::GfObjUtil::getObj(handle); }

void CharaIKUpdater::setAllIK(bool isEnable) {
  flags.set(FLAG_ALL_IK, isEnable);
  mTargetFrame = 0.0f;
  mRequests.set(REQUEST_ALL_IK);
  mRequests.set(REQUEST_FOOT_IK);
  mRequests.set(REQUEST_TARGET_IK);
  mRequests.set(REQUEST_TARGET_POS);
  mRequests.set(REQUEST_LENS_IK);
}

void CharaIKUpdater::setFootIK(bool isEnable, FOOT_TYPE type) {
  switch (type) {
  case FOOT_TYPE_0:
    flags.set(FLAG_FOOT_IK_0, isEnable);
    break;
  case FOOT_TYPE_1:
    flags.set(FLAG_FOOT_IK_1, isEnable);
    break;
  case FOOT_TYPE_2:
    flags.set(FLAG_FOOT_IK_2, isEnable);
    break;
  }
  mRequests.set(REQUEST_FOOT_IK);
}

void CharaIKUpdater::setTargetIK(bool isEnable, f32 frame, bool isNoSpine) {
  if (isEnable) {
    mTargetFrame = frame;
    flags.set(FLAG_TARGET_IK, true);
    flags.set(FLAG_TARGET_IK_NO_SPINE, isNoSpine);
    mRequests.set(REQUEST_TARGET_IK);
  } else if (flags.test(FLAG_TARGET_IK)) {
    flags.set(FLAG_TARGET_IK, false);
    flags.set(FLAG_TARGET_IK_NO_SPINE, isNoSpine);
    mTargetFrame = frame;
    mRequests.set(REQUEST_TARGET_IK);
  }
}

void CharaIKUpdater::setTargetPos(const mm::Vec3 &position) {
  mTargetPos = position;
  mRequests.set(REQUEST_TARGET_POS);
}

void CharaIKUpdater::setLensIK(bool isEnable, f32 x, f32 y) {
  mLensMove.x = x;
  mLensMove.y = y;
  flags.set(FLAG_LENS_IK, isEnable);
  mRequests.set(REQUEST_LENS_IK);
}

bool CharaIKUpdater::checkField(gf::GfObj *obj) {
  gf::GF_OBJ_HANDLE *handle = obj->handle;
  for (u32 i = 0; i < 3; i++) {
    gf::GF_OBJ_HANDLE *driver = gf::GfGameParty::getHandleDriver(i);
    if (gf::GfGameParty::isLeaderDriver(driver)) {
      continue;
    }
    if (driver == handle) {
      return false;
    }
  }
  for (u32 i = 0; i < 3; i++) {
    if (gf::GfGameParty::getHandleBlade(i, -1) == handle) {
      return false;
    }
  }
  return true;
}

} // namespace event
