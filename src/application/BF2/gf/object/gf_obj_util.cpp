#include "gf/object/gf_obj_util.h"
#include "gf/data/gf_bdat_rsc.h"
#include "gf/data/gf_data_npc.h"
#include "gf/data/gf_data_param_acc.h"
#include "gf/data/gf_object_type.h"

namespace gf {

static GF_OBJ_HANDLE *const INVALID_HANDLE = reinterpret_cast<GF_OBJ_HANDLE *>(-1);

class GfAssetManager {
public:
  static const char *getModelInfo(GF_ASSET_HANDLE *handle);
  static const char *getMotionInfo(GF_ASSET_HANDLE *handle);
};

void GfObjUtil::addDebugName(GF_OBJ_HANDLE *handle) {}

void GfObjUtil::addGfObj(GF_OBJ_HANDLE *handle, GfObj *obj) {
  GFOBJ_INFO *info = GfObjManager::getObjInfo(handle);
  if (info != nullptr) {
    info->obj = obj;
  }
}

void GfObjUtil::removeGfObj(GF_OBJ_HANDLE *handle) {
  GFOBJ_INFO *info = GfObjManager::getObjInfo(handle);
  if (info != nullptr) {
    info->obj = nullptr;
  }
}

u32 GfObjUtil::getObjType(GF_OBJ_HANDLE *handle) {
  GfObj *obj = getObj(handle);
  return obj != nullptr ? obj->objType : 0;
}

GfObj *GfObjUtil::getObj(GF_OBJ_HANDLE *handle) {
  if (handle == INVALID_HANDLE) {
    return nullptr;
  }

  GFOBJ_INFO *info = GfObjManager::getObjInfo(handle);
  return info != nullptr ? info->obj : nullptr;
}

u32 GfObjUtil::getObjLayer(GF_OBJ_HANDLE *handle) {
  GfObj *obj = getObj(handle);
  return obj != nullptr ? obj->layer : 4;
}

f32 GfObjUtil::getSetupScale(GF_OBJ_HANDLE *handle) {
  GFOBJ_INFO *info = GfObjManager::getObjInfo(handle);
  return info != nullptr && info->setup != nullptr ? info->setup->scale : 1.0f;
}

GfObjSetup *GfObjUtil::getObjSetup(GF_OBJ_HANDLE *handle) {
  GFOBJ_INFO *info = GfObjManager::getObjInfo(handle);
  return info != nullptr ? info->setup : nullptr;
}

GF_ASSET_HANDLE *GfObjUtil::getAssetHandle(GF_OBJ_HANDLE *handle) {
  GFOBJ_INFO *info = GfObjManager::getObjInfo(handle);
  return info != nullptr ? info->assetHandle : reinterpret_cast<GF_ASSET_HANDLE *>(-1);
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
  return info != nullptr ? info->mounts[attach].handle : reinterpret_cast<GF_MOUNT_HANDLE *>(-1);
}

u32 GfObjUtil::getGameObjectID(GF_OBJ_HANDLE *handle) {
  GFOBJ_INFO *info = GfObjManager::getObjInfo(handle);
  if (info != nullptr && info->setup != nullptr) {
    GfObjSetup *setup = info->setup;
    if (getObjType(handle) != OBJECT_TYPE_ENEMY) {
      return setup->id;
    }

    GfObjSetupEnemy *setupEnemy = mm::mtl::dynamicCast<GfObjSetupEnemy>(setup);
    if (setupEnemy != nullptr) {
      return setupEnemy->enArrangeId;
    }
  }

  return 0xffffffff;
}

GfObjProperty *GfObjUtil::getProperty(GF_OBJ_HANDLE *handle) {
  GFOBJ_INFO *info = GfObjManager::getObjInfo(handle);
  return info != nullptr ? info->property : nullptr;
}

int GfObjUtil::getPartyID(GF_OBJ_HANDLE *handle) {
  GFOBJ_INFO *info = GfObjManager::getObjInfo(handle);
  if (info == nullptr || info->setup == nullptr) {
    return -1;
  }

  return info->setup->partyMember;
}

bool GfObjUtil::isValid(GF_OBJ_HANDLE *handle) { return getObj(handle) != nullptr; }

bool GfObjUtil::isLoading(GF_OBJ_HANDLE *handle) {
  GFOBJ_INFO *info = GfObjManager::getObjInfo(handle);
  return info != nullptr && info->state == GFOBJ_STATE_LOADING;
}

bool GfObjUtil::isUpdate(GF_OBJ_HANDLE *handle) {
  GFOBJ_INFO *info = GfObjManager::getObjInfo(handle);
  return info != nullptr && info->state == GFOBJ_STATE_UPDATE;
}

void GfObjUtil::setOwner(GF_OBJ_HANDLE *handle, GF_OBJ_HANDLE *owner) {
  GFOBJ_INFO *info = GfObjManager::getObjInfo(handle);
  if (info != nullptr) {
    info->owner = owner;
  }
}

GF_OBJ_HANDLE *GfObjUtil::getOwner(GF_OBJ_HANDLE *handle) {
  GFOBJ_INFO *info = GfObjManager::getObjInfo(handle);
  return info != nullptr ? info->owner : INVALID_HANDLE;
}

void GfObjUtil::reload(GF_OBJ_HANDLE *handle) {}

bool GfObjUtil::testFlag(GF_OBJ_HANDLE *handle, u32 flag) {
  GFOBJ_INFO *info = GfObjManager::getObjInfo(handle);
  return info != nullptr && info->flags.test(flag);
}

bool GfObjUtil::testFlag(const GfObj *obj, u32 flag) { return obj->info != nullptr && obj->info->flags.test(flag); }

const char *GfObjUtil::getModelBaseName(GF_OBJ_HANDLE *handle) {
  GFOBJ_INFO *info = GfObjManager::getObjInfo(handle);
  return info == nullptr ? "" : info->modelBaseName;
}

const char *GfObjUtil::getAssetModelName(GF_OBJ_HANDLE *handle) { return GfAssetManager::getModelInfo(getAssetHandle(handle)); }

const char *GfObjUtil::getAssetMotionName(GF_OBJ_HANDLE *handle) { return GfAssetManager::getMotionInfo(getAssetHandle(handle)); }

} // namespace gf
