#include "gf/object/gf_obj_factory.h"

#include <string.h>

#include "arc/arc_data.h"
#include "gf/asset/gf_asset_def.h"
#include "gf/asset/gf_asset_factory.h"
#include "gf/asset/gf_asset_manager.h"
#include "gf/asset/gf_asset_pack_info.h"
#include "gf/asset/gf_asset_resource.h"
#include "gf/data/gf_bdat_chrbl.h"
#include "gf/data/gf_bdat_chrdr.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_bdat_wrapper.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/data/gf_data_enemy.h"
#include "gf/data/gf_data_param_acc.h"
#include "gf/data/gf_object_type.h"
#include "gf/field/gf_fobj_dropitem.h"
#include "gf/field/gf_fobj_manager.h"
#include "gf/game/gf_game_manager.h"
#include "gf/gf_allocator.h"
#include "gf/map/gf_map_manager.h"
#include "gf/object/component/gf_com_sound.h"
#include "gf/object/component/property/gf_com_property.h"
#include "gf/object/component/property/gf_env_property.h"
#include "gf/object/gf_append.h"
#include "gf/object/gf_init_param.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_manager.h"
#include "gf/object/gf_obj_setup.h"
#include "gf/object/gf_obj_util.h"
#include "gmk/gmk_bdat.h"
#include "mm_math/mm_math.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/fixed_array.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/rtti.h"
#include "mm_mtl/unique_ptr.h"

namespace gf {
struct GF_ASSET_HANDLE;

// Inferred role: registers a created object with its asset pack and its owner; original name unknown.
static void unknown001(GF_OBJ_HANDLE *handle, GF_ASSET_HANDLE *asset, const GfInitParam &param) {
  GFOBJ_INFO *info = GfObjManager::getObjInfo(handle);
  if (info != nullptr) {
    info->unknown02 = param.unknown24;
    info->unknown10 = asset;
    info->unknown88 = param.unknown38;
    if (GfObjManager::get() != nullptr && param.unknown38 != INVALID_HANDLE) {
      GfObjManager::get()->addFollowObj(handle);
    }
    AssetPackInfo *packInfo = GfAssetManager::getAssetPackInfo(asset);
    if (packInfo != nullptr) {
      packInfo->unknown2d8 = handle;
    }
  }
}

void GfObjFactory::destroyObj(GF_OBJ_HANDLE *handle) { GfObjUtil::destroy(handle); }

bool GfObjFactory::destroyObjHandle(GF_OBJ_HANDLE *handle) {
  GFOBJ_INFO *info = GfObjManager::getObjInfo(handle);
  GfAssetManager::destroy(info->unknown10);
  info->unknown10 = INVALID_ASSET_HANDLE;
  if (GfObjManager::get() != nullptr) {
    GfObjManager::get()->callGfObjListener(IGfObjListener::OBJEVT_REMOVE, handle);
  }
  if (info->unknown18 != nullptr) {
    info->unknown18->setTerminate();
    info->unknown18 = nullptr;
  }
  return true;
}

GF_OBJ_HANDLE *GfObjFactory::createDebugMap(const GfInitParamMap &) { return INVALID_HANDLE; }

GF_OBJ_HANDLE *GfObjFactory::createSmnEnemy(int id, const mm::Vec3 &position, const mm::Vec3 &rotation, bool flag) {
  GF_OBJ_HANDLE *handle = createGmkEnemy(id, 0, 0, position, rotation, flag);
  if (handle != INVALID_HANDLE) {
    {
      DataParamAcc acc(handle);
      if (acc.getSDataEnemy()->unknown04_0) {
        GfObjUtil::destroy(handle);
        return INVALID_HANDLE;
      }
    }
    mm::mtl::dynamicCast<GfObjSetupEnemy>(GfObjManager::getObjInfo(handle)->unknown30)->unknownb2 = true;
    return handle;
  }
  return INVALID_HANDLE;
}

bool checkSoundTriggerPlayer(GfComSound *sound, const fw::ResSoundTriggerInfo &info) {
  if (strcmp(info.unknown00, "S_jump_02") == 0 || strcmp(info.unknown00, "S_jumpdmg") == 0) {
    GfEnvProperty *env = static_cast<GfObj *>(sound->unknown08)->getComponent<GfComProperty>()->unknown28.get();
    GfEnvProperty::unknown002 *ground = (env->unknown2d0 & 2) ? &env->unknown00[0] : nullptr;
    if ((env->unknown2d0 & 1) && ground != nullptr) {
      return !(ground->unknown00.y <= env->unknown280.unknown00.x);
    }
  }
  return true;
}

void setSkelType(u32 type, GfObjSetup *setup) {
  s32 skelType;
  switch (type) {
  case 1:
    skelType = 0;
    break;
  case 2:
    skelType = 4;
    break;
  case 3:
    skelType = 1;
    break;
  case 4:
    skelType = 3;
    break;
  case 5:
    skelType = 5;
    break;
  case 6:
    skelType = 6;
    break;
  case 7:
    skelType = 7;
    break;
  case 8:
    skelType = 8;
    break;
  case 9:
    skelType = 9;
    break;
  case 10:
    skelType = 10;
    break;
  default:
    skelType = -1;
    break;
  }
  setup->unknown68 = skelType;
}

GF_OBJ_HANDLE *GfObjFactory::createMap(const GfInitParamMapSeamless &param) {
  GfObjManager *manager = GfObjManager::get();
  if (manager == nullptr || GfMapManager::getGfObjHandle() != INVALID_HANDLE) {
    return INVALID_HANDLE;
  }
  GF_ASSET_HANDLE *asset = GfAssetFactory::createAssetPackMap(param);
  if (asset == INVALID_ASSET_HANDLE) {
    return INVALID_HANDLE;
  }
  GF_OBJ_HANDLE *handle = manager->createGfObj(OBJECT_TYPE_MAP, param);
  if (handle != INVALID_HANDLE) {
    unknown001(handle, asset, param);
  }
  manager->addHandle(handle);
  GfObjSetup::createSetupParam(handle, param);
  GfObjUtil::addDebugName(handle);
  GfObj *obj = GfObjUtil::getObj(handle);
  if (obj != nullptr) {
    obj->setUpdateComponent(true);
  }
  manager->callGfObjListener(IGfObjListener::OBJEVT_ENTRY, handle);
  return handle;
}

GF_OBJ_HANDLE *GfObjFactory::createMapObj(const GfInitParamGimmick &param) {
  GfObjManager *manager = GfObjManager::get();
  if (manager == nullptr) {
    return INVALID_HANDLE;
  }
  GF_ASSET_HANDLE *asset = GfAssetFactory::createAssetPackGimmick(param);
  GF_OBJ_HANDLE *handle = manager->createGfObj(OBJECT_TYPE_GIMMICK, param);
  if (handle != INVALID_HANDLE) {
    unknown001(handle, asset, param);
  }
  manager->addHandle(handle);
  GfObjSetup::createSetupParam(handle, param);
  GfObjUtil::addDebugName(handle);
  GfObjAcc acc(handle);
  acc.setCameraFade(false);
  manager->callGfObjListener(IGfObjListener::OBJEVT_ENTRY, handle);
  return handle;
}

GF_OBJ_HANDLE *GfObjFactory::createEventObj(const GfInitParamEventObj &param) {
  GfObjManager *manager = GfObjManager::get();
  if (manager == nullptr) {
    return INVALID_HANDLE;
  }
  GF_ASSET_HANDLE *asset = GfAssetFactory::createAssetPackEventObj(param);
  GF_OBJ_HANDLE *handle = manager->createGfObj(OBJECT_TYPE_EVENT, param);
  if (handle != INVALID_HANDLE) {
    unknown001(handle, asset, param);
  }
  manager->addHandle(handle);
  GfObjSetupEventObj *setup = GfObjSetup::createSetupParam(handle, param);
  GfAssetManager::setModelInfo(asset, setup->unknown6c.c_str());
  GfObjUtil::addDebugName(handle);
  manager->callGfObjListener(IGfObjListener::OBJEVT_ENTRY, handle);
  return handle;
}

GF_OBJ_HANDLE *GfObjFactory::createUiObj(const GfInitParamUiObj &param) {
  GfObjManager *manager = GfObjManager::get();
  if (manager == nullptr) {
    return INVALID_HANDLE;
  }
  GF_ASSET_HANDLE *asset = GfAssetFactory::createAssetPackUiObj(param);
  GF_OBJ_HANDLE *handle = manager->createGfObj(OBJECT_TYPE_UI, param);
  if (handle != INVALID_HANDLE) {
    unknown001(handle, asset, param);
  }
  manager->addHandle(handle);
  GfObjSetup::createSetupParam(handle, param);
  GfObjUtil::addDebugName(handle);
  manager->callGfObjListener(IGfObjListener::OBJEVT_ENTRY, handle);
  return handle;
}

GF_OBJ_HANDLE *GfObjFactory::createMapLodAnim() {
  GfObjManager *manager = GfObjManager::get();
  if (manager == nullptr) {
    return INVALID_HANDLE;
  }
  GfInitParamMapLodAnim param;
  GF_OBJ_HANDLE *handle = manager->createGfObj(OBJECT_TYPE_UNKNOWN_2, param);
  GfObjSetup::createSetupParam(handle, param);
  manager->addHandle(handle);
  GfObjAcc acc(handle);
  acc.setCameraFade(false);
  manager->callGfObjListener(IGfObjListener::OBJEVT_ENTRY, handle);
  return handle;
}

GF_OBJ_HANDLE *GfObjFactory::createGmkEvent(const CBdatWrapper &bdat, int id) {
  GfObjManager *manager = GfObjManager::get();
  if (manager == nullptr) {
    return INVALID_HANDLE;
  }
  GfInitParamGimmick param;
  param.m_bladeID = id;
  param.unknown90 = reinterpret_cast<void *>(bdat.getValCheck("name", id, gmk::BDAT_TYPE_STRING));
  GF_OBJ_HANDLE *handle = manager->createGfObj(OBJECT_TYPE_GIMMICK, param);
  manager->addHandle(handle);
  GfObjSetup::createSetupParam(handle, param);
  GfObjUtil::addDebugName(handle);
  manager->callGfObjListener(IGfObjListener::OBJEVT_ENTRY, handle);
  return handle;
}

GF_OBJ_HANDLE *GfObjFactory::createGmkCollection(const CBdatWrapper &bdat, int id) {
  GfObjManager *manager = GfObjManager::get();
  if (manager == nullptr) {
    return INVALID_HANDLE;
  }
  GfInitParamGimmick param;
  param.m_bladeID = id;
  param.unknown90 = reinterpret_cast<void *>(bdat.getValCheck("name", id, gmk::BDAT_TYPE_STRING));
  GF_OBJ_HANDLE *handle = manager->createGfObj(OBJECT_TYPE_GIMMICK, param);
  manager->addHandle(handle);
  GfObjSetup::createSetupParam(handle, param);
  GfObjUtil::addDebugName(handle);
  manager->callGfObjListener(IGfObjListener::OBJEVT_ENTRY, handle);
  return handle;
}

GF_OBJ_HANDLE *GfObjFactory::createGmkMapGimmick(const CBdatWrapper &bdat, int id) {
  GfObjManager *manager = GfObjManager::get();
  if (manager == nullptr) {
    return INVALID_HANDLE;
  }
  GfInitParamGimmick param;
  param.m_bladeID = id;
  param.unknown90 = reinterpret_cast<void *>(bdat.getValCheck("name", id, gmk::BDAT_TYPE_STRING));
  param.unknown40 = 0;
  GF_OBJ_HANDLE *handle = manager->createGfObj(OBJECT_TYPE_GIMMICK, param);
  manager->addHandle(handle);
  GfObjSetup::createSetupParam(handle, param);
  GfObjUtil::addDebugName(handle);
  manager->callGfObjListener(IGfObjListener::OBJEVT_ENTRY, handle);
  return handle;
}

GF_OBJ_HANDLE *GfObjFactory::createGmkMob(int id, u16 param2, u16 param3, u16 param4, u16 param5) {
  CBdatWrapper bdat(GfDataBdat::getFP(BDAT_RSC_MOB_LIST));
  GfInitParamMob param;
  param.m_bladeID = id;
  param.unknown18 = &bdat;
  param.unknown90 = param2;
  param.unknown92 = param3;
  param.unknown94 = param4;
  param.unknown96 = param5;
  return createMob(param);
}

GF_OBJ_HANDLE *GfObjFactory::createMobNull() {
  GfInitParamMob param;
  GfObjManager *manager = GfObjManager::get();
  if (manager == nullptr || GfGameManager::isAssetNumberInvalid()) {
    return INVALID_HANDLE;
  }
  GF_OBJ_HANDLE *handle = manager->createGfObj(OBJECT_TYPE_MOB, param);
  if (handle == INVALID_HANDLE) {
    return INVALID_HANDLE;
  }
  manager->addHandle(handle);
  GfObjSetup::createSetupParam(handle, param);
  manager->callGfObjListener(IGfObjListener::OBJEVT_ENTRY, handle);
  return handle;
}

GF_OBJ_HANDLE *GfObjFactory::createFieldObj(const GfInitParamFobj &param) {
  GfObjManager *manager = GfObjManager::get();
  if (manager == nullptr) {
    return INVALID_HANDLE;
  }
  GF_ASSET_HANDLE *asset = GfAssetFactory::createAssetPackFobj(param);
  GF_OBJ_HANDLE *handle = manager->createGfObj(OBJECT_TYPE_FOBJ, param);
  if (handle != INVALID_HANDLE) {
    unknown001(handle, asset, param);
  }
  manager->addHandle(handle);
  GfObjSetup::createSetupParam(handle, param);
  GfObjUtil::addDebugName(handle);
  if (param.unknown95) {
    // __LINE__ must be 2409 as in the original file: it is the line argument of the allocation.
#line 2409
    GfFobjDropitem *dropitem = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) GfFobjDropitem(handle);
    GfFobjManager::registFiledObj(dropitem);
  }
  manager->callGfObjListener(IGfObjListener::OBJEVT_ENTRY, handle);
  return handle;
}

GF_OBJ_HANDLE *GfObjFactory::createExtraModel(GfInitParamExtra &param) {
  GfObjManager *manager = GfObjManager::get();
  if (manager == nullptr) {
    return INVALID_HANDLE;
  }
  GF_ASSET_HANDLE *asset = GfAssetFactory::createAssetPackExtra(param);
  if (asset == INVALID_ASSET_HANDLE) {
    return INVALID_HANDLE;
  }
  GF_OBJ_HANDLE *handle = manager->createGfObj(OBJECT_TYPE_UNKNOWN_14, param);
  if (handle != INVALID_HANDLE) {
    unknown001(handle, asset, param);
  }
  u16 mountIndex = param.unknown90.getMountIndex();
  if (handle != INVALID_HANDLE) {
    GFOBJ_INFO *info = GfObjManager::getObjInfo(handle);
    if (info != nullptr) {
      info->unknownb8[GFATTACH_APPEND].unknown08 = mountIndex;
    }
  }
  manager->addHandle(handle);
  GfObjSetup::createSetupParam(handle, param);
  GfAppendUtil::setupExtraModel(handle, param.unknown38);
  GfObjUtil::addDebugName(handle);
  manager->callGfObjListener(IGfObjListener::OBJEVT_ENTRY, handle);
  return handle;
}

GF_OBJ_HANDLE *GfObjFactory::createBelonging(GfInitParamBelonging &param) {
  GfObjManager *manager = GfObjManager::get();
  if (manager == nullptr) {
    return INVALID_HANDLE;
  }
  GF_ASSET_HANDLE *asset = GfAssetFactory::createAssetPackBelonging(param);
  if (asset == INVALID_ASSET_HANDLE) {
    return INVALID_HANDLE;
  }
  GF_OBJ_HANDLE *handle = manager->createGfObj(OBJECT_TYPE_BELONGING, param);
  if (handle != INVALID_HANDLE) {
    unknown001(handle, asset, param);
  }
  u16 mountIndex = param.unknown90.getMountIndex();
  if (handle != INVALID_HANDLE) {
    GFOBJ_INFO *info = GfObjManager::getObjInfo(handle);
    if (info != nullptr) {
      info->unknownb8[GFATTACH_BELONGING].unknown08 = mountIndex;
    }
  }
  manager->addHandle(handle);
  GfObjSetup::createSetupParam(handle, param);
  if (!param.unknown120) {
    GfAppendUtil::setupBelonging(handle, param.unknown118, param.unknown11a, param.unknown11c, param.unknown11e);
  } else {
    GfAppendUtil::setupBelongingForDriver(handle, *param.unknown128);
  }
  GfObjUtil::addDebugName(handle);
  manager->callGfObjListener(IGfObjListener::OBJEVT_ENTRY, handle);
  return handle;
}

void addExtendPackingSoundTrigger(GF_ASSET_HANDLE *handle, GfFileIdx index, GfExtendPacking *packing) {
  if (packing != nullptr) {
    GfAssetResource *resource = GfAssetManager::getResource(handle, index, ASSET_TYPE_BASE);
    if (resource != nullptr) {
      arc::CArcData archive(resource->getAssetData());
      u32 count = archive.getFiles();
      for (u32 i = 0; i < count; i++) {
        fw::SoundResTriggerImporter::unknown001 *trigger = fw::SoundResTriggerImporter::importBinary(archive.getFileAdr(i));
        if (trigger != nullptr) {
          packing->unknown20.push(trigger);
        }
      }
    }
  }
}

bool getSlopeIKLimit(GfObj *obj, f32 *pitch, f32 *roll) {
  u32 type = GfObjUtil::getObjType(obj->unknownf8);
  if (type == OBJECT_TYPE_DRIVER) {
    GfObjSetup *setup = GfObjUtil::getObjSetup(obj->unknownf8);
    GfBdatChrDr *bdat = GfBdatChrDr::get();
    u32 driver = setup->unknown10;
    u8 pitchLimit = bdat->getChrDrRotateLimitPitch(driver);
    u8 rollLimit = bdat->getChrDrRotateLimitRoll(driver);
    *pitch = pitchLimit * mm::DEG_TO_RAD;
    *roll = rollLimit * mm::DEG_TO_RAD;
    return true;
  }
  if (type == OBJECT_TYPE_BLADE) {
    GfObjSetup *setup = GfObjUtil::getObjSetup(obj->unknownf8);
    GfBdatChrBl *bdat = GfBdatChrBl::get();
    u32 blade = setup->unknown10;
    u8 pitchLimit = bdat->getChrBlRotateLimitPitch(blade);
    u8 rollLimit = bdat->getChrBlRotateLimitRoll(blade);
    *pitch = pitchLimit * mm::DEG_TO_RAD;
    *roll = rollLimit * mm::DEG_TO_RAD;
    return true;
  }
  return false;
}

} // namespace gf
