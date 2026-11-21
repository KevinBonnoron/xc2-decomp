#include "gf/game/gf_game_obj.h"

#include "fw/fw_coli_check.h"
#include "fw/fw_transform.h"
#include "fw/fw_update_info.h"
#include "gf/asset/gf_asset_manager.h"
#include "gf/data/gf_bdat_rsc.h"
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
#include "gf/object/component/enemy/gf_com_behavior_enemy.h"
#include "gf/object/component/gf_com_transform.h"
#include "gf/object/component/property/gf_com_property.h"
#include "gf/object/gf_init_param.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_manager.h"
#include "gf/object/gf_obj_setup.h"
#include "gf/object/gf_obj_util.h"
#include "gf/request/gf_req_scom.h"
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

void GfGameObj::bdatReload() {
  GfGameObj *gameObj = get();
  if (gameObj == nullptr) {
    return;
  }
  // The first two loops repeat the statements of refreshBdatInOut (0x710032474c, 39 instructions), which the game inlines here although it keeps a standalone copy:
  // the call form compiles to 156 instructions (refreshBdatInOut stays a call), the game has 218 (no call to it). The last two loops call refreshBdat (0x71003247e8), which clang inlines.
  for (mm::mtl::FixedList<INOUT, GAME_UNKNOWN_1024>::iterator it = gameObj->unknown3f1d0.begin(); it != gameObj->unknown3f1d0.end(); ++it) {
    GfObjAcc acc((*it).unknown00);
    if (acc.getType() == OBJECT_TYPE_ENEMY) {
      refreshBdat((*it).unknown00);
    }
  }
  for (mm::mtl::FixedList<INOUT, GAME_UNKNOWN_1024>::iterator it = gameObj->unknown47a00.begin(); it != gameObj->unknown47a00.end(); ++it) {
    GfObjAcc acc((*it).unknown00);
    if (acc.getType() == OBJECT_TYPE_ENEMY) {
      refreshBdat((*it).unknown00);
    }
  }
  for (mm::mtl::FixedList<GF_OBJ_HANDLE *, GAME_UNKNOWN_1024>::iterator it = gameObj->unknown9050.begin(); it != gameObj->unknown9050.end(); ++it) {
    refreshBdat(*it);
  }
  for (mm::mtl::FixedList<GF_OBJ_HANDLE *, GAME_UNKNOWN_1024>::iterator it = gameObj->unknownd870.begin(); it != gameObj->unknownd870.end(); ++it) {
    refreshBdat(*it);
  }
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

void GfGameObj::setupEffectFadeout(INOUT &inout, GfObjAcc &acc, const fw::UpdateInfo &info) {
  if ((acc.getType() == OBJECT_TYPE_ENEMY || acc.getType() == OBJECT_TYPE_GIMMICK) && acc.getObj()->getComponent<GfComProperty>() != nullptr) {
    // The game calls getHandle at each use, the search's call after the setup of the iterators (0x7100322b88); a local used at every call gives 94 instructions, the lambda taking acc by
    // reference 95 (the game has 96).
    mm::mtl::FixedList<ObjMsg, 256>::iterator it =
        mm::mtl::find_if(unknown54240.begin(), unknown54240.end(), [handle = acc.getHandle()](const ObjMsg &message) { return message.unknown00 == handle; });
    if (it != unknown54240.end()) {
      if (0.0f < inout.unknown08) {
        inout.unknown10 = 1.0f;
      }
      inout.unknown08 = SCOM_OBJ_VFADE::createDead(acc.getHandle(), it->unknown08);
      inout.unknown16 = true;
      if (acc.getType() == OBJECT_TYPE_ENEMY) {
        SCOM_DEAD_PARTICLE::create(acc.getHandle(), it->unknown08, inout.unknown08);
      }
    }
  }
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

// The singleton is loaded before the dispatch, as the game does (0x7100320b1c).
void GfGameObj::listenerGfObj(OBJEVT event, GF_OBJ_HANDLE *handle, u32 objectType) {
  GfGameObj *gameObj = get();
  switch (event) {
  case OBJEVT_UNKNOWN_1:
    GfGameEvent::applySetDispObject(handle);
    break;
  case OBJEVT_UNKNOWN_2:
    gameObj->addInObj(handle, 0.5f);
    break;
  case OBJEVT_UNKNOWN_3:
    gameObj->removeGameObj(handle);
    break;
  default:
    break;
  }
}

// Inferred role: list holding the object (the event character list, or the list of its type); no game symbol, original name unknown. The game inlines this choice in removeGameObj (0x7100320cc8),
// addGameObj (0x7100321b20) and addOutObj (0x71003214ac) and holds no function for it. Measured: the three functions match both with this helper (inlined, no symbol emitted) and with the six lines
// written out in each, so the helper is the form.
static mm::mtl::FixedList<GF_OBJ_HANDLE *, GAME_UNKNOWN_1024> *unknown001(GfGameObj *gameObj, GF_OBJ_HANDLE *handle) {
  GfObjSetup *setup = GfObjUtil::getObjSetup(handle);
  if (setup != nullptr && isEventCharacter(setup->unknown1c)) {
    return &gameObj->unknown28930;
  }
  return gameObj->getListType(GfObjUtil::getObjType(handle), handle);
}

// 0x7100320cc8. The event test is isEventCharacter (values 6, 7, 12), not GfObjSetup::isEvent. Measured: the ObjMsg search is a find_if with a capturing lambda (a plain loop is jump-threaded, the
// game's is not) and the last search is mm::mtl::find with `list->end() != found` (`found != list->end()` does not match). The switch of getListType inlined here lays its case blocks out as the
// game does (0/0xe, default, 3, 6, 7, 8, 0xd, 4, 5, 9, 10, 0xb, 0xc) only with the cases 0 and 0xe written as two separate returns (see getListType).
void GfGameObj::removeGameObj(GF_OBJ_HANDLE *handle) {
  if (!GfObjUtil::testFlag(handle, OBJ_FLAG_UNKNOWN_15)) {
    return;
  }
  GfObjAcc acc(handle);
  removeGameObjCommon(acc);
  mm::mtl::FixedList<ObjMsg, 256>::iterator message = mm::mtl::find_if(unknown54240.begin(), unknown54240.end(), [handle](const ObjMsg &entry) { return entry.unknown00 == handle; });
  if (message != unknown54240.end()) {
    unknown54240.erase(message);
  }
  for (mm::mtl::FixedList<INOUT, GAME_UNKNOWN_1024>::iterator it = unknown47a00.begin(); it != unknown47a00.end(); ++it) {
    if (it->unknown00 == handle) {
      unknown47a00.erase(it);
      acc.setFlag(OBJ_FLAG_UNKNOWN_15, false);
      return;
    }
  }
  for (mm::mtl::FixedList<INOUT, GAME_UNKNOWN_1024>::iterator it = unknown3f1d0.begin(); it != unknown3f1d0.end(); ++it) {
    if (it->unknown00 == handle) {
      unknown3f1d0.erase(it);
      return;
    }
  }
  mm::mtl::FixedList<GF_OBJ_HANDLE *, GAME_UNKNOWN_1024> *list = unknown001(this, handle);
  mm::mtl::FixedList<GF_OBJ_HANDLE *, GAME_UNKNOWN_1024>::iterator found = mm::mtl::find(list->begin(), list->end(), handle);
  if (list->end() != found) {
    list->erase(found);
    flushEvent();
  }
}

// 0x7100321b20. The list choice is unknown001, as in removeGameObj. Returns true on every path (the game sets w0 to 1).
bool GfGameObj::addGameObj(GF_OBJ_HANDLE *handle) {
  mm::mtl::FixedList<GF_OBJ_HANDLE *, GAME_UNKNOWN_1024> *list = unknown001(this, handle);
  list->push_back(handle);
  GfGameUtil::setKosmosArts3EnableBothWeapon(handle, false);
  return true;
}

// 0x71003214ac. The list choice is unknown001, as in removeGameObj and addGameObj. Measured: the list search tested as `list->end() == found` with the out list search first (the not found arm leaves
// the function early) gives the game's block order; `list->end() != found` with the search last gives 347 instructions (the two `return false` blocks merge), `found == list->end()` another `cmp`
// operand order, and a find_if for the last search another order. The two manager reads are the game's (0x7100321730, 0x71003217c0).
bool GfGameObj::addOutObj(GF_OBJ_HANDLE *handle, f32 fadeTime, bool isEffect) {
  mm::mtl::FixedList<GF_OBJ_HANDLE *, GAME_UNKNOWN_1024> *list = unknown001(this, handle);
  mm::mtl::FixedList<GF_OBJ_HANDLE *, GAME_UNKNOWN_1024>::iterator found = mm::mtl::find(list->begin(), list->end(), handle);
  if (list->end() == found) {
    for (mm::mtl::FixedList<INOUT, GAME_UNKNOWN_1024>::iterator it = unknown47a00.begin(); it != unknown47a00.end(); ++it) {
      if ((*it).unknown00 == handle) {
        return true;
      }
    }
    return false;
  }
  list->erase(found);
  if (GfGameManager::isFadeout()) {
    fadeTime = 0.0f;
  }
  INOUT inout;
  inout.unknown00 = handle;
  inout.unknown08 = fadeTime < 0.000001f ? 0.0f : fadeTime;
  inout.unknown0c = 0.0f;
  inout.unknown10 = fadeTime == 0.0f ? 0.0f : 1.0f;
  inout.unknown14 = true;
  inout.unknown15 = true;
  inout.unknown16 = false;
  unknown47a00.push_back(inout);
  GfObjAcc acc(handle);
  if (acc.testFlag(OBJ_FLAG_UNKNOWN_14)) {
    acc.setFlag(OBJ_FLAG_UNKNOWN_14, false);
  }
  if (!acc.testFlag(OBJ_FLAG_UNKNOWN_17)) {
    acc.setFlag(OBJ_FLAG_UNKNOWN_17, true);
  }
  if (isEffect) {
    GfObjManager *manager = GfObjManager::get();
    if (manager != nullptr) {
      mm::mtl::FixedList<GF_OBJ_HANDLE *, 32> *multiBind = manager->getMultiBindList(handle);
      if (multiBind != nullptr) {
        for (mm::mtl::FixedList<GF_OBJ_HANDLE *, 32>::iterator it = multiBind->begin(); it != multiBind->end(); ++it) {
          if (*it != handle) {
            // The game calls the GfObjAcc constructor (0x7100321798) for each bound object and never reads the accessor.
            GfObjAcc bound(*it);
            addOutObj(*it, fadeTime, false);
          }
        }
      }
    }
  }
  GfObjManager *manager = GfObjManager::get();
  if (manager != nullptr) {
    mm::mtl::FixedList<GF_OBJ_HANDLE *, 768> followObjs;
    if (manager->getFollowObj(followObjs, handle)) {
      for (mm::mtl::FixedList<GF_OBJ_HANDLE *, 768>::iterator it = followObjs.begin(); it != followObjs.end(); ++it) {
        addOutObj(*it, fadeTime, false);
      }
    }
  }
  return true;
}

// 0x7100324860. The list type switch inlined here has no event character test (unlike addGameObj and addOutObj). Measured: the follow object loop dereferences its iterator twice, as the game does
// (an assert each time): the search lambda captures `*it` by value and the new message reads `*it` again; a named local gives 376 instructions. The end comparisons are `found == list->end()` for
// the list search and `end() == existing` for the message search (the other operand orders give another `cmp`). The loops over followObjs that set the collision off construct the accessor from
// `handle` (the game never reads the node: the constructor call at 0x7100324928 takes x19, the handle).
void GfGameObj::addCharDeadMessage(GF_OBJ_HANDLE *handle, const MsgObjectNotifyDead &message) {
  mm::mtl::FixedList<GF_OBJ_HANDLE *, 768> followObjs;
  GfObjManager *manager = GfObjManager::get();
  if (manager != nullptr) {
    manager->getFollowObj(followObjs, handle);
  }
  GfObjAcc acc(handle);
  if (acc.getType() == OBJECT_TYPE_ENEMY) {
    acc.setCollisionChar(false);
    for (mm::mtl::FixedList<GF_OBJ_HANDLE *, 768>::iterator it = followObjs.begin(); it != followObjs.end(); ++it) {
      GfObjAcc follow(handle);
      follow.setCollisionChar(false);
    }
  }
  if (!message.unknown28 || message.unknown20 == 0) {
    return;
  }
  GfGameObj *gameObj = get();
  mm::mtl::FixedList<INOUT, GAME_UNKNOWN_1024>::iterator entering =
      mm::mtl::find_if(gameObj->unknown3f1d0.begin(), gameObj->unknown3f1d0.end(), [handle](const INOUT &entry) { return entry.unknown00 == handle; });
  if (entering == gameObj->unknown3f1d0.end()) {
    mm::mtl::FixedList<INOUT, GAME_UNKNOWN_1024>::iterator leaving =
        mm::mtl::find_if(gameObj->unknown47a00.begin(), gameObj->unknown47a00.end(), [handle](const INOUT &entry) { return entry.unknown00 == handle; });
    if (leaving == gameObj->unknown47a00.end()) {
      mm::mtl::FixedList<GF_OBJ_HANDLE *, GAME_UNKNOWN_1024> *list = gameObj->getListType(GfObjUtil::getObjType(handle), handle);
      mm::mtl::FixedList<GF_OBJ_HANDLE *, GAME_UNKNOWN_1024>::iterator found = mm::mtl::find(list->begin(), list->end(), handle);
      if (found == list->end()) {
        return;
      }
    }
  }
  u32 attribute = message.unknown20;
  ObjMsg objMessage;
  objMessage.unknown00 = handle;
  objMessage.unknown08 = attribute;
  gameObj->unknown54240.push_back(objMessage);
  for (mm::mtl::FixedList<GF_OBJ_HANDLE *, 768>::iterator it = followObjs.begin(); it != followObjs.end(); ++it) {
    mm::mtl::FixedList<ObjMsg, 256>::iterator existing =
        mm::mtl::find_if(gameObj->unknown54240.begin(), gameObj->unknown54240.end(), [followObj = *it](const ObjMsg &entry) { return entry.unknown00 == followObj; });
    if (gameObj->unknown54240.end() == existing) {
      ObjMsg followMessage;
      followMessage.unknown00 = *it;
      followMessage.unknown08 = attribute;
      gameObj->unknown54240.push_back(followMessage);
    }
  }
}

// Cases 0 and 0xe are two separate returns, in value order (0xe after 0xd). Measured: with `case 0: case 0xe:` grouped, this function matches the same, but the switch inlined into removeGameObj lays
// its case blocks out in another order than the game's and its jump table (0x7100f6a4f4) differs. The two cases still share one block; the order of the case blocks that tie in frequency follows
// the rounding of the jump table successors' frequencies, which the separate case labels change (read in clang 3.9's block placement).
mm::mtl::FixedList<GF_OBJ_HANDLE *, GAME_UNKNOWN_1024> *GfGameObj::getListType(u32 objectType, GF_OBJ_HANDLE *handle) {
  switch (objectType) {
  case 0:
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
  case 0xe:
    return &unknown28930;
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
    refreshBdat(inout.unknown00);
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

// Inferred role: whether the enemy behavior of the object has its unknown54e4 flag set; no game symbol, original name unknown. The game holds this test twice in calcGenusLink (0x7100325b4c for the
// first object, 0x7100325b8c for the second) and has no function for it. Measured: calcGenusLink matches both with this helper (inlined, no symbol emitted) and with the two blocks written out, so the
// helper is the form.
static bool unknown002(GF_OBJ_HANDLE *handle) {
  GfObj *obj = GfObjUtil::getObj(handle);
  if (obj != nullptr) {
    GfComBehaviorEnemy *behavior = obj->getComponent<GfComBehaviorEnemy>();
    if (behavior != nullptr && behavior->unknown54e4) {
      return true;
    }
  }
  return false;
}

// Game: 0x7100325ad0. The ColiCheckConfig stores repeat the seven of gf::util::getHitCollision, getUnderHitCollision and getUpperHitCollision (ruling 8): the game calls fw::ColiCheck::testLine
// directly with this block (0x7100325d48) and never calls those functions, which also read the first hit position.
void GfGameObjEnemy::calcGenusLink(Pair &pair) {
  bool wasLinked = pair.unknown10;
  pair.unknown10 = false;
  GfObjAcc first(pair.unknown00);
  GfObjAcc second(pair.unknown08);
  if (first.isValid() && second.isValid()) {
    if (first.isBattle() != second.isBattle()) {
      if (unknown002(pair.unknown00) || unknown002(pair.unknown08)) {
        return;
      }
      DataParamAcc firstParam(pair.unknown00);
      DataParamAcc secondParam(pair.unknown08);
      if (firstParam.getHp() != 0 && secondParam.getHp() != 0) {
        f32 radius = firstParam.getLinkRadius();
        if (!(radius * radius <= 0.000001f)) {
          mm::Vec3 delta = second.getWorldTransform().unknown00 - first.getWorldTransform().unknown00;
          if (delta.x * delta.x + delta.y * delta.y + delta.z * delta.z < radius * radius) {
            GfBdatRsc *bdatRsc = GfBdatRsc::get();
            if (pair.unknown12 == -1) {
              pair.unknown12 = first.getBoneIdx(bdatRsc->getRscEnSearchBaseBone(first.getEnRscId()));
            }
            if (pair.unknown14 == -1) {
              pair.unknown14 = second.getBoneIdx(bdatRsc->getRscEnSearchBaseBone(second.getEnRscId()));
            }
            fw::Transform firstBone;
            fw::Transform secondBone;
            if (first.getBoneTransform(firstBone, pair.unknown12) && second.getBoneTransform(secondBone, pair.unknown14)) {
              fw::TColiCheckResult<256> result;
              fw::ColiCheckConfig config;
              config.unknown04 = 0xffffffff;
              config.unknown10 = 1;
              config.unknown08 = 0.0f;
              config.unknown0c = 0.0f;
              config.unknown14 = false;
              config.unknown15 = false;
              config.unknown00 = 9;
              pair.unknown10 = !fw::ColiCheck::testLine(result, firstBone.unknown00, secondBone.unknown00, config);
            }
          }
          if (!wasLinked && pair.unknown10) {
            GF_OBJ_HANDLE *handle = first.isBattle() ? pair.unknown08 : pair.unknown00;
            mm::mtl::FixedList<GF_OBJ_HANDLE *, 256>::iterator found = mm::mtl::find(unknown1890.begin(), unknown1890.end(), handle);
            // The game compares the end iterator on the left of the test (0x7100325e00: cmp x23, x8), as removeGameObj and addOutObj do; the other order gives cmp x8, x23.
            if (unknown1890.end() == found) {
              unknown1890.push_back(handle);
            }
          }
        }
      }
    }
  }
}

bool GfGameObjEnemy::empty() const { return unknown08.empty(); }

} // namespace gf

template mm::mtl::PtrSingleton<gf::GfGameObj>::~PtrSingleton();
template mm::mtl::FixedList<gf::GfGameObj::INOUT, 1024>::iterator mm::mtl::FixedList<gf::GfGameObj::INOUT, 1024>::erase(mm::mtl::FixedList<gf::GfGameObj::INOUT, 1024>::iterator);
template mm::mtl::PtrSingleton<gf::GfGameObjEnemy>::~PtrSingleton();
template mm::mtl::FixedList<gf::GfGameObjEnemy::GINFO, 64>::iterator mm::mtl::FixedList<gf::GfGameObjEnemy::GINFO, 64>::erase(mm::mtl::FixedList<gf::GfGameObjEnemy::GINFO, 64>::iterator);
template mm::mtl::FixedList<gf::ObjMsg, 256>::iterator mm::mtl::FixedList<gf::ObjMsg, 256>::erase(mm::mtl::FixedList<gf::ObjMsg, 256>::iterator it);
