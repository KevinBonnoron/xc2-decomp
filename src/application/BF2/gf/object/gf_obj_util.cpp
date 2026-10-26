#include "gf/object/gf_obj_util.h"

#include "framework/object/component_object.h"
#include "framework/object/updatable_object.h"
#include "framework/pointer_map.h"
#include "gf/asset/gf_asset_manager.h"
#include "gf/data/gf_bdat_rsc.h"
#include "gf/data/gf_data_npc.h"
#include "gf/data/gf_data_param_acc.h"
#include "gf/data/gf_object_type.h"
#include "gf/game/gf_game_mount.h"
#include "gf/game/gf_game_party.h"
#include "gf/object/component/gf_component.h"
#include "gf/object/component/model/gf_com_model.h"
#include "gf/object/component/property/gf_com_property.h"
#include "gf/object/gf_init_param.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_property.h"
#include "mm_mtl/bitflag.h"
#include "mm_mtl/fixed_vector.h"

namespace gf {

void GfObjUtil::addDebugName(GF_OBJ_HANDLE *handle) {}

void GfObjUtil::addGfObj(GF_OBJ_HANDLE *handle, GfObj *obj) {
  GFOBJ_INFO *info = GfObjManager::getObjInfo(handle);
  if (info != nullptr) {
    info->unknown18 = obj;
  }
}

void GfObjUtil::removeGfObj(GF_OBJ_HANDLE *handle) {
  GFOBJ_INFO *info = GfObjManager::getObjInfo(handle);
  if (info != nullptr) {
    info->unknown18 = nullptr;
  }
}

u32 GfObjUtil::getObjType(GF_OBJ_HANDLE *handle) {
  GfObj *obj = getObj(handle);
  return obj != nullptr ? obj->unknown28 : 0;
}

GfObj *GfObjUtil::getObj(GF_OBJ_HANDLE *handle) {
  if (handle == INVALID_HANDLE) {
    return nullptr;
  }

  GFOBJ_INFO *info = GfObjManager::getObjInfo(handle);
  return info != nullptr ? info->unknown18 : nullptr;
}

u32 GfObjUtil::getObjLayer(GF_OBJ_HANDLE *handle) {
  GfObj *obj = getObj(handle);
  return obj != nullptr ? obj->unknown2c : 4;
}

f32 GfObjUtil::getSetupScale(GF_OBJ_HANDLE *handle) {
  GFOBJ_INFO *info = GfObjManager::getObjInfo(handle);
  return info != nullptr && info->unknown30 != nullptr ? info->unknown30->unknown40 : 1.0f;
}

GfObjSetup *GfObjUtil::getObjSetup(GF_OBJ_HANDLE *handle) {
  GFOBJ_INFO *info = GfObjManager::getObjInfo(handle);
  return info != nullptr ? info->unknown30 : nullptr;
}

GF_ASSET_HANDLE *GfObjUtil::getAssetHandle(GF_OBJ_HANDLE *handle) {
  GFOBJ_INFO *info = GfObjManager::getObjInfo(handle);
  return info != nullptr ? info->unknown10 : reinterpret_cast<GF_ASSET_HANDLE *>(-1);
}

void GfObjUtil::applyExecUpdate(GfObj *obj) { obj->unknown118 = isUpdateComponent(obj) && !isFollowObjNotReady(obj->unknownf8); }

GF_OBJ_HANDLE *GfObjUtil::getParentHandle(GF_OBJ_HANDLE *handle) {
  GfObj *obj = getObj(handle);
  if (obj != nullptr) {
    fw::UpdatableObject *parent = obj->unknownd0.get();
    if (parent != nullptr) {
      GfObj *parentObj = mm::mtl::dynamicCast<GfObj>(parent);
      if (parentObj != nullptr) {
        return parentObj->unknownf8;
      }
    }
  }

  return INVALID_HANDLE;
}

GfObj *GfObjUtil::getParentObj(GfObj *obj) {
  fw::UpdatableObject *parent = obj->unknownd0.get();
  if (parent == nullptr) {
    return nullptr;
  }

  return mm::mtl::dynamicCast<GfObj>(parent);
}

u32 GfObjUtil::getLayerSection(u32 layer) {
  switch (layer) {
  case 0:
    return 0;
  case 1:
  case 2:
  case 3:
    return 1;
  case 4:
  case 5:
  case 6:
    return 4;
  case 7:
  case 8:
  case 9:
    return 7;
  case 10:
  case 11:
  case 12:
    return 10;
  default:
    return 4;
  }
}

void GfObjUtil::changeLayer(GfObj *obj, u32 layer) {
  u32 oldLayer = obj->unknown2c;
  for (u32 i = 0; i < fw::UpdatableObject::COMPONENT_MAX; i++) {
    fw::ComponentObject *component = obj->unknown38[i];
    if (component != nullptr) {
      GfComponent *gfComponent = mm::mtl::dynamicCast<GfComponent>(component);
      if (gfComponent != nullptr) {
        gfComponent->changeLayer(oldLayer, layer);
      }
    }
  }

  obj->unknown2c = layer;
}

void GfObjUtil::changeLayer(GF_OBJ_HANDLE *handle, u32 layer) {
  GfObj *obj = getObj(handle);
  if (obj != nullptr) {
    changeLayer(obj, layer);
  }
}

const char *GfObjUtil::getResourceName(GF_OBJ_HANDLE *handle) {
  DataParamAcc paramAcc(handle);
  return paramAcc.getModelResourceName();
}

const char *GfObjUtil::getModelResourceName(GF_OBJ_HANDLE *handle) {
  DataParamAcc paramAcc(handle);
  return paramAcc.getModelResourceName();
}

const char *GfObjUtil::getMotionResourceName(GF_OBJ_HANDLE *handle) {
  DataParamAcc paramAcc(handle);
  return paramAcc.getMotionResourceName();
}

const char *GfObjUtil::getAddResourceName(GF_OBJ_HANDLE *handle) {
  switch (getObjType(handle)) {
  case OBJECT_TYPE_ENEMY: {
    DataParamAcc paramAcc(handle);
    return GfBdatRsc::get()->getRscEnRefMotion(paramAcc.getBdatIdEnRsc());
  }
  case OBJECT_TYPE_NPC: {
    DataParamAcc paramAcc(handle);
    return GfDataNpc::getAddMotionName(paramAcc.isValid() ? paramAcc.getBdatId() : 0);
  }
  }

  return nullptr;
}

GF_MOUNT_HANDLE *GfObjUtil::getMountHandle(GF_OBJ_HANDLE *handle, GFATTACH attach) {
  GFOBJ_INFO *info = GfObjManager::getObjInfo(handle);
  return info != nullptr ? info->unknownb8[attach].unknown00 : reinterpret_cast<GF_MOUNT_HANDLE *>(-1);
}

u32 GfObjUtil::getGameObjectID(GF_OBJ_HANDLE *handle) {
  GFOBJ_INFO *info = GfObjManager::getObjInfo(handle);
  if (info != nullptr && info->unknown30 != nullptr) {
    GfObjSetup *setup = info->unknown30;
    if (getObjType(handle) != OBJECT_TYPE_ENEMY) {
      return setup->unknown10;
    }

    GfObjSetupEnemy *setupEnemy = mm::mtl::dynamicCast<GfObjSetupEnemy>(setup);
    if (setupEnemy != nullptr) {
      return setupEnemy->m_enArrangeID;
    }
  }

  return 0xffffffff;
}

void GfObjUtil::setLimitHP(GF_OBJ_HANDLE *handle, u32 limitHp) {
  GfObj *obj = getObj(handle);
  if (obj != nullptr) {
    MsgObjectLimitHP message(limitHp);
    obj->sendMessage(obj, message);
  }
}

u32 GfObjUtil::getLimitHP(GF_OBJ_HANDLE *handle) {
  GfObj *obj = getObj(handle);
  if (obj != nullptr) {
    GfComProperty *property = obj->getComponent<GfComProperty>();
    if (property != nullptr && property->unknown10 != nullptr) {
      return property->unknown10->unknown14;
    }
  }

  return 0;
}

void GfObjUtil::setInvincible(GF_OBJ_HANDLE *handle, bool invincible, bool invincibleSub) {
  GfObj *obj = getObj(handle);
  if (obj != nullptr) {
    MsgObjectInvincible message(invincible, invincibleSub);
    obj->sendMessage(obj, message);
  }
}

bool GfObjUtil::testInvincible(GF_OBJ_HANDLE *handle) {
  bool isFound = false;
  bool invincible;
  GfObj *obj = getObj(handle);
  if (obj != nullptr) {
    GfComProperty *property = obj->getComponent<GfComProperty>();
    if (property != nullptr && property->unknown10 != nullptr) {
      invincible = property->unknown10->unknown18;
      isFound = true;
    }
  }

  return invincible & isFound;
}

void GfObjUtil::setInvincibleForDebug(GF_OBJ_HANDLE *handle, bool invincible) {
  GfObj *obj = getObj(handle);
  if (obj != nullptr) {
    GfComProperty *property = obj->getComponent<GfComProperty>();
    if (property != nullptr && property->unknown30 != nullptr) {
      property->unknown30->invincible = invincible;
    }
  }
}

bool GfObjUtil::testInvincibleForDebug(GF_OBJ_HANDLE *handle) {
  bool isFound = false;
  bool invincible;
  GfObj *obj = getObj(handle);
  if (obj != nullptr) {
    GfComProperty *property = obj->getComponent<GfComProperty>();
    if (property != nullptr && property->unknown30 != nullptr) {
      invincible = property->unknown30->invincible;
      isFound = true;
    }
  }

  return invincible & isFound;
}

void GfObjUtil::setDisableFallDeadForDebug(GF_OBJ_HANDLE *handle, bool disableFallDead) {
  GfObj *obj = getObj(handle);
  if (obj != nullptr) {
    GfComProperty *property = obj->getComponent<GfComProperty>();
    if (property != nullptr && property->unknown30 != nullptr) {
      property->unknown30->disableFallDead = disableFallDead;
    }
  }
}

bool GfObjUtil::testDisableFallDeadForDebug(GF_OBJ_HANDLE *handle) {
  bool isFound = false;
  bool disableFallDead;
  GfObj *obj = getObj(handle);
  if (obj != nullptr) {
    GfComProperty *property = obj->getComponent<GfComProperty>();
    if (property != nullptr && property->unknown30 != nullptr) {
      disableFallDead = property->unknown30->disableFallDead;
      isFound = true;
    }
  }

  return disableFallDead & isFound;
}

void GfObjUtil::setDisableAutoHeal(GF_OBJ_HANDLE *handle, bool disableAutoHeal) {
  GfObj *obj = getObj(handle);
  if (obj != nullptr) {
    MsgObjectStopAutoHeal message(disableAutoHeal);
    obj->sendMessage(obj, message);
  }
}

bool GfObjUtil::testDisableAutoHeal(GF_OBJ_HANDLE *handle) {
  bool isFound = false;
  bool disableAutoHeal;
  GfObj *obj = getObj(handle);
  if (obj != nullptr) {
    GfComProperty *property = obj->getComponent<GfComProperty>();
    if (property != nullptr && property->unknown10 != nullptr) {
      disableAutoHeal = property->unknown10->unknown1a;
      isFound = true;
    }
  }

  return disableAutoHeal & isFound;
}

GfObjProperty *GfObjUtil::getProperty(GF_OBJ_HANDLE *handle) {
  GFOBJ_INFO *info = GfObjManager::getObjInfo(handle);
  return info != nullptr ? info->unknown98 : nullptr;
}

u32 GfObjUtil::getHp(GF_OBJ_HANDLE *handle) {
  GfObj *obj = getObj(handle);
  if (obj != nullptr) {
    GfComProperty *property = obj->getComponent<GfComProperty>();
    if (property != nullptr && property->unknown10 != nullptr) {
      return property->unknown10->unknown10;
    }
  }

  return 0;
}

int GfObjUtil::getPartyID(GF_OBJ_HANDLE *handle) {
  GFOBJ_INFO *info = GfObjManager::getObjInfo(handle);
  if (info == nullptr || info->unknown30 == nullptr) {
    return -1;
  }

  return info->unknown30->unknown14;
}

GfWeapon *GfObjUtil::getWeaponMountObject(GF_OBJ_HANDLE *handle) { return GfMountManager::getAppendHandles(handle, GFATTACH_WEAPON); }

GfWeapon *GfObjUtil::getExtraMountObject(GF_OBJ_HANDLE *handle) { return GfMountManager::getAppendHandles(handle, GFATTACH_APPEND); }

bool GfObjUtil::isValid(GF_OBJ_HANDLE *handle) { return getObj(handle) != nullptr; }

bool GfObjUtil::isLoading(GF_OBJ_HANDLE *handle) {
  GFOBJ_INFO *info = GfObjManager::getObjInfo(handle);
  return info != nullptr && info->unknown06 == GFOBJ_STATE_LOADING;
}

bool GfObjUtil::isUpdate(GF_OBJ_HANDLE *handle) {
  GFOBJ_INFO *info = GfObjManager::getObjInfo(handle);
  return info != nullptr && info->unknown06 == GFOBJ_STATE_UPDATE;
}

void GfObjUtil::setOwner(GF_OBJ_HANDLE *handle, GF_OBJ_HANDLE *owner) {
  GFOBJ_INFO *info = GfObjManager::getObjInfo(handle);
  if (info != nullptr) {
    info->unknown90 = owner;
  }
}

GF_OBJ_HANDLE *GfObjUtil::getOwner(GF_OBJ_HANDLE *handle) {
  GFOBJ_INFO *info = GfObjManager::getObjInfo(handle);
  return info != nullptr ? info->unknown90 : INVALID_HANDLE;
}

void GfObjUtil::reload(GF_OBJ_HANDLE *handle) {}

bool GfObjUtil::isEnemyBlade(GF_OBJ_HANDLE *handle) {
  GfObjAcc objAcc(handle);
  if (objAcc.getType() != OBJECT_TYPE_ENEMY) {
    return false;
  }

  GfObjSetup *setup = getObjSetup(handle);
  return setup != nullptr && setup->unknown1c == CHARACTER_TYPE_ENEMY_BLADE;
}

bool GfObjUtil::testFlag(GF_OBJ_HANDLE *handle, u32 flag) {
  GFOBJ_INFO *info = GfObjManager::getObjInfo(handle);
  return info != nullptr && info->unknown38.test(flag);
}

bool GfObjUtil::testFlag(const GfObj *obj, u32 flag) { return obj->unknown100 != nullptr && obj->unknown100->unknown38.test(flag); }

const char *GfObjUtil::getModelBaseName(GF_OBJ_HANDLE *handle) {
  GFOBJ_INFO *info = GfObjManager::getObjInfo(handle);
  return info == nullptr ? "" : info->unknown404;
}

const char *GfObjUtil::getAssetModelName(GF_OBJ_HANDLE *handle) { return GfAssetManager::getModelInfo(getAssetHandle(handle)); }

const char *GfObjUtil::getAssetMotionName(GF_OBJ_HANDLE *handle) { return GfAssetManager::getMotionInfo(getAssetHandle(handle)); }

u32 GfObjUtil::getEyeRotControl(GF_OBJ_HANDLE *handle) {
  DataParamAcc paramAcc(handle);
  return paramAcc.getEyeRotControl();
}

GfComModel *GfObjUtil::getComModel(GF_OBJ_HANDLE *handle) {
  GfObj *obj = getObj(handle);
  return obj != nullptr ? obj->getComponent<GfComModel>() : nullptr;
}

GfVolumeFade *GfObjUtil::getVolumeFade(GF_OBJ_HANDLE *handle) {
  GFOBJ_INFO *info = GfObjManager::getObjInfo(handle);
  return info != nullptr ? info->unknown3d8 : nullptr;
}

bool GfObjUtil::isBattle(GF_OBJ_HANDLE *handle) {
  GFOBJ_INFO *info = GfObjManager::getObjInfo(handle);
  bool isFound = false;
  bool isBattle;
  if (info != nullptr && info->unknown98 != nullptr && info->unknown98->unknown10 != nullptr) {
    isBattle = info->unknown98->unknown10->unknown30;
    isFound = true;
  }

  return isFound & isBattle;
}

bool GfObjUtil::isVolumeFadeForUser(GF_OBJ_HANDLE *handle) {
  GFOBJ_INFO *info = GfObjManager::getObjInfo(handle);
  return info != nullptr && info->unknown38.test(OBJ_FLAG_VOLUME_FADE_FOR_USER);
}

void GfObjUtil::setVolumeFadeUserFlag(GF_OBJ_HANDLE *handle, bool isForUser) {
  GFOBJ_INFO *info = GfObjManager::getObjInfo(handle);
  if (info != nullptr && info->unknown38.test(OBJ_FLAG_VOLUME_FADE_FOR_USER) != isForUser) {
    info->unknown38.set(OBJ_FLAG_VOLUME_FADE_FOR_USER, isForUser);
  }
}

void GfObjUtil::setTalking(GF_OBJ_HANDLE *handle, bool isTalking) {
  GFOBJ_INFO *info = GfObjManager::getObjInfo(handle);
  if (info != nullptr) {
    info->unknown38.set(OBJ_FLAG_TALKING, isTalking);
  }
}

bool GfObjUtil::isTalking(GF_OBJ_HANDLE *handle) {
  GFOBJ_INFO *info = GfObjManager::getObjInfo(handle);
  return info != nullptr && info->unknown38.test(OBJ_FLAG_TALKING);
}

bool GfObjUtil::isSearchEmptyResource(GF_OBJ_HANDLE *handle) {
  GF_ASSET_HANDLE *assetHandle = getAssetHandle(handle);
  if (GfAssetManager::get() != nullptr) {
    return GfAssetManager::get()->isFullResource(assetHandle);
  }

  return false;
}

bool GfObjUtil::getMobSlotHandle(mm::mtl::FixedVector<GF_SLOT_HANDLE *, 88> &slots, GF_OBJ_HANDLE *handle) {
  slots.clear();
  if (getObjType(handle) == OBJECT_TYPE_MOB) {
    GfAssetManager::getSlotHandle(slots, getAssetHandle(handle));
  }

  return !slots.empty();
}

bool GfObjUtil::isTrinityBlade(GF_OBJ_HANDLE *handle) {
  GfObjSetup *setup = getObjSetup(handle);
  return setup != nullptr && setup->unknown1c == CHARACTER_TYPE_TRINITY_BLADE;
}

bool GfObjUtil::isUpdateComponent(const GfObj *obj) {
  const GFOBJ_INFO *info = obj->unknown100;
  if (!obj->unknown114.test(OBJ_STATE_UPDATE_ENABLE) || (info != nullptr && info->unknown38.test(OBJ_FLAG_DESTROY)) || (GfObjManager::get() != nullptr && GfObjManager::get()->isSuspendUpdate()) ||
      (info != nullptr && info->unknown38.test(OBJ_FLAG_PARTY_OBJ) && !GfGameParty::isPartyMemberInGameObj())) {
    return false;
  }

  return true;
}

void GfObjUtil::applyExecUpdate(GF_OBJ_HANDLE *handle) { applyExecUpdate(getObj(handle)); }

} // namespace gf
