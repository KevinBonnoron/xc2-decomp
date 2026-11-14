#include "event/chara_ik_updater.h"

#include "event/chara_facial_util.h"
#include "gf/game/gf_game_party.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_util.h"

namespace event {

// The constructor at 0x71000b9044 writes flags at +0x8, the handle at
// +0x10, Vec3::zero at +0x20, and Vec2::zero at +0x30 through +0x70.
CharaIKUpdater::CharaIKUpdater() : unknown08(), unknown0c(), unknown10(gf::unknown020), unknown18(0.0f), unknown20(mm::Vec3::zero) {
  f32 x = mm::Vec2::zero.x;
  f32 y = mm::Vec2::zero.y;
  unknown30.x = x;
  unknown30.y = y;
  unknown40.x = x;
  unknown40.y = y;
  unknown50.x = x;
  unknown50.y = y;
  unknown60.x = x;
  unknown60.y = y;
  unknown70.x = x;
  unknown70.y = y;
}

void CharaIKUpdater::create(gf::GF_OBJ_HANDLE *handle) {
  this->unknown10 = handle;
  gf::GfObj *obj = gf::GfObjUtil::getObj(handle);
  if (obj != nullptr) {
    CharaFacialUtil::getLensLimit(unknown40, unknown50, unknown60, unknown70, obj);
  }
  unknown08.set(FLAG_UNKNOWN_0, true);
  unknown08.set(FLAG_UNKNOWN_1, true);
  unknown08.set(FLAG_UNKNOWN_2, true);
  unknown08.set(FLAG_UNKNOWN_3, true);
  unknown08.set(FLAG_UNKNOWN_4, false);
  unknown08.set(FLAG_UNKNOWN_6, false);
}

void CharaIKUpdater::render(const mm::Vec3 &position, f32 height) { gf::GfObjUtil::getObj(unknown10); }

void CharaIKUpdater::setAllIK(bool isEnable) {
  unknown08.set(FLAG_UNKNOWN_0, isEnable);
  unknown18 = 0.0f;
  unknown0c.set(REQUEST_UNKNOWN_0);
  unknown0c.set(REQUEST_UNKNOWN_1);
  unknown0c.set(REQUEST_UNKNOWN_2);
  unknown0c.set(REQUEST_UNKNOWN_3);
  unknown0c.set(REQUEST_UNKNOWN_4);
}

void CharaIKUpdater::setFootIK(bool isEnable, FOOT_TYPE type) {
  switch (type) {
  case FOOT_TYPE_UNKNOWN_0:
    unknown08.set(FLAG_UNKNOWN_1, isEnable);
    break;
  case FOOT_TYPE_UNKNOWN_1:
    unknown08.set(FLAG_UNKNOWN_2, isEnable);
    break;
  case FOOT_TYPE_UNKNOWN_2:
    unknown08.set(FLAG_UNKNOWN_3, isEnable);
    break;
  }
  unknown0c.set(REQUEST_UNKNOWN_1);
}

void CharaIKUpdater::setTargetIK(bool isEnable, f32 frame, bool isNoSpine) {
  if (isEnable) {
    unknown18 = frame;
    unknown08.set(FLAG_UNKNOWN_4, true);
    unknown08.set(FLAG_UNKNOWN_5, isNoSpine);
    unknown0c.set(REQUEST_UNKNOWN_2);
  } else if (unknown08.test(FLAG_UNKNOWN_4)) {
    unknown08.set(FLAG_UNKNOWN_4, false);
    unknown08.set(FLAG_UNKNOWN_5, isNoSpine);
    unknown18 = frame;
    unknown0c.set(REQUEST_UNKNOWN_2);
  }
}

void CharaIKUpdater::setTargetPos(const mm::Vec3 &position) {
  unknown20 = position;
  unknown0c.set(REQUEST_UNKNOWN_3);
}

void CharaIKUpdater::setLensIK(bool isEnable, f32 x, f32 y) {
  unknown30.x = x;
  unknown30.y = y;
  unknown08.set(FLAG_UNKNOWN_6, isEnable);
  unknown0c.set(REQUEST_UNKNOWN_4);
}

bool CharaIKUpdater::checkField(gf::GfObj *obj) {
  gf::GF_OBJ_HANDLE *handle = obj->unknownf8;
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
