#include "gf/game/gf_game_obj.h"

#include "fw/fw_transform.h"
#include "fw/fw_update_info.h"
#include "gf/asset/gf_asset_manager.h"
#include "gf/data/gf_data_blade.h"
#include "gf/data/gf_data_enemy.h"
#include "gf/data/gf_data_param_acc.h"
#include "gf/data/gf_object_type.h"
#include "gf/event/gf_event.h"
#include "gf/game/event/gf_game_event.h"
#include "gf/game/gf_game_manager.h"
#include "gf/game/gf_game_mount.h"
#include "gf/game/gf_game_obj_enemy.h"
#include "gf/game/gf_game_party.h"
#include "gf/game/gf_game_ride.h"
#include "gf/game/gf_game_scene.h"
#include "gf/game/gf_game_search_obj.h"
#include "gf/game/gf_game_util.h"
#include "gf/gf_allocator.h"
#include "gf/object/component/gf_com_transform.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_manager.h"
#include "gf/object/gf_obj_setup.h"
#include "gf/object/gf_obj_util.h"
#include "mm_math/mm_quat.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/algorithm.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/rtti.h"

namespace gf {
struct GF_MOUNT_HANDLE;

void GfGameObj::build(const GfSetupParam &param) {
  // __LINE__ must be 213 as in the original file: it is the line argument of the allocation.
#line 213
  new (getAllocator(ALLOCATOR_UNKNOWN_1), __FILE__, __LINE__, 8) GfGameObj(param);
}

GfGameObj::GfGameObj(const GfSetupParam &param) : unknown55c68(nullptr), unknown55c70(false) {
  initialize(param);
  GfObjManager::addListener(this, OBJEVT_UNKNOWN_0);
}

GfGameObj::~GfGameObj() { GfObjManager::removeListener(this); }

void GfGameObj::finalize() {
  unknown54240.clear();
  GfGameSearchObj::destroy();
  if (unknown55c68 != nullptr) {
    delete unknown55c68;
    unknown55c68 = nullptr;
  }
  unknown55c70 = false;
}

void GfGameObj::destroy() {
  GfGameObj *gameObj = get();
  gameObj->finalize();
  delete gameObj;
}

void GfGameObj::calcCameraFade(const mm::mtl::FixedList<GF_OBJ_HANDLE *, GAME_UNKNOWN_1024> &list, const mm::Vec3 &cameraPosition) {
  for (mm::mtl::FixedList<GF_OBJ_HANDLE *, GAME_UNKNOWN_1024>::const_iterator it = list.begin(); it != list.end(); ++it) {
    GfObjAcc acc(*it);
    if (acc.getObj()->unknown118) {
      mm::Vec3 position = acc.getWorldTransformNoSync().unknown00;
      f32 radius = acc.getModelRadius();
      f32 height = position.y + radius;
      f32 dx = position.x - cameraPosition.x;
      f32 dy = height - cameraPosition.y;
      f32 dz = position.z - cameraPosition.z;
      if (radius >= 50.0f || dx * dx + dy * dy + dz * dz < 400.0f || acc.getAlphaCamera() < 1.0f || acc.getAlpha() != acc.getModelAlpha()) {
        acc.setCalcCameraAlpha();
      }
    }
  }
}

void GfGameObj::enableGameObj(GfObjAcc &acc, bool isEnable) {
  acc.setFlag(OBJ_FLAG_UNKNOWN_14, isEnable);
  acc.setCollisionChar(isEnable);
  acc.getObj()->setUpdateComponent(isEnable);
  if (!isEnable) {
    if (acc.isPartyObj()) {
      if (GfGameParty::getPartyId(acc.getHandle()) != PARTY_UNKNOWN_4294967295 && (acc.getType() == OBJECT_TYPE_PC || acc.getType() == OBJECT_TYPE_BLADE)) {
        GfGameUtil::resetFormationParam(acc.getHandle());
      }
    }
    unknown52238.push_back(acc.getHandle());
  } else {
    unknown50230.push_back(acc.getHandle());
  }
}

void GfGameObj::removeGameObjCommon(GfObjAcc &acc) {
  if (acc.isPartyObj() && acc.getType() != OBJECT_TYPE_PC_WEAPON) {
    acc.getPartyID();
    if (GfGameRide::testRideOn() && GfGameScene::get() != nullptr && GfGameScene::get()->isRideObj(acc.getHandle())) {
      GfGameRide::setRideOn(false);
    }
  }
  enableGameObj(acc, false);
  acc.setFlag(OBJ_FLAG_UNKNOWN_17, false);
  if (acc.isReload() && !acc.hasParent() && GfObjUtil::getParentHandle(acc.getHandle()) == unknown020) {
    GfObj *obj = acc.getObj();
    if (obj != nullptr && obj->getComponent<GfComTransform>() != nullptr) {
      GFOBJ_INFO *info = acc.unknown00;
      const fw::Transform &transform = acc.getWorldTransform();
      info->unknown50 = transform.unknown00;
      info->unknown60 = transform.unknown10;
    }
  }
  unknown55c68->leaveEnemyObj(acc.getHandle());
  GfObjManager *manager = GfObjManager::get();
  if (manager != nullptr) {
    mm::mtl::FixedList<GF_OBJ_HANDLE *, 768> followObjs;
    manager->getFollowObj(followObjs, acc.getHandle());
    for (GF_OBJ_HANDLE *followObj : followObjs) {
      GfObjUtil::unmountFromBone(followObj);
    }
    GfObjUtil::unmountFromBone(acc.getHandle());
  }
  int partyId = acc.getPartyID();
  bool isReload = acc.isReload();
  if (partyId == -1) {
    if (!isReload && !acc.isRebuild()) {
      return;
    }
    if (acc.testFlag(OBJ_FLAG_UNKNOWN_8) && (acc.getType() == OBJECT_TYPE_BLADE || acc.getType() == OBJECT_TYPE_PC_WEAPON)) {
      acc.setFlag(OBJ_FLAG_UNKNOWN_9, true);
    }
    return;
  }
  if (!isReload && !acc.isRebuild()) {
    return;
  }
  if (!acc.testFlag(OBJ_FLAG_UNKNOWN_8)) {
    return;
  }
  if (acc.getType() != OBJECT_TYPE_BLADE && acc.getType() != OBJECT_TYPE_PC_WEAPON) {
    return;
  }
  DataParamAcc paramAcc(GfGameParty::getHandleDriver(acc.getPartyID()));
  int bladeSet = paramAcc.getBladeSet(false);
  if (acc.getType() == OBJECT_TYPE_BLADE) {
    GfObjSetupBlade *setup = mm::mtl::dynamicCast<GfObjSetupBlade>(GfObjManager::getObjInfo(acc.getHandle())->unknown30);
    acc.setFlag(OBJ_FLAG_UNKNOWN_9, bladeSet == setup->unknown6c);
  } else if (acc.getType() == OBJECT_TYPE_PC_WEAPON) {
    GfObjSetupWeapon *setup = mm::mtl::dynamicCast<GfObjSetupWeapon>(GfObjManager::getObjInfo(acc.getHandle())->unknown30);
    acc.setFlag(OBJ_FLAG_UNKNOWN_9, bladeSet == setup->unknown6c);
  }
}

bool GfGameObj::fadeoutGameObj(INOUT &inout, GfObjAcc &acc, const fw::UpdateInfo &info) {
  inout.unknown0c += info.unknown04;
  f32 step = 0.0f;
  if (!inout.unknown16) {
    if (inout.unknown08 > 0.0f) {
      step = (-1.0f / inout.unknown08) * info.unknown04;
    }
    inout.unknown10 += step;
  }
  if (inout.unknown15) {
    if (inout.unknown10 < 1.0f && inout.unknown10 - step >= 1.0f) {
      inout.unknown15 = false;
      setupEffectFadeout(inout, acc, info);
    }
  }
  if (inout.unknown10 <= 0.0f || isEffectFadeEnd(inout, acc)) {
    inout.unknown10 = 0.0f;
    if (inout.unknown14) {
      inout.unknown14 = false;
      enableGameObj(acc, false);
    }
    acc.setFlag(OBJ_FLAG_UNKNOWN_17, false);
    if (!acc.testFlag(OBJ_FLAG_UNKNOWN_8) || acc.isRebuild()) {
      if (!acc.isDestroy()) {
        GfObjUtil::destroy(inout.unknown00);
      }
    } else {
      GfObjUtil::rebuild(inout.unknown00);
    }
    return true;
  }
  acc.setAlphaLife(inout.unknown10 > 1.0f ? 1.0f : inout.unknown10);
  return false;
}

bool GfGameObj::isInitialized() {
  GfGameObj *gameObj = get();
  if (gameObj != nullptr) {
    return gameObj->unknown55c70;
  }
  return false;
}

bool GfGameObj::isExistEnemy() { return get()->unknown9050.size() != 0; }

const mm::mtl::FixedList<GF_OBJ_HANDLE *, GAME_UNKNOWN_1024> *GfGameObj::getListEnemyBlade() { return &get()->unknownd870; }

bool GfGameObj::isGameObjWaiting(GF_OBJ_HANDLE *handle) { return GfObjUtil::testFlag(handle, OBJ_FLAG_UNKNOWN_16); }

bool GfGameObj::isDestroyGameObj(GF_OBJ_HANDLE *handle) {
  GfObjAcc acc(handle);
  if (!acc.isValid()) {
    return true;
  }
  return !acc.testFlag(OBJ_FLAG_UNKNOWN_14);
}

bool GfGameObj::isValidGameObj(GF_OBJ_HANDLE *handle, bool isCheckState, mm::mtl::FixStr<128> *reason) {
  GfGameObj *gameObj = get();
  GfObjAcc acc(handle);
  if (isCheckState) {
    for (mm::mtl::FixedList<INOUT, GAME_UNKNOWN_1024>::iterator it = gameObj->unknown3f1d0.begin(); it != gameObj->unknown3f1d0.end(); ++it) {
      if (it->unknown00 == handle) {
        return true;
      }
    }
  } else {
    for (mm::mtl::FixedList<INOUT, GAME_UNKNOWN_1024>::iterator it = gameObj->unknown3f1d0.begin(); it != gameObj->unknown3f1d0.end(); ++it) {
      if ((*it).unknown00 == handle) {
        if (reason != nullptr) {
          reason->format("GfGameObj::Fadein[%s]", acc.getDebugName());
        }
        return false;
      }
    }
  }
  bool isValid = acc.testFlag(OBJ_FLAG_UNKNOWN_14);
  if (reason == nullptr || isValid) {
    return isValid;
  }
  GfAssetManager *assetManager = GfAssetManager::get();
  if (assetManager != nullptr && !assetManager->isLoaded(acc.getAssetHandle(), nullptr)) {
    reason->format("Loading Asset[%s]", acc.getDebugName());
  } else if (!acc.isLoadedWaitOK()) {
    reason->format("isLoadedWaitOK[%s]", acc.getDebugName());
  } else if (!GfObjManager::get()->isValidMultiBind(acc.getHandle(), acc.getMultiBindUniqId())) {
    reason->format("isValidMultiBind[%s]", acc.getDebugName());
  } else if (isGameObjWaiting(handle)) {
    reason->format("GfObjFlags::GAMEOBJ[%s]", acc.getDebugName());
  } else {
    reason->format("GfGameObj::isGameObjWaiting[%s]", acc.getDebugName());
  }
  return false;
}

bool GfGameObj::isEnterGameObj(GF_OBJ_HANDLE *handle) {
  if (handle == reinterpret_cast<GF_OBJ_HANDLE *>(-1)) {
    return false;
  }
  GfGameObj *gameObj = get();
  for (mm::mtl::FixedList<INOUT, GAME_UNKNOWN_1024>::iterator it = gameObj->unknown3f1d0.begin(); it != gameObj->unknown3f1d0.end(); ++it) {
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
  for (mm::mtl::FixedList<INOUT, GAME_UNKNOWN_1024>::iterator it = gameObj->unknown3f1d0.begin(); it != gameObj->unknown3f1d0.end(); ++it) {
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
  for (mm::mtl::FixedList<INOUT, GAME_UNKNOWN_1024>::iterator it = gameObj->unknown3f1d0.begin(); it != gameObj->unknown3f1d0.end(); ++it) {
    if (it->unknown00 == handle) {
      return GfObjUtil::getObj(handle);
    }
  }
  if (acc.testFlag(OBJ_FLAG_UNKNOWN_14)) {
    return GfObjUtil::getObj(handle);
  }
  return nullptr;
}

bool GfGameObj::fadeinGameObj(INOUT &inout, GfObjAcc &acc, const fw::UpdateInfo &info) {
  if (inout.unknown15) {
    inout.unknown15 = false;
  }
  if (GfGameManager::isFadeout()) {
    inout.unknown10 = 1.0f;
  }
  if (0.0f < inout.unknown08) {
    inout.unknown10 += (1.0f / inout.unknown08) * info.unknown04;
    acc.setAlphaLife(inout.unknown10);
    if (!(inout.unknown10 >= 1.0f)) {
      return false;
    }
  } else {
    inout.unknown10 = 1.0f;
  }
  addGameObj(inout.unknown00);
  acc.setAlphaLife(1.0f);
  return true;
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

bool GfGameObj::isBattle(const mm::mtl::FixedList<GF_OBJ_HANDLE *, GAME_UNKNOWN_1024> &list) const {
  for (mm::mtl::FixedList<GF_OBJ_HANDLE *, GAME_UNKNOWN_1024>::const_iterator it = list.begin(); it != list.end(); ++it) {
    GfObjAcc acc(*it);
    if (acc.isBattle()) {
      return true;
    }
  }
  return false;
}

mm::mtl::FixedList<GF_OBJ_HANDLE *, GAME_UNKNOWN_1024> *GfGameObj::getListType(u32 objectType, GF_OBJ_HANDLE *handle) {
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

const mm::mtl::FixedList<GF_OBJ_HANDLE *, GAME_UNKNOWN_1024> *GfGameObj::getList(u32 objectType) { return get()->getListType(objectType, reinterpret_cast<GF_OBJ_HANDLE *>(-1)); }

void GfGameObj::getList(mm::mtl::FixedVector<GF_OBJ_HANDLE *, GAME_UNKNOWN_1024> &list, u32 objectType) {
  if (get() == nullptr) {
    return;
  }
  const mm::mtl::FixedList<GF_OBJ_HANDLE *, GAME_UNKNOWN_1024> *objects = getList(objectType);
  for (mm::mtl::FixedList<GF_OBJ_HANDLE *, GAME_UNKNOWN_1024>::const_iterator it = objects->begin(); it != objects->end(); ++it) {
    list.push_back(*it);
  }
}

void GfGameObj::getListEnemyBlade(mm::mtl::FixedVector<GF_OBJ_HANDLE *, GAME_UNKNOWN_1024> &list) {
  if (get() == nullptr) {
    return;
  }
  mm::mtl::FixedList<GF_OBJ_HANDLE *, GAME_UNKNOWN_1024> &enemyBlades = get()->unknownd870;
  for (mm::mtl::FixedList<GF_OBJ_HANDLE *, GAME_UNKNOWN_1024>::iterator it = enemyBlades.begin(); it != enemyBlades.end(); ++it) {
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
  for (mm::mtl::FixedList<GF_OBJ_HANDLE *, GAME_UNKNOWN_1024>::iterator it = unknown10.begin(); it != unknown10.end(); ++it) {
    GfGameUtil::flushProperty(*it);
  }
  for (mm::mtl::FixedList<GF_OBJ_HANDLE *, GAME_UNKNOWN_1024>::iterator it = unknown4830.begin(); it != unknown4830.end(); ++it) {
    GfGameUtil::flushProperty(*it);
  }
  mm::mtl::FixedList<GF_OBJ_HANDLE *, GAME_UNKNOWN_1024> &enemies = GfObjUtil::isEnemyBlade(reinterpret_cast<GF_OBJ_HANDLE *>(-1)) ? unknownd870 : unknown9050;
  for (mm::mtl::FixedList<GF_OBJ_HANDLE *, GAME_UNKNOWN_1024>::iterator it = enemies.begin(); it != enemies.end(); ++it) {
    GfGameUtil::flushProperty(*it);
  }
  for (mm::mtl::FixedList<GF_OBJ_HANDLE *, GAME_UNKNOWN_1024>::iterator it = unknown28930.begin(); it != unknown28930.end(); ++it) {
    GfGameUtil::flushProperty(*it);
  }
}

void GfGameObj::updateObjectProperty(u32 objectType) {
  mm::mtl::FixedList<GF_OBJ_HANDLE *, GAME_UNKNOWN_1024> *list = getListType(objectType, reinterpret_cast<GF_OBJ_HANDLE *>(-1));
  for (mm::mtl::FixedList<GF_OBJ_HANDLE *, GAME_UNKNOWN_1024>::iterator it = list->begin(); it != list->end(); ++it) {
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
    setup->unknown64 = VFACC_UNKNOWN_4;
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
  acc.setFlag(OBJ_FLAG_UNKNOWN_15, true);
  if (acc.getType() == OBJECT_TYPE_ENEMY) {
    acc.getObj()->setUpdateComponent(true);
  }
}

void GfGameObj::setupLeaveGameObj(GF_OBJ_HANDLE *handle, f32 fadeTime) {
  if (handle != unknown020) {
    GfGameObj *gameObj = get();
    GfObjAcc acc(handle);
    if (gameObj->addOutObj(handle, fadeTime, true)) {
      acc.setCollisionChar(false);
      if (acc.testFlag(OBJ_FLAG_UNKNOWN_8)) {
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
  mm::mtl::FixedList<GF_OBJ_HANDLE *, GAME_UNKNOWN_1024> *list = get()->getListType(objectType, unknown020);
  for (mm::mtl::FixedList<GF_OBJ_HANDLE *, GAME_UNKNOWN_1024>::iterator it = list->begin(); it != list->end(); ++it) {
    GfGameUtil::changeStopLayer(*it, isStop);
  }
}

void GfGameObj::changeStopLayerIgnoreEventObj(u32 layer, bool isIgnore) {
  mm::mtl::FixedList<GF_OBJ_HANDLE *, GAME_UNKNOWN_1024> *list = get()->getListType(layer, unknown020);
  for (mm::mtl::FixedList<GF_OBJ_HANDLE *, GAME_UNKNOWN_1024>::iterator it = list->begin(); it != list->end(); ++it) {
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
    ObjMsg destroyAttribute = {handle, attribute};
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
  mm::mtl::FixedList<GF_OBJ_HANDLE *, GAME_UNKNOWN_1024> &enemies = GfObjUtil::isEnemyBlade(unknown020) ? gameObj->unknownd870 : gameObj->unknown9050;
  for (mm::mtl::FixedList<GF_OBJ_HANDLE *, GAME_UNKNOWN_1024>::iterator it = enemies.begin(); it != enemies.end(); ++it) {
    DataParamAcc paramAcc(*it);
    u32 bdatId = 0;
    if (paramAcc.isValid()) {
      bdatId = paramAcc.getBdatId();
    }
    if (bdatId == arrange) {
      count++;
    }
  }
  for (mm::mtl::FixedList<INOUT, GAME_UNKNOWN_1024>::iterator it = unknown3f1d0.begin(); it != unknown3f1d0.end(); ++it) {
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
  for (mm::mtl::FixedList<INOUT, GAME_UNKNOWN_1024>::iterator it = unknown47a00.begin(); it != unknown47a00.end(); ++it) {
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

GfGameObjEnemy::GfGameObjEnemy() {}

GfGameObjEnemy::~GfGameObjEnemy() {}

bool GfGameObjEnemy::isGenusLink(GF_OBJ_HANDLE *handle) {
  GfGameObjEnemy *enemy = get();
  if (enemy != nullptr && !GfObjAcc(handle).isBattle()) {
    return mm::mtl::find(enemy->unknown1890.begin(), enemy->unknown1890.end(), handle) != enemy->unknown1890.end();
  }
  return false;
}

bool GfGameObjEnemy::empty() const { return unknown08.empty(); }

} // namespace gf

template mm::mtl::PtrSingleton<gf::GfGameObj>::~PtrSingleton();
template mm::mtl::FixedList<gf::GfGameObj::INOUT, 1024>::iterator mm::mtl::FixedList<gf::GfGameObj::INOUT, 1024>::erase(mm::mtl::FixedList<gf::GfGameObj::INOUT, 1024>::iterator);
template mm::mtl::PtrSingleton<gf::GfGameObjEnemy>::~PtrSingleton();
template mm::mtl::FixedList<gf::GfGameObjEnemy::GINFO, 64>::iterator mm::mtl::FixedList<gf::GfGameObjEnemy::GINFO, 64>::erase(mm::mtl::FixedList<gf::GfGameObjEnemy::GINFO, 64>::iterator);
template mm::mtl::FixedList<gf::ObjMsg, 256>::iterator mm::mtl::FixedList<gf::ObjMsg, 256>::erase(mm::mtl::FixedList<gf::ObjMsg, 256>::iterator it);
