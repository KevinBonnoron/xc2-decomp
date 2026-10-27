#include "gf/game/gf_game_obj.h"

#include "gf/data/gf_data_blade.h"
#include "gf/data/gf_object_type.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_manager.h"
#include "gf/object/gf_obj_util.h"
#include "mm_mtl/fixed_vector.h"

namespace gf {

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

void GfGameObj::enterStayObject(GF_OBJ_HANDLE *handle) { GfObjManager::enterStayObject(handle); }

void GfGameObj::enterStayObject(GF_OBJ_HANDLE *handle, GFATTACH attach, OPTMNT type) { GfObjManager::enterStayObject(GfMountManager::getHandle(handle, attach, type)); }

} // namespace gf
