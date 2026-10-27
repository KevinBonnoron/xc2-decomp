#include "gf/request/gf_req_scom.h"

#include <math.h>

#include "fw/fw_update_info.h"
#include "gf/data/gf_data_blade.h"
#include "gf/data/gf_data_en_book.h"
#include "gf/data/gf_data_map.h"
#include "gf/data/gf_data_param_acc.h"
#include "gf/game/gf_game_manager.h"
#include "gf/game/gf_game_obj.h"
#include "gf/game/gf_game_util.h"
#include "gf/gf_allocator.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_util.h"
#include "gf/request/gf_scom.h"
#include "gf/scom/gf_scom_enbook.h"
#include "gf/scom/gf_scom_obj.h"
#include "mm_mtl/fixed_vector.h"

namespace gf {

static const u32 unknown001 = 4; // Inferred role: object attribute bit cleared when destroying a game object; original name unknown.

SCOM::SCOM(GF_SCOM_HANDLE *handle, SCOM_TYPE type, SCOM_EXEC exec, u16 unknown10) : unknown08(handle), unknown10(unknown10), unknown14(exec), unknown18(type) {}

GF_OBJ_HANDLE *SCOM::getObjHandle() const { return INVALID_HANDLE; }

GF_SCOM_HANDLE *GfReqSmallCom::allocate() {
  s64 handle = unknownd868++;
  if (handle == -1) {
    handle++;
    unknownd868++;
  }
  return reinterpret_cast<GF_SCOM_HANDLE *>(handle);
}

bool SCOM_ENBOOK_IN_BATTLE::exec(const fw::UpdateInfo &) {
  GfDataEnBook::setAttackFlag(unknown1c);
  return true;
}

GF_SCOM_HANDLE *SCOM_ENBOOK_IN_BATTLE::create(GF_OBJ_HANDLE *handle) {
  DataParamAcc acc(handle);
#line 4274
  SCOM_ENBOOK_IN_BATTLE *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_ENBOOK_IN_BATTLE(GfReqSmallCom::get()->allocate(), acc.isValid() ? acc.getBdatId() : 0);
  return GfReqSmallCom::addRequestParallel(command);
}

bool SCOM_ENBOOK_BOSS_TIME::exec(const fw::UpdateInfo &) {
  GfDataEnBook::setClearNamedTime(unknown1c, unknown20);
  return true;
}

GF_SCOM_HANDLE *SCOM_ENBOOK_BOSS_TIME::create(GF_OBJ_HANDLE *handle, u32 time) {
  DataParamAcc acc(handle);
#line 4289
  SCOM_ENBOOK_BOSS_TIME *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_ENBOOK_BOSS_TIME(GfReqSmallCom::get()->allocate(), acc.isValid() ? acc.getBdatId() : 0, time);
  return GfReqSmallCom::addRequestParallel(command);
}

bool SCOM_ENBOOK_DEFEAT_ENEMY::exec(const fw::UpdateInfo &) {
  GfDataEnBook::incDefeatNum(unknown1c);
  return true;
}

GF_SCOM_HANDLE *SCOM_ENBOOK_DEFEAT_ENEMY::create(GF_OBJ_HANDLE *handle) {
  DataParamAcc acc(handle);
#line 4304
  SCOM_ENBOOK_DEFEAT_ENEMY *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_ENBOOK_DEFEAT_ENEMY(GfReqSmallCom::get()->allocate(), acc.isValid() ? acc.getBdatId() : 0);
  return GfReqSmallCom::addRequestParallel(command);
}

bool SCOM_ENBOOK_DEAD_PLAYER::exec(const fw::UpdateInfo &) {
  GfDataEnBook::incDeadNum(unknown1c);
  return true;
}

GF_SCOM_HANDLE *SCOM_ENBOOK_DEAD_PLAYER::create(GF_OBJ_HANDLE *handle) {
  DataParamAcc acc(handle);
#line 4319
  SCOM_ENBOOK_DEAD_PLAYER *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_ENBOOK_DEAD_PLAYER(GfReqSmallCom::get()->allocate(), acc.isValid() ? acc.getBdatId() : 0);
  return GfReqSmallCom::addRequestParallel(command);
}

bool SCOM_ADD_TRUST::exec(const fw::UpdateInfo &) {
  if (unknown20 == 0) {
    mm::mtl::FixedVector<u16, 422> blades;
    GfDataBlade::getListPartyAll(blades);
    for (const u16 *it = blades.begin(); it != blades.end(); ++it) {
      GfGameUtil::addTrustPoint(*it, unknown1c);
    }
  } else {
    GfGameUtil::addTrustPoint(unknown20, unknown1c);
  }
  return true;
}

GF_SCOM_HANDLE *SCOM_ADD_TRUST::create(u32 blade, u32 point) {
  if (point != 0) {
#line 535
    SCOM_ADD_TRUST *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_ADD_TRUST(GfReqSmallCom::get()->allocate(), blade, point);
    return GfReqSmallCom::addRequestParallel(command);
  }
  return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
}

bool SCOM_TARGET_UI::exec(const fw::UpdateInfo &) {
  GfGameManager::setTargetUI(unknown20);
  return true;
}

void SCOM_TARGET_UI::create(GF_OBJ_HANDLE *target) {
#line 1942
  SCOM_TARGET_UI *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_TARGET_UI(GfReqSmallCom::get()->allocate(), target);
  GfReqSmallCom::addRequestParallel(command);
}

bool SCOM_ZONE::exec(const fw::UpdateInfo &) {
  if (!GfGameManager::isControlFree()) {
    return false;
  }
  u32 map = GfGameManager::getMapID();
  if (map == unknown1c && !GfDataMap::isMapCompleteFlag(map)) {
    GfDataMap::setMapCompleteFlag(unknown1c);
  }
  return true;
}

void SCOM_ZONE::create(u32 map) {
#line 4259
  SCOM_ZONE *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_ZONE(GfReqSmallCom::get()->allocate(), map);
  GfReqSmallCom::addRequestParallel(command);
}

bool SCOM_LEVELUP_DEVELOP::exec(const fw::UpdateInfo &) {
  if (!GfGameManager::isControlFree()) {
    return false;
  }
  GfGameUtil::execDevelopLevelUp();
  return true;
}

void SCOM_LEVELUP_DEVELOP::create() {
#line 431
  SCOM_LEVELUP_DEVELOP *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_LEVELUP_DEVELOP(GfReqSmallCom::get()->allocate());
  GfReqSmallCom::addRequestParallel(command);
}

bool SCOM_DESTROY_GAME_OBJ::exec(const fw::UpdateInfo &) {
  GfGameObj::destroyGameObjWithAttribute(unknown20, unknown28, unknown2c);
  return true;
}

void SCOM_DESTROY_GAME_OBJ::create(GF_OBJ_HANDLE *handle, f32 fadeTime, u32 attribute) {
  GfObjAcc acc(handle);
  acc.setFlag(OBJ_FLAG_UI_HIDDEN, true);
  acc.setAttribute(acc.getAttribute() & ~unknown001);
#line 692
  SCOM_DESTROY_GAME_OBJ *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_DESTROY_GAME_OBJ(GfReqSmallCom::get()->allocate(), handle, fadeTime, attribute);
  GfReqSmallCom::addRequestParallel(command);
}

SCOM_OBJ_VFADE_OFF::SCOM_OBJ_VFADE_OFF(GF_SCOM_HANDLE *handle, GF_OBJ_HANDLE *target) : SCOM(handle, SCOM_TYPE_UNKNOWN_67, SCOM_EXEC_UNKNOWN_0, 1), unknown20(target) {}

bool SCOM_OBJ_VFADE_OFF::exec(const fw::UpdateInfo &) {
  GfObjUtil::setVolumeFadeUserFlag(unknown20, false);
  return true;
}

GF_SCOM_HANDLE *SCOM_OBJ_VFADE_OFF::create(GF_OBJ_HANDLE *handle) {
  if (handle != INVALID_HANDLE) {
#line 1305
    SCOM_OBJ_VFADE_OFF *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_OBJ_VFADE_OFF(GfReqSmallCom::get()->allocate(), handle);
    return GfReqSmallCom::addRequestParallel(command);
  }
  return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
}

bool SCOM_ADD_SP::exec(const fw::UpdateInfo &) {
  u32 driverId = unknown20;
  if (driverId == 0) {
    if (unknown28 == INVALID_HANDLE) {
      driverId = 0;
    } else {
      GfObjAcc acc(unknown28);
      driverId = acc.getDriverId();
    }
  }
  GfGameUtil::addSP(driverId, unknown1c);
  return true;
}

GF_SCOM_HANDLE *SCOM_ADD_SP::create(GF_OBJ_HANDLE *handle, int skillPoint) {
  if (skillPoint != 0) {
#line 348
    SCOM_ADD_SP *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_ADD_SP(GfReqSmallCom::get()->allocate(), skillPoint, 0, handle);
    return GfReqSmallCom::addRequestParallel(command);
  }
  return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
}

GF_SCOM_HANDLE *SCOM_ADD_SP::create(u32 driver, int skillPoint) {
  if (skillPoint != 0) {
#line 353
    SCOM_ADD_SP *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_ADD_SP(GfReqSmallCom::get()->allocate(), skillPoint, driver, INVALID_HANDLE);
    return GfReqSmallCom::addRequestParallel(command);
  }
  return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
}

bool SCOM_EXEC_LVUP::exec(const fw::UpdateInfo &) {
  u32 driverId = unknown20;
  if (driverId == 0) {
    if (unknown28 == INVALID_HANDLE) {
      driverId = 0;
    } else {
      GfObjAcc acc(unknown28);
      driverId = acc.getDriverId();
    }
  }
  GfGameUtil::execLevelUp(driverId, unknown1c);
  return true;
}

GF_SCOM_HANDLE *SCOM_EXEC_LVUP::create(u32 level, GF_OBJ_HANDLE *handle) {
  if (level != 0) {
#line 238
    SCOM_EXEC_LVUP *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_EXEC_LVUP(GfReqSmallCom::get()->allocate(), level, 0, handle);
    return GfReqSmallCom::addRequestParallel(command);
  }
  return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
}

GF_SCOM_HANDLE *SCOM_EXEC_LVUP::create(u32 level, u32 driver) {
  if (level != 0) {
#line 243
    SCOM_EXEC_LVUP *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_EXEC_LVUP(GfReqSmallCom::get()->allocate(), level, driver, INVALID_HANDLE);
    return GfReqSmallCom::addRequestParallel(command);
  }
  return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
}

SCOM_OBJ_ALPHA::SCOM_OBJ_ALPHA(GF_SCOM_HANDLE *handle, GF_OBJ_HANDLE *target, f32 time, f32 alpha)
    : SCOM(handle, SCOM_TYPE_UNKNOWN_40, SCOM_EXEC_UNKNOWN_0, 1), unknown20(target), unknown28(time), unknown2c(0.0f), unknown30(alpha), unknown34(-1.0f) {}

bool SCOM_OBJ_ALPHA::exec(const fw::UpdateInfo &info) {
  GfObjAcc acc(unknown20);
  if (!acc.isValid()) {
    return true;
  }
  if (unknown34 < 0.0f) {
    unknown34 = acc.getAlphaNormal();
  }
  f32 time = unknown28;
  f32 alpha = unknown30;
  f32 startAlpha = unknown34;
  if (time > 0.000001f && fabsf(alpha - startAlpha) >= 0.000001f) {
    f32 elapsed = info.unknown04 + unknown2c;
    if (elapsed > time) {
      elapsed = time;
    }
    unknown2c = elapsed;
    acc.setAlphaNormal(alpha * (elapsed / time) + startAlpha * (1.0f - elapsed / time));
    if (unknown2c < unknown28) {
      return false;
    }
  } else {
    acc.setAlphaNormal(alpha);
  }
  return true;
}

GF_SCOM_HANDLE *SCOM_OBJ_ALPHA::create(GF_OBJ_HANDLE *handle, f32 time, f32 alpha) {
  if (handle != INVALID_HANDLE) {
#line 1268
    SCOM_OBJ_ALPHA *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_OBJ_ALPHA(GfReqSmallCom::get()->allocate(), handle, time, alpha);
    return GfReqSmallCom::addRequestParallel(command);
  }
  return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
}

bool GfReqSmallCom::isExistCommand() {
  GfReqSmallCom *smallCom = get();
  if (smallCom->unknown4820 != 0) {
    return true;
  }

  return smallCom->unknown9040 != 0;
}

} // namespace gf
