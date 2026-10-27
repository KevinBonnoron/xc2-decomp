#include "gf/game/gf_game_obj.h"

#include "gf/data/gf_data_blade.h"
#include "gf/data/gf_data_enemy.h"
#include "gf/data/gf_data_param_acc.h"
#include "gf/data/gf_object_type.h"
#include "gf/event/gf_event.h"
#include "gf/game/event/gf_game_event.h"
#include "gf/game/gf_game_mount.h"
#include "gf/game/gf_game_obj_enemy.h"
#include "gf/game/gf_game_util.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_manager.h"
#include "gf/object/gf_obj_setup.h"
#include "gf/object/gf_obj_util.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/rtti.h"

namespace gf {
struct GF_MOUNT_HANDLE;

bool GfGameObj::isInitialized() {
  GfGameObj *gameObj = get();
  if (gameObj != nullptr) {
    return gameObj->unknown55c70;
  }
  return false;
}

bool GfGameObj::isExistEnemy() { return get()->unknown9050.size() != 0; }

const mm::mtl::FixedList<GF_OBJ_HANDLE *, GAME_OBJ_LIST_CAPACITY> *GfGameObj::getListEnemyBlade() { return &get()->unknownd870; }

bool GfGameObj::isGameObjWaiting(GF_OBJ_HANDLE *handle) { return GfObjUtil::testFlag(handle, OBJ_FLAG_WAIT); }

bool GfGameObj::isDestroyGameObj(GF_OBJ_HANDLE *handle) {
  GfObjAcc acc(handle);
  if (!acc.isValid()) {
    return true;
  }
  return !acc.testFlag(OBJ_FLAG_UNKNOWN_E);
}

bool GfGameObj::isEnterGameObj(GF_OBJ_HANDLE *handle) {
  if (handle == reinterpret_cast<GF_OBJ_HANDLE *>(-1)) {
    return false;
  }
  GfGameObj *gameObj = get();
  for (mm::mtl::FixedList<INOUT, GAME_OBJ_LIST_CAPACITY>::iterator it = gameObj->unknown3f1d0.begin(); it != gameObj->unknown3f1d0.end(); ++it) {
    if (it->unknown00 == handle) {
      return true;
    }
  }
  return false;
}

void GfGameObj::setupEnterGameObj(GF_OBJ_HANDLE *handle, f32 fadeTime) {
  if (handle == reinterpret_cast<GF_OBJ_HANDLE *>(-1)) {
    return;
  }
  GfObjAcc acc(handle);
  GfGameObj *gameObj = get();
  for (mm::mtl::FixedList<INOUT, GAME_OBJ_LIST_CAPACITY>::iterator it = gameObj->unknown3f1d0.begin(); it != gameObj->unknown3f1d0.end(); ++it) {
    if (it->unknown00 == handle) {
      if (acc.getType() == OBJECT_TYPE_BLADE && GfDataBlade::isDummyBlade(acc.getBladeId())) {
        return;
      }
      f32 time = fadeTime;
      if (fadeTime < 1e-6f) {
        time = 0.0f;
      }
      it->unknown08 = time;
      f32 alpha = 0.0f;
      if (fadeTime == 0.0f) {
        alpha = 1.0f;
      }
      acc.setAlphaLife(alpha);
      return;
    }
  }
}

GfObj *GfGameObj::getObj(GF_OBJ_HANDLE *handle) {
  GfGameObj *gameObj = get();
  GfObjAcc acc(handle);
  for (mm::mtl::FixedList<INOUT, GAME_OBJ_LIST_CAPACITY>::iterator it = gameObj->unknown3f1d0.begin(); it != gameObj->unknown3f1d0.end(); ++it) {
    if (it->unknown00 == handle) {
      return GfObjUtil::getObj(handle);
    }
  }
  if (acc.testFlag(OBJ_FLAG_UNKNOWN_E)) {
    return GfObjUtil::getObj(handle);
  }
  return nullptr;
}

bool GfGameObj::isEffectFadeEnd(const INOUT &inout, const GfObjAcc &acc) const {
  if (!inout.unknown16) {
    return false;
  }
  if (acc.isValid()) {
    return inout.unknown08 < inout.unknown0c;
  }
  return false;
}

bool GfGameObj::isBattle(const mm::mtl::FixedList<GF_OBJ_HANDLE *, GAME_OBJ_LIST_CAPACITY> &list) const {
  for (mm::mtl::FixedList<GF_OBJ_HANDLE *, GAME_OBJ_LIST_CAPACITY>::const_iterator it = list.begin(); it != list.end(); ++it) {
    GfObjAcc acc(*it);
    if (acc.isBattle()) {
      return true;
    }
  }
  return false;
}

mm::mtl::FixedList<GF_OBJ_HANDLE *, GAME_OBJ_LIST_CAPACITY> *GfGameObj::getListType(u32 objectType, GF_OBJ_HANDLE *handle) {
  switch (objectType) {
  case 0:
  case 0xe:
    return &unknown28930;
  default:
    return &unknown3a9b0;
  case 3:
    return &unknown10;
  case 4:
    return &unknown4830;
  case 5:
    if (GfObjUtil::isEnemyBlade(handle)) {
      return &unknownd870;
    }
    return &unknown9050;
  case 6:
    return &unknown12090;
  case 7:
    return &unknown168b0;
  case 8:
    return &unknown1b0d0;
  case 9:
    return &unknown1f8f0;
  case 10:
    return &unknown24110;
  case 0xb:
    return &unknown31970;
  case 0xc:
    return &unknown2d150;
  case 0xd:
    return &unknown36190;
  }
}

const mm::mtl::FixedList<GF_OBJ_HANDLE *, GAME_OBJ_LIST_CAPACITY> *GfGameObj::getList(u32 objectType) { return get()->getListType(objectType, reinterpret_cast<GF_OBJ_HANDLE *>(-1)); }

void GfGameObj::getList(mm::mtl::FixedVector<GF_OBJ_HANDLE *, GAME_OBJ_LIST_CAPACITY> &list, u32 objectType) {
  if (get() == nullptr) {
    return;
  }
  const mm::mtl::FixedList<GF_OBJ_HANDLE *, GAME_OBJ_LIST_CAPACITY> *objects = getList(objectType);
  for (mm::mtl::FixedList<GF_OBJ_HANDLE *, GAME_OBJ_LIST_CAPACITY>::const_iterator it = objects->begin(); it != objects->end(); ++it) {
    list.push_back(*it);
  }
}

void GfGameObj::getListEnemyBlade(mm::mtl::FixedVector<GF_OBJ_HANDLE *, GAME_OBJ_LIST_CAPACITY> &list) {
  if (get() == nullptr) {
    return;
  }
  mm::mtl::FixedList<GF_OBJ_HANDLE *, GAME_OBJ_LIST_CAPACITY> &enemyBlades = get()->unknownd870;
  for (mm::mtl::FixedList<GF_OBJ_HANDLE *, GAME_OBJ_LIST_CAPACITY>::iterator it = enemyBlades.begin(); it != enemyBlades.end(); ++it) {
    list.push_back(*it);
  }
}

bool GfGameObj::isEmpty() {
  GfGameObj *gameObj = get();
  if (gameObj == nullptr) {
    return true;
  }
  if (gameObj->unknown9050.size() != 0) {
    return false;
  }
  if (gameObj->unknownd870.size() != 0) {
    return false;
  }
  if (gameObj->unknown12090.size() != 0) {
    return false;
  }
  if (gameObj->unknown168b0.size() != 0) {
    return false;
  }
  if (gameObj->unknown31970.size() != 0) {
    return false;
  }
  if (gameObj->unknown10.size() != 0) {
    return false;
  }
  if (gameObj->unknown4830.size() != 0) {
    return false;
  }
  if (gameObj->unknown1b0d0.size() != 0) {
    return false;
  }
  if (gameObj->unknown1f8f0.size() != 0) {
    return false;
  }
  if (gameObj->unknown24110.size() != 0) {
    return false;
  }
  if (gameObj->unknown2d150.size() != 0) {
    return false;
  }
  if (gameObj->unknown28930.size() != 0) {
    return false;
  }
  if (gameObj->unknown36190.size() != 0) {
    return false;
  }
  if (gameObj->unknown3f1d0.size() != 0) {
    return false;
  }
  return gameObj->unknown47a00.size() == 0;
}

void GfGameObj::postUpdate(const fw::UpdateInfo &info) { get()->updateObjectProperty(); }

void GfGameObj::updateObjectProperty() {
  for (mm::mtl::FixedList<GF_OBJ_HANDLE *, GAME_OBJ_LIST_CAPACITY>::iterator it = unknown10.begin(); it != unknown10.end(); ++it) {
    GfGameUtil::flushProperty(*it);
  }
  for (mm::mtl::FixedList<GF_OBJ_HANDLE *, GAME_OBJ_LIST_CAPACITY>::iterator it = unknown4830.begin(); it != unknown4830.end(); ++it) {
    GfGameUtil::flushProperty(*it);
  }
  mm::mtl::FixedList<GF_OBJ_HANDLE *, GAME_OBJ_LIST_CAPACITY> &enemies = GfObjUtil::isEnemyBlade(reinterpret_cast<GF_OBJ_HANDLE *>(-1)) ? unknownd870 : unknown9050;
  for (mm::mtl::FixedList<GF_OBJ_HANDLE *, GAME_OBJ_LIST_CAPACITY>::iterator it = enemies.begin(); it != enemies.end(); ++it) {
    GfGameUtil::flushProperty(*it);
  }
  for (mm::mtl::FixedList<GF_OBJ_HANDLE *, GAME_OBJ_LIST_CAPACITY>::iterator it = unknown28930.begin(); it != unknown28930.end(); ++it) {
    GfGameUtil::flushProperty(*it);
  }
}

void GfGameObj::updateObjectProperty(u32 objectType) {
  mm::mtl::FixedList<GF_OBJ_HANDLE *, GAME_OBJ_LIST_CAPACITY> *list = getListType(objectType, reinterpret_cast<GF_OBJ_HANDLE *>(-1));
  for (mm::mtl::FixedList<GF_OBJ_HANDLE *, GAME_OBJ_LIST_CAPACITY>::iterator it = list->begin(); it != list->end(); ++it) {
    GfGameUtil::flushProperty(*it);
  }
}

void GfGameObj::enterStayObject(GF_OBJ_HANDLE *handle) { GfObjManager::enterStayObject(handle); }

void GfGameObj::enterStayObject(GF_OBJ_HANDLE *handle, GFATTACH attach, OPTMNT type) { GfObjManager::enterStayObject(GfMountManager::getHandle(handle, attach, type)); }

void GfGameObj::enterStayObject(GF_MOUNT_HANDLE *mountHandle) {
  GfGameMount *mount = GfMountManager::getMount(mountHandle);
  if (mount != nullptr) {
    u32 count = mount->getAllWeapons();
    for (u32 index = 0; index < count; index++) {
      GfObjManager::enterStayObject(mount->getAllWeapons(index));
    }
  }
}

void GfGameObj::enterStayObjectMount(GF_OBJ_HANDLE *handle, GFATTACH attach) {
  GfGameMount *mount = GfMountManager::getMount(GfObjUtil::getMountHandle(handle, attach));
  if (mount != nullptr) {
    u32 count = mount->getAllWeapons();
    for (u32 index = 0; index < count; index++) {
      GfObjManager::enterStayObject(mount->getAllWeapons(index));
    }
  }
}

void GfGameObj::enterStayObjectWithVolumeFade(GF_OBJ_HANDLE *handle) {
  GfObjSetup *setup = GfObjUtil::getObjSetup(handle);
  if (setup != nullptr) {
    setup->unknown50 = 1.0f;
    setup->unknown60 = false;
    setup->unknown64 = VFEFF_UNKNOWN_4;
  }
  GfObjManager::enterStayObject(handle);
}

void GfGameObj::enterStayObjectWithVolumeFade(GF_OBJ_HANDLE *handle, GFATTACH attach, OPTMNT type) { enterStayObjectWithVolumeFade(GfMountManager::getHandle(handle, attach, type)); }

void GfGameObj::enterStayObjectMountWithVolumeFade(GF_OBJ_HANDLE *handle, GFATTACH attach) {
  GfGameMount *mount = GfMountManager::getMount(GfObjUtil::getMountHandle(handle, attach));
  if (mount != nullptr) {
    u32 count = mount->getAllWeapons();
    for (u32 index = 0; index < count; index++) {
      enterStayObjectWithVolumeFade(mount->getAllWeapons(index));
    }
  }
}

void GfGameObj::enterStayObjectWithVolumeFade(GF_MOUNT_HANDLE *mountHandle) {
  GfGameMount *mount = GfMountManager::getMount(mountHandle);
  if (mount != nullptr) {
    u32 count = mount->getAllWeapons();
    for (u32 index = 0; index < count; index++) {
      enterStayObjectWithVolumeFade(mount->getAllWeapons(index));
    }
  }
}

void GfGameObj::addInObj(GF_OBJ_HANDLE *handle, f32 fadeTime) {
  GfGameEvent::applySetDispObject(handle);
  GfObjAcc acc(handle);
  INOUT inout;
  inout.unknown00 = handle;
  inout.unknown15 = true;
  inout.unknown08 = fadeTime;
  inout.unknown10 = acc.getAlphaLife();
  inout.unknown14 = false;
  inout.unknown16 = false;
  unknown3f1d0.push_back(inout);
  acc.setFlag(OBJ_FLAG_UNKNOWN_F, true);
  if (acc.getType() == OBJECT_TYPE_ENEMY) {
    acc.getObj()->setUpdateComponent(true);
  }
}

void GfGameObj::setupLeaveGameObj(GF_OBJ_HANDLE *handle, f32 fadeTime) {
  if (handle != INVALID_HANDLE) {
    GfGameObj *gameObj = get();
    GfObjAcc acc(handle);
    if (gameObj->addOutObj(handle, fadeTime, true)) {
      acc.setCollisionChar(false);
      if (acc.testFlag(OBJ_FLAG_LOADED_WAIT)) {
        if (acc.getType() == OBJECT_TYPE_BLADE) {
          mm::mtl::dynamicCast<GfObjSetupBlade>(GfObjManager::getObjInfo(handle)->unknown30)->unknown70 = true;
        } else if (acc.getType() == OBJECT_TYPE_PC_WEAPON) {
          mm::mtl::dynamicCast<GfObjSetupWeapon>(GfObjManager::getObjInfo(handle)->unknown30)->unknown70 = true;
        }
      }
    }
  }
}

void GfGameObj::setupLeaveGameObjMount(GF_OBJ_HANDLE *handle, GFATTACH attach, f32 fadeTime) {
  GfGameMount *mount = GfMountManager::getMount(GfObjUtil::getMountHandle(handle, attach));
  if (mount != nullptr) {
    u32 count = mount->getAllWeapons();
    for (u32 index = 0; index < count; index++) {
      setupLeaveGameObj(mount->getAllWeapons(index), fadeTime);
    }
  }
}

void GfGameObj::changeStopLayer(u32 objectType, bool isStop) {
  mm::mtl::FixedList<GF_OBJ_HANDLE *, GAME_OBJ_LIST_CAPACITY> *list = get()->getListType(objectType, INVALID_HANDLE);
  for (mm::mtl::FixedList<GF_OBJ_HANDLE *, GAME_OBJ_LIST_CAPACITY>::iterator it = list->begin(); it != list->end(); ++it) {
    GfGameUtil::changeStopLayer(*it, isStop);
  }
}

void GfGameObj::changeStopLayerIgnoreEventObj(u32 layer, bool isIgnore) {
  mm::mtl::FixedList<GF_OBJ_HANDLE *, GAME_OBJ_LIST_CAPACITY> *list = get()->getListType(layer, INVALID_HANDLE);
  for (mm::mtl::FixedList<GF_OBJ_HANDLE *, GAME_OBJ_LIST_CAPACITY>::iterator it = list->begin(); it != list->end(); ++it) {
    if (!GfObjUtil::getObjSetup(*it)->isEvent()) {
      GfGameUtil::changeStopLayer(*it, isIgnore);
    }
  }
}

void GfGameObj::refreshBdat(GF_OBJ_HANDLE *handle) {
  GfObjSetupEnemy *setup = GfObjUtil::getObjSetup<GfObjSetupEnemy>(handle);
  if (setup != nullptr) {
    GfDataEnemy::setupSDataEnemy(*setup->unknowna0, setup->unknowna0->unknown00, setup->unknowna0->unknowna8);
  }
}

void GfGameObj::refreshBdatInOut(INOUT &inout) {
  GfObjAcc acc(inout.unknown00);
  if (acc.getType() == OBJECT_TYPE_ENEMY) {
    GfObjSetupEnemy *setup = GfObjUtil::getObjSetup<GfObjSetupEnemy>(inout.unknown00);
    if (setup != nullptr) {
      GfDataEnemy::setupSDataEnemy(*setup->unknowna0, setup->unknowna0->unknown00, setup->unknowna0->unknowna8);
    }
  }
}

bool GfGameObj::isBattle() {
  GfGameObj *gameObj = get();
  return gameObj->isBattle(gameObj->unknown10) || gameObj->isBattle(gameObj->unknown9050);
}

void GfGameObj::destroyGameObj(GF_OBJ_HANDLE *handle, f32 fadeTime) {
  if (GfObjUtil::getObj(handle) != nullptr && !get()->addOutObj(handle, fadeTime, true)) {
    GfObjUtil::destroy(handle);
  }
}

void GfGameObj::destroyGameObjWithAttribute(GF_OBJ_HANDLE *handle, f32 fadeTime, u32 attribute) {
  if (GfObjUtil::getObj(handle) == nullptr) {
    return;
  }
  GfGameObj *gameObj = get();
  if (attribute != 0) {
    DestroyAttribute destroyAttribute = {handle, attribute};
    gameObj->unknown54240.push_back(destroyAttribute);
  }
  if (!gameObj->addOutObj(handle, fadeTime, true)) {
    GfObjUtil::destroy(handle);
  }
}

u32 GfGameObj::getObjNumberByEnArrangeId(u32 arrange) {
  u32 count = 0;
  if (arrange == 0) {
    return count;
  }
  GfGameObj *gameObj = get();
  mm::mtl::FixedList<GF_OBJ_HANDLE *, GAME_OBJ_LIST_CAPACITY> &enemies = GfObjUtil::isEnemyBlade(INVALID_HANDLE) ? gameObj->unknownd870 : gameObj->unknown9050;
  for (mm::mtl::FixedList<GF_OBJ_HANDLE *, GAME_OBJ_LIST_CAPACITY>::iterator it = enemies.begin(); it != enemies.end(); ++it) {
    DataParamAcc paramAcc(*it);
    u32 bdatId = 0;
    if (paramAcc.isValid()) {
      bdatId = paramAcc.getBdatId();
    }
    if (bdatId == arrange) {
      count++;
    }
  }
  for (mm::mtl::FixedList<INOUT, GAME_OBJ_LIST_CAPACITY>::iterator it = unknown3f1d0.begin(); it != unknown3f1d0.end(); ++it) {
    DataParamAcc paramAcc((*it).unknown00);
    if (paramAcc.getObjType() == OBJECT_TYPE_ENEMY) {
      u32 bdatId = 0;
      if (paramAcc.isValid()) {
        bdatId = paramAcc.getBdatId();
      }
      if (bdatId == arrange) {
        count++;
      }
    }
  }
  for (mm::mtl::FixedList<INOUT, GAME_OBJ_LIST_CAPACITY>::iterator it = unknown47a00.begin(); it != unknown47a00.end(); ++it) {
    DataParamAcc paramAcc((*it).unknown00);
    if (paramAcc.getObjType() == OBJECT_TYPE_ENEMY) {
      u32 bdatId = 0;
      if (paramAcc.isValid()) {
        bdatId = paramAcc.getBdatId();
      }
      if (bdatId == arrange) {
        count++;
      }
    }
  }
  return count;
}

void GfGameObj::flushEvent() {
  for (GF_OBJ_HANDLE **it = unknown50230.begin(); it != unknown50230.end(); ++it) {
    if (unknown55c68 != nullptr) {
      unknown55c68->enterEnemyObj(*it);
    }
    GfEvent::callGameObjEnter(*it);
  }
  for (GF_OBJ_HANDLE **it = unknown52238.begin(); it != unknown52238.end(); ++it) {
    if (unknown55c68 != nullptr) {
      unknown55c68->leaveEnemyObj(*it);
    }
    GfEvent::callGameObjLeave(*it);
  }
  unknown50230.clear();
  unknown52238.clear();
}

void GfGameObj::setupEnterGameObjMount(GF_OBJ_HANDLE *handle, GFATTACH attach, f32 fadeTime) {
  GfGameMount *mount = GfMountManager::getMount(GfObjUtil::getMountHandle(handle, attach));
  if (mount != nullptr) {
    u32 count = mount->getAllWeapons();
    for (u32 index = 0; index < count; index++) {
      setupEnterGameObj(mount->getAllWeapons(index), fadeTime);
    }
  }
}

} // namespace gf
