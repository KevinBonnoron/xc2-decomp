#include "gf/asset/gf_asset_util.h"

#include "gf/asset/gf_asset_manager.h"
#include "gf/asset/gf_asset_pack_info.h"
#include "gf/data/gf_data_param_acc.h"
#include "gf/data/gf_object_type.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_manager.h"
#include "mm_mtl/fixed_list.h"

namespace gf {

namespace {

const char *const unknown001[] = {
    "atEmpty",  "atProg",      "atDebug",     "atMap",       "atPc",   "atPcCom", "atBlade", "atBladeCom", "atWeapon", "atWeaponEff",
    "atEneNpc", "atEneNpcMot", "atEneNpcArc", "atEneNpcEff", "atFobj", "atMobj",  "atPcWm",  "atOption",   "atTemp",   "atSound"}; // Inferred role: names of GfAssetType; original name unknown.

} // namespace

void GfAssetUtil::addDestroyObject(GF_ASSET_HANDLE *handle, bool flag) {
  GfObjAcc acc(getObjHandle(handle));
  if (acc.isValid() && !acc.isDestroy()) {
    GfObjManager *manager = GfObjManager::get();
    if (manager != nullptr) {
      manager->addDestroyObj(getObjHandle(handle), flag);
    }
  }
}

GF_OBJ_HANDLE *GfAssetUtil::getObjHandle(GF_ASSET_HANDLE *handle) {
  AssetPackInfo *info = GfAssetManager::getAssetPackInfo(handle);
  if (info != nullptr) {
    return info->unknown2d8;
  }
  return INVALID_HANDLE;
}

void GfAssetUtil::getAssetHandleBySlotHandle(mm::mtl::FixedList<GF_ASSET_HANDLE *, 1024> &assets, const mm::mtl::FixedList<GF_ASSET_HANDLE *, 1024> &handles, GF_SLOT_HANDLE *slot) {
  for (mm::mtl::FixedList<GF_ASSET_HANDLE *, 1024>::const_iterator it = handles.begin(); it != handles.end(); ++it) {
    if (GfAssetManager::getAssetPack(slot) != nullptr) {
      assets.push_back(*it);
    }
  }
}

u32 GfAssetUtil::getAssetPrio(GF_ASSET_HANDLE *handle) {
  DataParamAcc paramAcc(getObjHandle(handle));
  if (paramAcc.isValid() && paramAcc.getObjType() == OBJECT_TYPE_ENEMY) {
    return paramAcc.getLevel(false);
  }
  return 0;
}

bool GfAssetUtil::isObjectDestroy(GF_ASSET_HANDLE *handle) {
  GfObjAcc acc(getObjHandle(handle));
  if (!acc.isValid()) {
    return true;
  }
  return acc.isDestroy();
}

bool GfAssetUtil::isRetargetLoad(GF_ASSET_HANDLE *handle) {
  AssetPackInfo *info = GfAssetManager::getAssetPackInfo(handle);
  if (info != nullptr) {
    return info->unknown306;
  }
  return false;
}

void GfAssetUtil::setRetargetLoad(GF_ASSET_HANDLE *handle, bool isRetarget) {
  AssetPackInfo *info = GfAssetManager::getAssetPackInfo(handle);
  if (info != nullptr) {
    info->unknown306 = isRetarget;
  }
}

const char *GfAssetUtil::getAssetTypeName(GfAssetType type) { return unknown001[type]; }

} // namespace gf
