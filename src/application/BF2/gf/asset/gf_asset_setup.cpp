#include "gf/asset/gf_asset_setup.h"

#include "gf/asset/gf_asset_manager.h"
#include "gf/asset/gf_asset_name.h"
#include "gf/asset/gf_asset_pack.h"
#include "gf/asset/gf_asset_resource.h"
#include "gf/data/gf_bdat_chrenarrange.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_bdat_rsc.h"
#include "gf/data/gf_bdat_wrapper.h"
#include "gf/data/gf_character_id.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/data/gf_data_blade.h"
#include "gf/data/gf_data_driver.h"
#include "gf/data/gf_data_enemy.h"
#include "gf/data/gf_data_hana.h"
#include "gf/data/gf_data_map.h"
#include "gf/data/gf_data_mob.h"
#include "gf/data/gf_data_npc.h"
#include "gf/data/gf_data_param_acc.h"
#include "gf/data/gf_data_sound.h"
#include "gf/data/gf_data_util.h"
#include "gf/data/gf_data_weapon.h"
#include "gf/data/gf_object_type.h"
#include "gf/game/gf_game_util.h"
#include "gf/gf_allocator.h"
#include "gf/object/gf_init_param.h"
#include "gf/util/gf_util.h"
#include "mm_mtl/fixed_queue.h"
#include "nn/diag.h"
#include "string.h"

namespace gf {

namespace {

const int SALVAGE_MOTION_NUMBER = 99;
const int UI_MOTION_NUMBER = 98;
const u32 HANA_JS_ATTRIBUTE = 5;
const u32 HANA_JK_ATTRIBUTE = 1;
const u32 HANA_JD_ATTRIBUTE = 5;
const int BDAT_TYPE_STRING = 7;
const char *const MOB_EVENT_MOTION = "np423000";
const char *const NPC_EVENT_MODEL = "np/np002001";
const GfFileIdx FOOT_STEP_SE_FILE_INDEX = static_cast<GfFileIdx>(1);
const GfFileIdx FOOT_STEP_SE_SUB_FILE_INDEX = static_cast<GfFileIdx>(2);
const GfFileIdx ADD_MOTION_FILE_INDEX = static_cast<GfFileIdx>(15);

const char *getValidName(const char *name) {
  if (name == nullptr || *name == '\0') {
    return nullptr;
  }
  return name;
}

const char *getRscValue(const GfAssetSetup *setup, u32 table, const char *member) {
  CBdatWrapper rsc = {GfDataBdat::getFP(table)};
  const CBdatWrapper *bdat = setup->bdat != nullptr ? setup->bdat : &rsc;
  return reinterpret_cast<const char *>(bdat->getValCheck(member, setup->id, BDAT_TYPE_STRING));
}

void makeWeaponFileName(mm::mtl::FixStr<128> &fileName, const mm::mtl::FixStr<128> &refName, const char *name, bool isDeathBlowWeapon) {
  fileName.clear();
  if (!refName.empty()) {
    fileName = refName.c_str();
  } else if (name != nullptr && *name != '\0') {
    fileName = name;
  }

  if (isDeathBlowWeapon) {
    int length = fileName.length();
    int index = -1;
    for (int i = 0; i < length; i++) {
      if (strncmp(fileName.c_str() + i, "wp/", 3) == 0) {
        index = i;
        break;
      }
    }
    if (index != -1) {
      fileName.erase(0, 3);
      fileName.insert(0, "db/", 3);
    }
  }
}

GfAssetType makeMotionAssetName(mm::mtl::FixStr<128> &name, GfAssetType type, const char *motion) {
  NN_ABORT_UNLESS(*motion != '\0');
  if (strstr(motion, MOB_EVENT_MOTION) != nullptr) {
    type = ASSET_TYPE_TEMPORARY;
  }
  if (type == ASSET_TYPE_TEMPORARY || type == ASSET_TYPE_MAP_OBJECT) {
    GfAssetSetup::makeAssetNamePrefix(name, type, motion, "Mot");
  } else {
    GfAssetSetup::makeAssetNamePrefix(name, type, motion, "");
  }
  return type;
}

} // namespace

GfAssetSetup::GfAssetSetup() : id(0), handle(INVALID_ASSET_HANDLE), bdat(nullptr), hasRefResource(false) { initParam = nullptr; }

GfAssetSetup::~GfAssetSetup() {
  for (RefResource *&resource : refResources) {
    if (resource != nullptr) {
      delete resource;
      resource = nullptr;
    }
  }
  GfAssetManager::lockEnterRersource(handle);
  if (bdat != nullptr) {
    delete bdat;
    bdat = nullptr;
  }
}

void GfAssetSetup::setupParam(GF_ASSET_HANDLE *handle, const GfInitParam &param) {
  this->handle = handle;
  id = param.id;
  initParam = &param;
  if (param.bdat != nullptr) {
    // __LINE__ must be 100 as in the original source: it is the line argument of operator new.
#line 100
    bdat = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) CBdatWrapper(*param.bdat);
  }
}

void GfAssetSetup::requestCoreResource(GfAssetPack *pack, GF_ASSET_HANDLE *handle) {
  if (pack == nullptr) {
    return;
  }

  GfAssetFiles &files = pack->files;

  if (const char *file = getMdlFile(files.assetType)) {
    if (!setupReference(pack, file, getMdlSlot())) {
      GfAssetManager::setModelInfo(handle, file);
      mm::mtl::FixStr<128> path;
      path.format("%s%s%s", getPath(), file, ".wimdo");
      files.addResource(getMdlSlot(), path.c_str());
    }
  }

  if (const char *file = getArcFile(files.assetType)) {
    if (!setupReference(pack, file, getArcSlot())) {
      mm::mtl::FixStr<128> path;
      path.format("%s%s%s", getPath(), file, ".arc");
      files.addResource(getArcSlot(), path.c_str());
    }
  }

  if (const char *file = getMotFile(files.assetType)) {
    if (!setupReference(pack, file, getMotSlot())) {
      GfAssetManager::setMotionInfo(handle, file);
      mm::mtl::FixStr<128> path;
      path.format("%s%s%s", getPath(), file, ".mot");
      files.addResource(getMotSlot(), path.c_str());
    }
  }

  if (const char *file = getEvtMotFile(files.assetType)) {
    if (!setupReference(pack, file, getEvtMotSlot())) {
      mm::mtl::FixStr<128> path;
      path.format("%s%s%s", getEvtPath(), file, ".mot");
      files.addResource(getEvtMotSlot(), path.c_str());
    }
  }

  if (const char *file = getEfpFile(files.assetType)) {
    if (!setupReference(pack, file, getEfpSlot())) {
      mm::mtl::FixStr<128> path;
      path.format("%s%s%s", getPath(), file, ".wiefp");
      if (!files.addResource(getEfpSlot(), path.c_str())) {
        pack->dispAssetLogForDebug();
      }
    }
  }

  if (const char *file = getEabFile(files.assetType)) {
    if (!setupReference(pack, file, getEabSlot())) {
      mm::mtl::FixStr<128> path;
      path.format("%s%s%s", getEffPath(), file, ".wieab");
      files.addResource(getEabSlot(), path.c_str());
    }
  }

  if (const char *file = getEfbFile(files.assetType)) {
    if (!setupReference(pack, file, getEfbSlot())) {
      mm::mtl::FixStr<128> path;
      path.format("%s%s%s", getEffPath(), file, ".wiefb");
      files.addResource(getEfbSlot(), path.c_str());
    }
  }

  if (const char *file = getStpFile(files.assetType)) {
    mm::mtl::FixStr<128> name;
    GfAssetFilesInfo info;
    info.handle = handle;
    info.assetType = ASSET_TYPE_ENEMY_ARC;
    info.name = name.c_str();
    makeAssetNamePrefix(name, ASSET_TYPE_ENEMY_ARC, file, "Stp");
    GfAssetPack *stpPack = GfAssetManager::createAssetFiles(info);
    if (!setupReference(stpPack, file, getStpSlot())) {
      mm::mtl::FixStr<128> path;
      path.format("%s%s%s", getStpPath(), file, ".stp");
      stpPack->files.addResource(getStpSlot(), path.c_str());
    }
  }

  if (const char *file = getEvtStpFile(files.assetType)) {
    mm::mtl::FixStr<128> name;
    GfAssetFilesInfo info;
    info.handle = handle;
    info.assetType = ASSET_TYPE_ENEMY_ARC;
    info.name = name.c_str();
    makeAssetNamePrefix(name, ASSET_TYPE_ENEMY_ARC, file, "EvtStp");
    GfAssetPack *stpPack = GfAssetManager::createAssetFiles(info);
    if (!setupReference(stpPack, file, getEvtStpSlot())) {
      mm::mtl::FixStr<128> path;
      path.format("%s%s%s", getEvtPath(), file, ".stp");
      stpPack->files.addResource(getEvtStpSlot(), path.c_str());
    }
  }
}

bool GfAssetSetup::setupReference(GfAssetPack *pack, const char *name, GfFileIdx index) {
  RefResource *resource = getRefResource(index);
  if (resource == nullptr || resource->data == nullptr) {
    return false;
  }

  if (pack->getResource(index) == nullptr) {
    GfAssetResource *assetResource = GfAssetResource::create(pack->getAssetName(), name, resource->data, resource->size);
    pack->files.addResource(index, name);
    pack->setResource(index, assetResource);
  }
  return true;
}

void GfAssetSetup::makeAssetNamePrefix(mm::mtl::FixStr<128> &name, GfAssetType type, const char *file, const char *suffix) {
  name.format("%2d", type);
  if (file != nullptr) {
    name += util::getNoPathExtName(file).c_str();
  }
  if (suffix != nullptr) {
    name += util::getNoPathExtName(suffix).c_str();
  }
}

bool GfAssetSetup::checkValidResource() {
  if (getMdlFile(getAssetType()) != nullptr && *getMdlFile(getAssetType()) != '\0') {
    return true;
  }

  GfAssetManager::destroy(handle);
  handle = INVALID_ASSET_HANDLE;
  return false;
}

GfAssetSetup::RefResource *GfAssetSetup::getRefResource(u32 index) {
  for (RefResource *resource : refResources) {
    if (resource->index == index) {
      return resource;
    }
  }
  return nullptr;
}

void GfAssetSetup::setRefResource(u32 index, const char *name, void *data, u32 size) {
  RefResource *resource = getRefResource(index);
  if (resource == nullptr) {
    // __LINE__ must be 282 as in the original source: it is the line argument of operator new.
#line 282
    resource = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) RefResource();
    refResources.push_back(resource);
    resource->index = index;
  }
  resource->name = name;
  resource->data = data;
  resource->size = size;
  hasRefResource = true;
}

void GfAssetSetup::makeAssetName(mm::mtl::FixStr<128> &name, GfAssetType type, const char *file) { makeAssetNamePrefix(name, type, file, ""); }

void GfAssetSetup::requestFootStepSePackFile(GfAssetFilesInfo &info, u32 footStep, GfFileIdx firstIndex, GfFileIdx secondIndex) {
  mm::mtl::FixedVector<const char *, 2> files;
  if (!GfDataSound::getFootStepSePackFile(files, footStep)) {
    return;
  }

  mm::mtl::FixStr<128> name;
  info.assetType = ASSET_TYPE_SE;
  info.backupAssetTypes.clear();
  info.backupAssetTypes.push(ASSET_TYPE_TEMPORARY);
  info.name = name.c_str();
  for (u32 i = 0; i < files.size(); i++) {
    makeAssetNamePrefix(name, info.assetType, files[i], "");
    GfAssetPack *pack = GfAssetManager::createAssetFiles(info);
    GfFileIdx index = i == 0 ? firstIndex : secondIndex;
    mm::mtl::FixStr<128> path;
    path.format("%s%s%s", GfAssetPath::getSePack(), files[i], ".xsp");
    pack->files.addResource(index, path.c_str());
    pack->sePackFileIndex = index;
  }
}

void GfAssetSetup::requestWpnSePackFile(GfAssetFilesInfo &info, u32 weaponType, GfFileIdx index) {
  const char *file = GfDataSound::getSeFileByWeaponType(weaponType);
  if (file == nullptr) {
    return;
  }

  mm::mtl::FixStr<128> name;
  info.assetType = ASSET_TYPE_SE;
  info.backupAssetTypes.clear();
  info.backupAssetTypes.push(ASSET_TYPE_TEMPORARY);
  info.name = name.c_str();
  makeAssetNamePrefix(name, info.assetType, file, "");
  GfAssetPack *pack = GfAssetManager::createAssetFiles(info);
  GfFileIdx seIndex = static_cast<GfFileIdx>(weaponType + index - 1);
  mm::mtl::FixStr<128> path;
  path.format("%s%s%s", GfAssetPath::getSePack(), file, ".xsp");
  pack->files.addResource(seIndex, path.c_str());
  pack->sePackFileIndex = seIndex;
}

GfAssetSetupDriver::GfAssetSetupDriver() : reservedFileIndex(FILE_IDX_NONE) {}

bool GfAssetSetupDriver::makeAssetNameWpnType(mm::mtl::FixStr<128> &name, GfAssetType type, u32 driver, u32 weaponType, u32 blade) {
  name = "";
  mm::mtl::FixStr<128> anim;
  if (GfDataDriver::getDriverAddAnim(anim, driver, weaponType) && !anim.empty()) {
    mm::mtl::FixStr<32> suffix;
    if (blade < 10) {
      suffix.format("_bl000%d", blade);
    } else if (blade < 100) {
      suffix.format("_bl00%d", blade);
    } else if (blade < 1000) {
      suffix.format("_bl0%d", blade);
    } else {
      suffix.format("_bl%2d", blade);
    }
    makeAssetNamePrefix(name, type, anim.c_str(), suffix.c_str());
    return true;
  }
  return false;
}

bool GfAssetSetupDriver::makeAssetNameWpnTypeEff(mm::mtl::FixStr<128> &name, GfAssetType type, u32 driver, u32 weaponType, u32 blade, u32 attribute) {
  name = "";
  mm::mtl::FixStr<128> anim;
  if (GfDataDriver::getDriverAddAnim(anim, driver, weaponType) && !anim.empty()) {
    mm::mtl::FixStr<32> suffix;
    suffix.format("_%s", GfDataUtil::getAttributeFileName(attribute));
    makeAssetNamePrefix(name, type, anim.c_str(), suffix.c_str());
    return true;
  }
  return false;
}

u32 GfAssetSetupDriver::getFootStepId() const {
  DataParamAcc dataParamAcc(OBJECT_TYPE_DRIVER, id, GIMMICK_TYPE_NONE);
  return dataParamAcc.getFootStep();
}

const char *GfAssetSetupDriver::getMdlFile(GfAssetType type) {
  RefResource *resource = getRefResource(getMdlSlot());
  if (resource != nullptr && !resource->name.empty()) {
    return resource->name.c_str();
  }
  const char *model = GfGameUtil::getDriverModel(id);
  if (model == nullptr || *model == '\0') {
    return nullptr;
  }
  return model;
}

const char *GfAssetSetupDriver::getArcFile(GfAssetType type) {
  RefResource *resource = getRefResource(getArcSlot());
  if (resource != nullptr && !resource->name.empty()) {
    return resource->name.c_str();
  }
  const char *model = GfGameUtil::getDriverModel(id);
  if (model == nullptr || *model == '\0') {
    return nullptr;
  }
  return model;
}

const char *GfAssetSetupDriver::getMotFile(GfAssetType type) {
  if (getAssetTypeMot() == type) {
    RefResource *resource = getRefResource(getMotSlot());
    if (resource != nullptr && !resource->name.empty()) {
      return resource->name.c_str();
    }
    DataParamAcc dataParamAcc(OBJECT_TYPE_DRIVER, id, GIMMICK_TYPE_NONE);
    return getValidName(dataParamAcc.getMotionResourceName());
  }
  return nullptr;
}

const char *GfAssetSetupDriver::getEfpFile(GfAssetType type) { return getMdlFile(type); }

const char *GfAssetSetupDriver::getEabFile(GfAssetType type) {
  DataParamAcc dataParamAcc(OBJECT_TYPE_DRIVER, id, GIMMICK_TYPE_NONE);
  return dataParamAcc.getEffectResourceName();
}

const char *GfAssetSetupDriver::getEfbFile(GfAssetType type) {
  if (getAssetTypeMot() == type) {
    return getEabFile(type);
  }
  return nullptr;
}

const char *GfAssetSetupDriver::getEfTailFile(GfAssetType type) {
  if (type == ASSET_TYPE_WEAPON_MOTION) {
    return getEabFile(ASSET_TYPE_WEAPON_MOTION);
  }
  return nullptr;
}

const char *GfAssetSetupDriver::getStpFile(GfAssetType type) {
  if (getAssetType() == type) {
    DataParamAcc dataParamAcc(OBJECT_TYPE_DRIVER, id, GIMMICK_TYPE_NONE);
    return getValidName(dataParamAcc.getMotionResourceName());
  }
  return nullptr;
}

const char *GfAssetSetupDriver::getPath() const { return GfAssetPath::getMdoModel(); }

void GfAssetSetupDriver::changeResoueceEffName(mm::mtl::FixStr<128> &name) {
  GfAssetName assetName(name.c_str());
  name = assetName.getName();
}

const char *GfAssetSetupEventDriver::getEvtMotFile(GfAssetType type) {
  if (getAssetTypeEvtMot() == type) {
    RefResource *resource = getRefResource(getEvtMotSlot());
    if (resource != nullptr && !resource->name.empty()) {
      return resource->name.c_str();
    }
    DataParamAcc dataParamAcc(OBJECT_TYPE_DRIVER, id, GIMMICK_TYPE_NONE);
    return getValidName(dataParamAcc.getMotionResourceName());
  }
  return nullptr;
}

const char *GfAssetSetupEventDriver::getEvtStpFile(GfAssetType type) {
  if (getAssetType() == type) {
    DataParamAcc dataParamAcc(OBJECT_TYPE_DRIVER, id, GIMMICK_TYPE_NONE);
    return getValidName(dataParamAcc.getMotionResourceName());
  }
  return nullptr;
}

const char *GfAssetSetupEventDriver::getEvtPath() const { return GfAssetPath::getEvt(); }

void GfAssetSetupSalvage::setup(GF_ASSET_HANDLE *handle, const GfInitParamDriver &param) {
  setupParam(handle, param);
  if (!checkValidResource()) {
    return;
  }

  mm::mtl::FixStr<128> name;
  GfAssetFilesInfo info;
  info.handle = handle;
  info.name = name.c_str();
  info.priority = param.priority;
  info.assetType = getAssetType();
  makeAssetNamePrefix(name, info.assetType, getMdlFile(info.assetType), "");
  GfAssetPack *corePack = GfAssetManager::createAssetFiles(info);
  requestCoreResource(corePack, handle);

  info.assetType = getAssetTypeMot();
  if (const char *motion = getMotFile(info.assetType)) {
    makeAssetNamePrefix(name, info.assetType, motion, "");
    GfAssetPack *pack = GfAssetManager::createAssetFiles(info);
    if (!setupReference(pack, name.c_str(), getMotSlot())) {
      GfAssetManager::setMotionInfo(handle, motion);
      mm::mtl::FixStr<128> path;
      path.format("%s%s%s", getPath(), motion, ".mot");
      pack->files.addResource(getMotSlot(), path.c_str());
    }
  }

  info.assetType = getAssetTypeMot();
  if (const char *efb = getEfbFile(info.assetType)) {
    makeAssetNamePrefix(name, info.assetType, efb, "");
    GfAssetPack *pack = GfAssetManager::createAssetFiles(info);
    if (!setupReference(pack, efb, getEfbSlot())) {
      mm::mtl::FixStr<128> path;
      path.format("%s%s%s", getEffPath(), efb, ".wiefb");
      pack->files.addResource(getEfbSlot(), path.c_str());
    }
  }

  info.assetType = ASSET_TYPE_WEAPON_MOTION;
  if (const char *motion = getSalvageMotFile(info.assetType)) {
    makeAssetNamePrefix(name, info.assetType, motion, getAssetCategoryName());
    GfAssetPack *pack = GfAssetManager::createAssetFiles(info);
    if (!setupReference(pack, motion, getSalvageMotSlot())) {
      mm::mtl::FixStr<128> path;
      path.format("%s%s%s", getPath(), motion, ".mot");
      pack->files.addResource(getSalvageMotSlot(), path.c_str());
    }
  }

  info.assetType = getAssetType();
  info.backupAssetTypes.clear();
  info.backupAssetTypes.push(ASSET_TYPE_TEMPORARY);
  if (const char *stp = getSalvageStpFile(info.assetType)) {
    makeAssetNamePrefix(name, info.assetType, stp, getAssetCategoryName());
    GfAssetPack *pack = GfAssetManager::createAssetFiles(info);
    if (!setupReference(pack, stp, getSalvageStpSlot())) {
      mm::mtl::FixStr<128> path;
      path.format("%s%s%s", getStpPath(), stp, ".stp");
      pack->files.addResource(getSalvageStpSlot(), path.c_str());
    }
  }

  requestFootStepSePackFile(info, getFootStepId(), FOOT_STEP_SE_FILE_INDEX, FOOT_STEP_SE_SUB_FILE_INDEX);
}

const char *GfAssetSetupSalvage::getMdlFile(GfAssetType type) { return GfGameUtil::getSalvageDriverModel(id); }

const char *GfAssetSetupSalvage::getArcFile(GfAssetType type) { return getMdlFile(type); }

const char *GfAssetSetupSalvage::getSalvageMotFile(GfAssetType type) {
  if (type == ASSET_TYPE_WEAPON_MOTION) {
    DataParamAcc dataParamAcc(OBJECT_TYPE_DRIVER, id, GIMMICK_TYPE_NONE);
    const char *motion = getValidName(dataParamAcc.getMotionResourceName());
    static mm::mtl::FixStr<128> s_motion;
    s_motion.clear();
    s_motion.format("%s_%d", motion, SALVAGE_MOTION_NUMBER);
    return s_motion.c_str();
  }
  return nullptr;
}

const char *GfAssetSetupSalvage::getSalvageStpFile(GfAssetType type) {
  if (getAssetType() == type) {
    DataParamAcc dataParamAcc(OBJECT_TYPE_DRIVER, id, GIMMICK_TYPE_NONE);
    const char *motion = getValidName(dataParamAcc.getMotionResourceName());
    static mm::mtl::FixStr<128> s_stp;
    s_stp.clear();
    s_stp.format("%s_%d", motion, SALVAGE_MOTION_NUMBER);
    return s_stp.c_str();
  }
  return nullptr;
}

const char *GfAssetSetupDriverForUi::getUiMotFile(GfAssetType type) {
  if (type == ASSET_TYPE_TEMPORARY) {
    DataParamAcc dataParamAcc(OBJECT_TYPE_DRIVER, id, GIMMICK_TYPE_NONE);
    const char *motion = getValidName(dataParamAcc.getMotionResourceName());
    static mm::mtl::FixStr<128> s_motion;
    s_motion.clear();
    s_motion.format("%s_%d", motion, UI_MOTION_NUMBER);
    return s_motion.c_str();
  }
  return nullptr;
}

const char *GfAssetSetupDriverForUi::getUiStpFile(GfAssetType type) {
  if (getAssetType() == type) {
    DataParamAcc dataParamAcc(OBJECT_TYPE_DRIVER, id, GIMMICK_TYPE_NONE);
    const char *motion = getValidName(dataParamAcc.getMotionResourceName());
    static mm::mtl::FixStr<128> s_stp;
    s_stp.clear();
    s_stp.format("%s_%d", motion, UI_MOTION_NUMBER);
    return s_stp.c_str();
  }
  return nullptr;
}

GfAssetSetupBlade::GfAssetSetupBlade() : useCondModel(false) {}

const char *GfAssetSetupBlade::getSwtFile(GfAssetType type) { return getRetargetMotFile(type); }

const char *GfAssetSetupBlade::getSePackFile() const {
  const char *sePack = GfDataBlade::getSePack(id);
  if (sePack == nullptr || *sePack == '\0') {
    sePack = nullptr;
  }
  return sePack;
}

u32 GfAssetSetupBlade::getFootStepId() const {
  DataParamAcc dataParamAcc(OBJECT_TYPE_BLADE, id, GIMMICK_TYPE_NONE);
  return dataParamAcc.getFootStep();
}

const char *GfAssetSetupBlade::getMdlFile(GfAssetType type) {
  RefResource *resource = getRefResource(getMdlSlot());
  if (resource != nullptr && !resource->name.empty()) {
    return resource->name.c_str();
  }
  const char *model = GfGameUtil::getBladeModel(id, false);
  if (model == nullptr || *model == '\0') {
    return nullptr;
  }
  return model;
}

const char *GfAssetSetupBlade::getArcFile(GfAssetType type) {
  RefResource *resource = getRefResource(getArcSlot());
  if (resource != nullptr && !resource->name.empty()) {
    return resource->name.c_str();
  }
  const char *model = GfGameUtil::getBladeModel(id, false);
  if (model == nullptr || *model == '\0') {
    return nullptr;
  }
  return model;
}

const char *GfAssetSetupBlade::getRetargetMotFile(GfAssetType type) {
  if (getAssetTypeMot() == type) {
    RefResource *resource = getRefResource(getMotSlot());
    if (resource != nullptr && !resource->name.empty()) {
      return resource->name.c_str();
    }
    const char *motion = GfGameUtil::getBladeMotion(id, false);
    if (motion == nullptr || *motion == '\0') {
      return nullptr;
    }
    return motion;
  }
  return nullptr;
}

const char *GfAssetSetupBlade::getEfpFile(GfAssetType type) { return getMdlFile(type); }

const char *GfAssetSetupBlade::getEabFile(GfAssetType type) {
  DataParamAcc dataParamAcc(OBJECT_TYPE_BLADE, id, GIMMICK_TYPE_NONE);
  return dataParamAcc.getEffectResourceName();
}

const char *GfAssetSetupBlade::getEfbFile(GfAssetType type) {
  if (getAssetTypeEfb() == type || type == ASSET_TYPE_TEMPORARY) {
    return getEabFile(type);
  }
  return nullptr;
}

const char *GfAssetSetupBlade::getStpFile(GfAssetType type) {
  if (getAssetType() == type) {
    DataParamAcc dataParamAcc(OBJECT_TYPE_BLADE, id, GIMMICK_TYPE_NONE);
    return getValidName(dataParamAcc.getMotionResourceName());
  }
  return nullptr;
}

const char *GfAssetSetupBlade::getPath() const { return GfAssetPath::getMdoModel(); }

bool GfAssetSetupBlade::makeAssetNameWpnType(mm::mtl::FixStr<128> &name, u32 blade, u32 weaponType) {
  name = "";
  mm::mtl::FixStr<128> anim;
  u32 creator = GfDataBlade::getCreator(blade);
  if (GfDataDriver::getDriverAddAnim(anim, creator == 0 ? 1 : creator, weaponType) && !anim.empty()) {
    makeAssetNamePrefix(name, ASSET_TYPE_WEAPON_MOTION, anim.c_str(), "");
    return true;
  }
  return false;
}

const char *GfAssetSetupEventBlade::getEvtMotFile(GfAssetType type) {
  if (getAssetTypeEventMot() == type) {
    RefResource *resource = getRefResource(getEvtMotSlot());
    if (resource != nullptr && !resource->name.empty()) {
      return resource->name.c_str();
    }
    const char *motion = GfGameUtil::getBladeMotion(id, !useCondModel);
    if (motion == nullptr || *motion == '\0') {
      return nullptr;
    }
    return motion;
  }
  return nullptr;
}

const char *GfAssetSetupEventBlade::getEvtStpFile(GfAssetType type) {
  if (getAssetType() == type) {
    DataParamAcc dataParamAcc(OBJECT_TYPE_BLADE, id, GIMMICK_TYPE_NONE);
    return getValidName(dataParamAcc.getMotionResourceName());
  }
  return nullptr;
}

const char *GfAssetSetupEventBlade::getEvtPath() const { return GfAssetPath::getEvt(); }

const char *GfAssetSetupEventBlade::getMdlFile(GfAssetType type) {
  RefResource *resource = getRefResource(getMdlSlot());
  if (resource != nullptr && !resource->name.empty()) {
    return resource->name.c_str();
  }
  const char *model = GfGameUtil::getBladeModel(id, !useCondModel);
  if (model == nullptr || *model == '\0') {
    return nullptr;
  }
  return model;
}

const char *GfAssetSetupEventBlade::getArcFile(GfAssetType type) {
  RefResource *resource = getRefResource(getArcSlot());
  if (resource != nullptr && !resource->name.empty()) {
    return resource->name.c_str();
  }
  const char *model = GfGameUtil::getBladeModel(id, !useCondModel);
  if (model == nullptr || *model == '\0') {
    return nullptr;
  }
  return model;
}

const char *GfAssetSetupEventBlade::getRetargetMotFile(GfAssetType type) {
  if (getAssetTypeMot() == type) {
    RefResource *resource = getRefResource(getMotSlot());
    if (resource != nullptr && !resource->name.empty()) {
      return resource->name.c_str();
    }
    const char *motion = GfGameUtil::getBladeMotion(id, !useCondModel);
    if (motion == nullptr || *motion == '\0') {
      return nullptr;
    }
    return motion;
  }
  return nullptr;
}

const char *GfAssetSetupBladeForUi::getUiMotFile(GfAssetType type) {
  if (getAssetTypeMot() == type) {
    DataParamAcc dataParamAcc(OBJECT_TYPE_BLADE, id, GIMMICK_TYPE_NONE);
    const char *motion = getValidName(dataParamAcc.getMotionResourceName());
    static mm::mtl::FixStr<128> s_motion;
    s_motion.clear();
    s_motion.format("%s_%d", motion, UI_MOTION_NUMBER);
    return s_motion.c_str();
  }
  return nullptr;
}

const char *GfAssetSetupBladeForUi::getUiStpFile(GfAssetType type) {
  if (getAssetType() == type) {
    DataParamAcc dataParamAcc(OBJECT_TYPE_BLADE, id, GIMMICK_TYPE_NONE);
    const char *motion = getValidName(dataParamAcc.getMotionResourceName());
    static mm::mtl::FixStr<128> s_stp;
    s_stp.clear();
    s_stp.format("%s_%d", motion, UI_MOTION_NUMBER);
    return s_stp.c_str();
  }
  return nullptr;
}

GfAssetSetupEnemy::GfAssetSetupEnemy() : initParamEnemy(nullptr) {}

void GfAssetSetupEnemy::makeEnemyEffectAssetName(mm::mtl::FixStr<128> &name, const GfInitParamEnemy &param, u32 attribute) {
  makeAssetNamePrefix(name, ASSET_TYPE_EFFECT, getEabFile(ASSET_TYPE_EFFECT), "");
  if (attribute != 0) {
    mm::mtl::FixStr<16> weaponName;
    if (GfDataBlade::getBladeWpnType(param.getBladeID()) != 0) {
      u32 weaponType = GfDataWeapon::getAsmWeaponType(GfDataBlade::getBladeWpnType(param.getBladeID()));
      if (weaponType >= 10) {
        weaponName.format("%d", weaponType);
      } else {
        weaponName.format("0%d", weaponType);
      }
      name += "_";
      name += weaponName.c_str();
    }
    name += "_";
    name += GfDataUtil::getAttributeFileName(attribute);
  }
}

u32 GfAssetSetupEnemy::getEnemyAttribute(const GfInitParamEnemy &param) {
  u32 attribute = GfBdatChrEnArrange::get()->getChrEnArrangeBladeAtr(param.getEnArrangeID());
  u32 blade = param.getBladeID();
  if (attribute != 0) {
    return attribute;
  }

  if (GfDataBlade::getCommonBladeName(getMdlFile(getAssetType())) ||
      GfBdatChrEnArrange::get()->getChrEnArrangeDriverLev(param.getEnArrangeID()) != 0) {
    attribute = GfDataBlade::getAttribute(blade);
    if (attribute != 0) {
      return attribute;
    }
  }

  if (!GfDataHana::isValid(param.getBladeID())) {
    return 0;
  }

  attribute = GfDataBlade::getAttribute(blade);
  if (attribute == 0) {
    if (blade == BLADE_HANA_JS) {
      attribute = HANA_JS_ATTRIBUTE;
    } else if (blade == BLADE_HANA_JK) {
      attribute = HANA_JK_ATTRIBUTE;
    } else if (blade == BLADE_HANA_JD) {
      attribute = HANA_JD_ATTRIBUTE;
    }
  }
  return attribute;
}

void GfAssetSetupEnemy::getEnemyEabFileName(mm::mtl::FixStr<128> &name, const GfInitParamEnemy &param, GfAssetType type) {
  const char *eab = getEabFile(type);
  if (eab != nullptr && strstr(eab, "en/") != nullptr) {
    name.format("%s%s%s", getEffPath(), eab, ".wieab");
    return;
  }

  u32 blade = param.getBladeID();
  if (!GfDataBlade::isRegularBlade(blade) || param.characterType == CHARACTER_TYPE_ENEMY_BLADE || GfDataHana::isValid(blade)) {
    name.format("%s%s%s%s", getEffPath(), eab, GfDataBlade::getBaseEabWeaponName(blade), ".wieab");
  } else {
    name.format("%s%s%s%s", getEffPath(), eab, GfDataBlade::getBaseEfbWeaponName(blade), ".wieab");
  }
}

void GfAssetSetupEnemy::getEnemyEfbFileName(mm::mtl::FixStr<128> &name, const GfInitParamEnemy &param, GfAssetType type, u32 attribute) {
  u32 blade = param.getBladeID();
  const char *efb = getEfbFile(type);
  if ((efb == nullptr || strstr(efb, "en/") == nullptr) &&
      (!GfDataBlade::isRegularBlade(blade) || param.characterType != CHARACTER_TYPE_ENEMY_BLADE || GfDataHana::isValid(blade))) {
    u32 baseAttribute = blade == BLADE_SAIKA ? 0 : attribute;
    name.format("%s%s%s%s%s",
                getEffPath(),
                efb,
                GfDataBlade::getBaseEfbWeaponName(blade),
                GfDataBlade::getBaseEfbAttributeName(blade, baseAttribute),
                ".wiefb");
    return;
  }

  name.format("%s%s%s", getEffPath(), efb, ".wiefb");
}

const char *GfAssetSetupEnemy::getSwtFile(GfAssetType type) { return getRetargetMotFile(type); }

bool GfAssetSetupEnemy::makeAssetNameWpnType(mm::mtl::FixStr<128> &name, u32 driver, u32 number) {
  name = "";
  mm::mtl::FixStr<128> anim;
  if (GfDataEnemy::getDriverAddAnim(anim, driver, number) && !anim.empty()) {
    makeAssetNamePrefix(name, ASSET_TYPE_WEAPON_MOTION, anim.c_str(), "en");
    return true;
  }
  return false;
}

const char *GfAssetSetupEnemy::getSePackFile() const {
  const char *sePack = GfDataEnemy::getSePack(id);
  if (sePack == nullptr || *sePack == '\0') {
    sePack = nullptr;
  }
  return sePack;
}

u32 GfAssetSetupEnemy::getFootStepId() const {
  DataParamAcc dataParamAcc(OBJECT_TYPE_ENEMY, initParamEnemy->getEnArrangeID(), GIMMICK_TYPE_NONE);
  return dataParamAcc.getFootStep();
}

const char *GfAssetSetupEnemy::getMdlFile(GfAssetType type) {
  RefResource *resource = getRefResource(getMdlSlot());
  if (resource != nullptr && !resource->name.empty()) {
    return resource->name.c_str();
  }
  return getValidName(getRscValue(this, BDAT_RSC_EN, "Model"));
}

const char *GfAssetSetupEnemy::getArcFile(GfAssetType type) {
  if (getAssetTypeArc() == type) {
    return getMdlFile(type);
  }
  return nullptr;
}

const char *GfAssetSetupEnemy::getMotFile(GfAssetType type) {
  if (getAssetTypeMot() == type) {
    RefResource *resource = getRefResource(getMotSlot());
    if (resource != nullptr && !resource->name.empty()) {
      return resource->name.c_str();
    }
    return getValidName(getRscValue(this, BDAT_RSC_EN, "Model"));
  }
  return nullptr;
}

const char *GfAssetSetupEnemy::getRetargetMotFile(GfAssetType type) {
  if (getAssetTypeMot() == type) {
    RefResource *resource = getRefResource(getMotSlot());
    if (resource != nullptr && !resource->name.empty()) {
      return resource->name.c_str();
    }
    return getValidName(getRscValue(this, BDAT_RSC_EN, "Motion"));
  }
  return nullptr;
}

const char *GfAssetSetupEnemy::getEfpFile(GfAssetType type) { return getMdlFile(type); }

const char *GfAssetSetupEnemy::getEabFile(GfAssetType type) {
  if (type == ASSET_TYPE_EFFECT) {
    const char *effect = GfBdatRsc::get()->getRscEnComp_Eff(id);
    if (effect == nullptr || *effect == '\0') {
      effect = GfBdatRsc::get()->getRscEnEffectPack(id);
      if (effect == nullptr || *effect == '\0') {
        return getEfpFile(ASSET_TYPE_EFFECT);
      }
    }
    return effect;
  }
  return nullptr;
}

const char *GfAssetSetupEnemy::getEfbFile(GfAssetType type) {
  if (type == ASSET_TYPE_EFFECT) {
    return getEabFile(ASSET_TYPE_EFFECT);
  }
  return nullptr;
}

const char *GfAssetSetupEnemy::getStpFile(GfAssetType type) {
  if (getAssetType() == type) {
    return getValidName(getRscValue(this, BDAT_RSC_EN, "Motion"));
  }
  return nullptr;
}

const char *GfAssetSetupEnemy::getPath() const { return "/model/"; }

GfAssetSetupEnemyBlade::GfAssetSetupEnemyBlade() {}

const char *GfAssetSetupEnemyBlade::getMdlFile(GfAssetType type) {
  RefResource *resource = getRefResource(getMdlSlot());
  if (resource != nullptr && !resource->name.empty()) {
    return resource->name.c_str();
  }
  return GfDataBlade::getResourceNameModel(initParamEnemy->bladeId);
}

const char *GfAssetSetupEnemyBlade::getMotFile(GfAssetType type) {
  if (getAssetTypeMot() != type) {
    return nullptr;
  }
  RefResource *resource = getRefResource(getMotSlot());
  if (resource != nullptr && !resource->name.empty()) {
    return resource->name.c_str();
  }
  return GfDataBlade::getResourceNameMotion(initParamEnemy->bladeId);
}

const char *GfAssetSetupEnemyBlade::getRetargetMotFile(GfAssetType type) {
  if (getAssetTypeMot() != type) {
    return nullptr;
  }
  RefResource *resource = getRefResource(getMotSlot());
  if (resource != nullptr && !resource->name.empty()) {
    return resource->name.c_str();
  }
  return GfDataBlade::getResourceNameMotion(initParamEnemy->bladeId);
}

const char *GfAssetSetupEnemyBlade::getPath() const { return GfAssetPath::getMdoModel(); }

void GfAssetSetupEventEnemy::setup(GF_ASSET_HANDLE *handle, const GfInitParamEnemy &param) {
  initParamEnemy = &param;
  setupParam(handle, param);
  if (!checkValidResource()) {
    return;
  }

  mm::mtl::FixStr<128> name;
  GfAssetFilesInfo info;
  info.handle = handle;
  info.assetType = getAssetType();
  info.name = name.c_str();
  info.priority = param.priority;
  info.assetType = getAssetType();
  info.backupAssetTypes.clear();
  info.backupAssetTypes.push(ASSET_TYPE_TEMPORARY);
  makeAssetNamePrefix(name, info.assetType, getMdlFile(info.assetType), "Mdl");
  GfAssetPack *corePack = GfAssetManager::createAssetFiles(info);
  requestCoreResource(corePack, handle);

  info.assetType = getAssetTypeArc();
  info.backupAssetTypes.clear();
  info.backupAssetTypes.push(ASSET_TYPE_TEMPORARY);
  if (const char *arc = getArcFile(info.assetType)) {
    makeAssetNamePrefix(name, info.assetType, arc, "EV");
    GfAssetPack *pack = GfAssetManager::createAssetFiles(info);
    if (!setupReference(pack, name.c_str(), getArcSlot())) {
      mm::mtl::FixStr<128> path;
      path.format("%s%s%s", getPath(), arc, ".arc");
      pack->files.addResource(getArcSlot(), path.c_str());
    }
  }

  info.assetType = getAssetTypeMot();
  info.backupAssetTypes.clear();
  info.backupAssetTypes.push(ASSET_TYPE_TEMPORARY);
  if (const char *motion = getRetargetMotFile(info.assetType)) {
    makeAssetNamePrefix(name, info.assetType, motion, "Mot");
    GfAssetPack *pack = GfAssetManager::createAssetFiles(info);
    if (!setupReference(pack, name.c_str(), getRetargetMotSlot())) {
      GfAssetManager::setMotionInfo(handle, motion);
      mm::mtl::FixStr<128> path;
      path.format("%s%s%s", getPath(), motion, ".mot");
      pack->files.addResource(getRetargetMotSlot(), path.c_str());
    }
  }

  const char *retargetMotion = getRetargetMotFile(info.assetType);
  const char *addMotion = GfDataEnemy::getAddMotionName(id);
  info.backupAssetTypes.clear();
  info.backupAssetTypes.push(ASSET_TYPE_TEMPORARY);
  if (retargetMotion != nullptr && addMotion != nullptr && strcmp(retargetMotion, addMotion) != 0) {
    makeAssetNamePrefix(name, info.assetType, addMotion, "Mot");
    GfAssetPack *pack = GfAssetManager::createAssetFiles(info);
    mm::mtl::FixStr<128> path;
    path.format("%s%s%s", getPath(), addMotion, ".mot");
    pack->files.addResource(getMotSlot(), path.c_str());
  }

  info.assetType = ASSET_TYPE_TEMPORARY;
  info.backupAssetTypes.clear();
  info.backupAssetTypes.push(ASSET_TYPE_ENEMY_MOTION);
  if (const char *eventMotion = getEvtMotFile(ASSET_TYPE_BASE)) {
    makeAssetNamePrefix(name, info.assetType, eventMotion, "Evt");
    GfAssetPack *pack = GfAssetManager::createAssetFiles(info);
    if (!setupReference(pack, name.c_str(), getEvtMotSlot())) {
      mm::mtl::FixStr<128> path;
      path.format("%s%s%s", getEvtPath(), eventMotion, ".mot");
      pack->files.addResource(getEvtMotSlot(), path.c_str());
      if (const char *eventAddMotion = GfDataEnemy::getAddMotionName(id)) {
        makeAssetNamePrefix(name, info.assetType, eventAddMotion, "Evt");
        GfAssetPack *addPack = GfAssetManager::createAssetFiles(info);
        path.format("%s%s%s", getEvtPath(), eventAddMotion, ".mot");
        addPack->files.addResource(getAddMotSlot(), path.c_str());
      }
    }
  }

  info.assetType = ASSET_TYPE_EFFECT;
  info.backupAssetTypes.clear();
  if (const char *eab = getEabFile(info.assetType)) {
    makeAssetNamePrefix(name, info.assetType, eab, "Eff");
    GfAssetPack *pack = GfAssetManager::createAssetFiles(info);
    if (!setupReference(pack, name.c_str(), getEabSlot())) {
      mm::mtl::FixStr<128> path;
      path.format("%s%s%s", getEffPath(), eab, ".wieab");
      pack->files.addResource(getEabSlot(), path.c_str());
    }
    if (const char *efb = getEfbFile(info.assetType)) {
      if (!setupReference(pack, name.c_str(), getEfbSlot())) {
        mm::mtl::FixStr<128> path;
        path.format("%s%s%s", getEffPath(), efb, ".wiefb");
        pack->files.addResource(getEfbSlot(), path.c_str());
      }
    }
  }

  requestFootStepSePackFile(info, getFootStepId(), FOOT_STEP_SE_FILE_INDEX, FOOT_STEP_SE_SUB_FILE_INDEX);
}

const char *GfAssetSetupEventEnemy::getEvtMotFile(GfAssetType type) {
  if (type == ASSET_TYPE_BASE) {
    RefResource *resource = getRefResource(getEvtMotSlot());
    if (resource != nullptr && !resource->name.empty()) {
      return resource->name.c_str();
    }
    return getValidName(getRscValue(this, BDAT_RSC_EN, "Motion"));
  }
  return nullptr;
}

const char *GfAssetSetupEventEnemy::getEvtStpFile(GfAssetType type) {
  if (getAssetType() == type) {
    return getValidName(getRscValue(this, BDAT_RSC_EN, "Model"));
  }
  return nullptr;
}

const char *GfAssetSetupEventEnemy::getEvtPath() const { return GfAssetPath::getEvt(); }

GfAssetSetupNpc::GfAssetSetupNpc() {}

void GfAssetSetupNpc::setup(GF_ASSET_HANDLE *handle, const GfInitParamNpc &param) {
  setupParam(handle, param);
  if (!checkValidResource()) {
    return;
  }

  mm::mtl::FixStr<128> name;
  GfAssetFilesInfo info;
  info.handle = handle;
  info.assetType = getAssetType();
  info.name = name.c_str();
  info.priority = param.priority;
  info.assetType = getAssetType();
  info.backupAssetTypes.clear();
  info.backupAssetTypes.push(ASSET_TYPE_TEMPORARY);
  makeAssetNamePrefix(name, info.assetType, getMdlFile(info.assetType), "");
  GfAssetPack *corePack = GfAssetManager::createAssetFiles(info);
  requestCoreResource(corePack, handle);

  info.assetType = getAssetTypeArc();
  info.backupAssetTypes.clear();
  info.backupAssetTypes.push(ASSET_TYPE_TEMPORARY);
  if (const char *arc = getArcFile(info.assetType)) {
    makeAssetNamePrefix(name, info.assetType, arc, "NP");
    GfAssetPack *pack = GfAssetManager::createAssetFiles(info);
    if (!setupReference(pack, name.c_str(), getArcSlot())) {
      mm::mtl::FixStr<128> path;
      path.format("%s%s%s", getPath(), arc, ".arc");
      pack->files.addResource(getArcSlot(), path.c_str());
    }
  }

  info.assetType = getAssetTypeMot();
  if (const char *motion = getRetargetMotFile(info.assetType)) {
    GfAssetType motionType = makeMotionAssetName(name, info.assetType, motion);
    info.assetType = motionType;
    info.backupAssetTypes.clear();
    info.backupAssetTypes.push(ASSET_TYPE_TEMPORARY);
    GfAssetPack *pack = GfAssetManager::createAssetFiles(info);
    if (!setupReference(pack, name.c_str(), getRetargetMotSlot())) {
      GfAssetManager::setMotionInfo(handle, motion);
      mm::mtl::FixStr<128> path;
      path.format("%s%s%s", getPath(), motion, ".mot");
      pack->files.addResource(getRetargetMotSlot(), path.c_str());
    }
  }

  info.assetType = getAssetTypeMot();
  const char *retargetMotion = getRetargetMotFile(info.assetType);
  const char *addMotion = GfDataNpc::getAddMotionName(id);
  if (retargetMotion != nullptr && addMotion != nullptr && strcmp(retargetMotion, addMotion) != 0) {
    info.assetType = makeMotionAssetName(name, info.assetType, addMotion);
    GfAssetType motionType = makeMotionAssetName(name, info.assetType, addMotion);
    info.assetType = motionType;
    info.backupAssetTypes.clear();
    info.backupAssetTypes.push(ASSET_TYPE_TEMPORARY);
    GfAssetPack *pack = GfAssetManager::createAssetFiles(info);
    mm::mtl::FixStr<128> path;
    path.format("%s%s%s", getPath(), addMotion, ".mot");
    pack->files.addResource(getMotSlot(), path.c_str());
  }

  if (strstr(getMdlFile(info.assetType), NPC_EVENT_MODEL) != nullptr) {
    info.assetType = ASSET_TYPE_TEMPORARY;
    info.backupAssetTypes.clear();
    if (const char *eventMotion = getEvtMotFile(ASSET_TYPE_BASE)) {
      makeAssetNamePrefix(name, info.assetType, eventMotion, "Evt");
      GfAssetPack *pack = GfAssetManager::createAssetFiles(info);
      if (!setupReference(pack, name.c_str(), getEvtMotSlot())) {
        mm::mtl::FixStr<128> path;
        path.format("%s%s%s", getEvtPath(), eventMotion, ".mot");
        pack->files.addResource(getEvtMotSlot(), path.c_str());
        if (const char *eventAddMotion = GfDataNpc::getAddMotionName(id)) {
          path.format("%s%s%s", getEvtPath(), eventAddMotion, ".mot");
          pack->files.addResource(ADD_MOTION_FILE_INDEX, path.c_str());
        }
      }
    }
  }

  info.assetType = ASSET_TYPE_EFFECT;
  info.backupAssetTypes.clear();
  if (const char *eab = getEabFile(info.assetType)) {
    makeAssetNamePrefix(name, info.assetType, eab, "");
    GfAssetPack *pack = GfAssetManager::createAssetFiles(info);
    if (!setupReference(pack, name.c_str(), getEabSlot())) {
      mm::mtl::FixStr<128> path;
      path.format("%s%s%s", getEffPath(), eab, ".wieab");
      pack->files.addResource(getEabSlot(), path.c_str());
    }
    if (const char *efb = getEfbFile(info.assetType)) {
      if (!setupReference(pack, name.c_str(), getEfbSlot())) {
        mm::mtl::FixStr<128> path;
        path.format("%s%s%s", getEffPath(), efb, ".wiefb");
        pack->files.addResource(getEfbSlot(), path.c_str());
      }
    }
  }

  requestFootStepSePackFile(info, getFootStepId(), FOOT_STEP_SE_FILE_INDEX, FOOT_STEP_SE_SUB_FILE_INDEX);
}

u32 GfAssetSetupNpc::getFootStepId() const {
  DataParamAcc dataParamAcc(OBJECT_TYPE_NPC, id, GIMMICK_TYPE_NONE);
  return dataParamAcc.getFootStep();
}

const char *GfAssetSetupNpc::getMdlFile(GfAssetType type) {
  RefResource *resource = getRefResource(getMdlSlot());
  if (resource != nullptr && !resource->name.empty()) {
    return resource->name.c_str();
  }
  const char *model = GfDataNpc::getModelName(id);
  if (model == nullptr || *model == '\0') {
    return nullptr;
  }
  return model;
}

const char *GfAssetSetupNpc::getArcFile(GfAssetType type) {
  if (getAssetTypeArc() == type) {
    return getMdlFile(type);
  }
  return nullptr;
}

const char *GfAssetSetupNpc::getMotFile(GfAssetType type) {
  if (getAssetTypeMot() == type) {
    RefResource *resource = getRefResource(getMotSlot());
    if (resource != nullptr && !resource->name.empty()) {
      return resource->name.c_str();
    }
    const char *motion = GfDataNpc::getMotionName(id);
    if (motion == nullptr || *motion == '\0') {
      return nullptr;
    }
    return motion;
  }
  return nullptr;
}

const char *GfAssetSetupNpc::getEfpFile(GfAssetType type) { return getMdlFile(type); }

const char *GfAssetSetupNpc::getRetargetMotFile(GfAssetType type) {
  if (getAssetTypeMot() == type) {
    RefResource *resource = getRefResource(getMotSlot());
    if (resource != nullptr && !resource->name.empty()) {
      return resource->name.c_str();
    }
    const char *motion = GfDataNpc::getMotionName(id);
    if (motion == nullptr || *motion == '\0') {
      return nullptr;
    }
    return motion;
  }
  return nullptr;
}

const char *GfAssetSetupNpc::getStpFile(GfAssetType type) {
  if (getAssetType() == type) {
    return getValidName(GfDataNpc::getMotionName(id));
  }
  return nullptr;
}

const char *GfAssetSetupNpc::getPath() const { return "/model/"; }

const char *GfAssetSetupNpc::getEvtMotFile(GfAssetType type) {
  if (type == ASSET_TYPE_BASE && GfDataNpc::isNeedResourceEvent(id)) {
    RefResource *resource = getRefResource(getEvtMotSlot());
    if (resource != nullptr && !resource->name.empty()) {
      return resource->name.c_str();
    }
    const char *motion = GfDataNpc::getMotionName(id);
    if (motion == nullptr || *motion == '\0') {
      return nullptr;
    }
    return motion;
  }
  return nullptr;
}

const char *GfAssetSetupNpc::getEabFile(GfAssetType type) {
  if (type == ASSET_TYPE_EFFECT) {
    return GfDataNpc::getEffectName(id);
  }
  return nullptr;
}

const char *GfAssetSetupNpc::getEfbFile(GfAssetType type) { return getEabFile(type); }

const char *GfAssetSetupNpc::getEvtPath() const { return GfAssetPath::getEvt(); }

void GfAssetSetupEventNpc::setup(GF_ASSET_HANDLE *handle, const GfInitParamNpc &param) {
  setupParam(handle, param);
  if (!checkValidResource()) {
    return;
  }

  mm::mtl::FixStr<128> name;
  GfAssetFilesInfo info;
  info.handle = handle;
  info.name = name.c_str();
  info.priority = param.priority;
  info.assetType = getAssetType();
  info.backupAssetTypes.clear();
  info.backupAssetTypes.push(ASSET_TYPE_TEMPORARY);
  info.backupAssetTypes.push(ASSET_TYPE_ENEMY_MOTION);
  makeAssetNamePrefix(name, info.assetType, getMdlFile(info.assetType), "Mdl");
  GfAssetPack *corePack = GfAssetManager::createAssetFiles(info);
  requestCoreResource(corePack, handle);

  info.assetType = getAssetTypeArc();
  info.backupAssetTypes.clear();
  info.backupAssetTypes.push(ASSET_TYPE_TEMPORARY);
  info.backupAssetTypes.push(ASSET_TYPE_ENEMY_MOTION);
  if (const char *arc = getArcFile(info.assetType)) {
    makeAssetNamePrefix(name, info.assetType, arc, "EV");
    GfAssetPack *pack = GfAssetManager::createAssetFiles(info);
    if (!setupReference(pack, name.c_str(), getArcSlot())) {
      mm::mtl::FixStr<128> path;
      path.format("%s%s%s", getPath(), arc, ".arc");
      pack->files.addResource(getArcSlot(), path.c_str());
    }
  }

  info.assetType = getAssetTypeMot();
  info.backupAssetTypes.clear();
  info.backupAssetTypes.push(ASSET_TYPE_ENEMY_MOTION);
  if (const char *motion = getRetargetMotFile(info.assetType)) {
    makeAssetNamePrefix(name, info.assetType, motion, "Mot");
    GfAssetPack *pack = GfAssetManager::createAssetFiles(info);
    if (!setupReference(pack, name.c_str(), getRetargetMotSlot())) {
      GfAssetManager::setMotionInfo(handle, motion);
      mm::mtl::FixStr<128> path;
      path.format("%s%s%s", getPath(), motion, ".mot");
      pack->files.addResource(getRetargetMotSlot(), path.c_str());
    }
  }

  const char *retargetMotion = getRetargetMotFile(info.assetType);
  const char *addMotion = GfDataNpc::getAddMotionName(id);
  if (retargetMotion != nullptr && addMotion != nullptr && strcmp(retargetMotion, addMotion) != 0) {
    makeAssetNamePrefix(name, info.assetType, addMotion, "Mot");
    GfAssetPack *pack = GfAssetManager::createAssetFiles(info);
    mm::mtl::FixStr<128> path;
    path.format("%s%s%s", getPath(), addMotion, ".mot");
    pack->files.addResource(getMotSlot(), path.c_str());
  }

  info.assetType = ASSET_TYPE_TEMPORARY;
  info.backupAssetTypes.clear();
  info.backupAssetTypes.push(ASSET_TYPE_ENEMY_MOTION);
  if (const char *eventMotion = getEvtMotFile(ASSET_TYPE_BASE)) {
    makeAssetNamePrefix(name, info.assetType, eventMotion, "Evt");
    GfAssetPack *pack = GfAssetManager::createAssetFiles(info);
    if (!setupReference(pack, name.c_str(), getEvtMotSlot())) {
      mm::mtl::FixStr<128> path;
      path.format("%s%s%s", getEvtPath(), eventMotion, ".mot");
      pack->files.addResource(getEvtMotSlot(), path.c_str());
      if (const char *eventAddMotion = GfDataNpc::getAddMotionName(id)) {
        makeAssetNamePrefix(name, info.assetType, eventAddMotion, "Evt");
        GfAssetPack *addPack = GfAssetManager::createAssetFiles(info);
        path.format("%s%s%s", getEvtPath(), eventAddMotion, ".mot");
        addPack->files.addResource(ADD_MOTION_FILE_INDEX, path.c_str());
      }
    }
  }

  info.assetType = ASSET_TYPE_EFFECT;
  info.backupAssetTypes.clear();
  if (const char *eab = getEabFile(info.assetType)) {
    makeAssetNamePrefix(name, info.assetType, eab, "Eff");
    GfAssetPack *pack = GfAssetManager::createAssetFiles(info);
    if (!setupReference(pack, name.c_str(), getEabSlot())) {
      mm::mtl::FixStr<128> path;
      path.format("%s%s%s", getEffPath(), eab, ".wieab");
      pack->files.addResource(getEabSlot(), path.c_str());
    }
    if (const char *efb = getEfbFile(info.assetType)) {
      if (!setupReference(pack, name.c_str(), getEfbSlot())) {
        mm::mtl::FixStr<128> path;
        path.format("%s%s%s", getEffPath(), efb, ".wiefb");
        pack->files.addResource(getEfbSlot(), path.c_str());
      }
    }
  }

  requestFootStepSePackFile(info, getFootStepId(), FOOT_STEP_SE_FILE_INDEX, FOOT_STEP_SE_SUB_FILE_INDEX);
}

const char *GfAssetSetupEventNpc::getMotFile(GfAssetType type) {
  if (type == ASSET_TYPE_BASE) {
    RefResource *resource = getRefResource(getMotSlot());
    if (resource != nullptr && !resource->name.empty()) {
      return resource->name.c_str();
    }
    const char *motion = GfDataNpc::getMotionName(id);
    if (motion == nullptr || *motion == '\0') {
      return nullptr;
    }
    return motion;
  }
  return nullptr;
}

const char *GfAssetSetupEventNpc::getEvtMotFile(GfAssetType type) {
  if (type == ASSET_TYPE_BASE) {
    RefResource *resource = getRefResource(getEvtMotSlot());
    if (resource != nullptr && !resource->name.empty()) {
      return resource->name.c_str();
    }
    const char *motion = GfDataNpc::getMotionName(id);
    if (motion == nullptr || *motion == '\0') {
      return nullptr;
    }
    return motion;
  }
  return nullptr;
}

const char *GfAssetSetupEventNpc::getEvtStpFile(GfAssetType type) {
  if (getAssetType() == type) {
    return getValidName(GfDataNpc::getMotionName(id));
  }
  return nullptr;
}

GfAssetSetupMob::GfAssetSetupMob() {}

void GfAssetSetupMob::setup(GF_ASSET_HANDLE *handle, const GfInitParamMob &param) {
  setupParam(handle, param);
  if (!checkValidResource()) {
    return;
  }

  mm::mtl::FixStr<128> name;
  GfAssetFilesInfo info;
  info.handle = handle;
  info.assetType = getAssetType();
  info.name = name.c_str();
  info.priority = param.priority;
  makeAssetNamePrefix(name, info.assetType, getMdlFile(info.assetType), "Mdl");
  GfAssetPack *corePack = GfAssetManager::createAssetFiles(info);
  requestCoreResource(corePack, handle);

  info.assetType = ASSET_TYPE_BASE;
  if (const char *motion = getRetargetMotFile(ASSET_TYPE_BASE)) {
    GfAssetType motionType = makeMotionAssetName(name, ASSET_TYPE_MAP_OBJECT, motion);
    info.assetType = motionType;
    GfAssetPack *pack = GfAssetManager::createAssetFiles(info);
    if (!setupReference(pack, name.c_str(), getRetargetMotSlot())) {
      GfAssetManager::setMotionInfo(handle, motion);
      mm::mtl::FixStr<128> path;
      path.format("%s%s%s", getPath(), motion, ".mot");
      pack->files.addResource(getRetargetMotSlot(), path.c_str());
    }
  }

  const char *retargetMotion = getRetargetMotFile(ASSET_TYPE_BASE);
  const char *addMotion = GfDataMob::getAddMotionName(id);
  if (retargetMotion != nullptr && addMotion != nullptr && strcmp(retargetMotion, addMotion) != 0) {
    GfAssetType motionType = makeMotionAssetName(name, ASSET_TYPE_MAP_OBJECT, addMotion);
    info.assetType = motionType;
    GfAssetPack *pack = GfAssetManager::createAssetFiles(info);
    mm::mtl::FixStr<128> path;
    path.format("%s%s%s", getPath(), addMotion, ".mot");
    pack->files.addResource(getMotSlot(), path.c_str());
  }

  requestFootStepSePackFile(info, getFootStepId(), FOOT_STEP_SE_FILE_INDEX, FOOT_STEP_SE_SUB_FILE_INDEX);
}

u32 GfAssetSetupMob::getFootStepId() const {
  DataParamAcc dataParamAcc(OBJECT_TYPE_MOB, id, GIMMICK_TYPE_NONE);
  return dataParamAcc.getFootStep();
}

const char *GfAssetSetupMob::getMdlFile(GfAssetType type) {
  RefResource *resource = getRefResource(getMdlSlot());
  if (resource != nullptr && !resource->name.empty()) {
    return resource->name.c_str();
  }
  return getValidName(getRscValue(this, BDAT_RSC_MOB_LIST, "Model"));
}

const char *GfAssetSetupMob::getArcFile(GfAssetType type) { return getMdlFile(type); }

const char *GfAssetSetupMob::getMotFile(GfAssetType type) {
  if (type == ASSET_TYPE_BASE) {
    RefResource *resource = getRefResource(getMotSlot());
    if (resource != nullptr && !resource->name.empty()) {
      return resource->name.c_str();
    }
    return getValidName(getRscValue(this, BDAT_RSC_MOB_LIST, "Motion"));
  }
  return nullptr;
}

const char *GfAssetSetupMob::getRetargetMotFile(GfAssetType type) {
  if (type == ASSET_TYPE_BASE) {
    RefResource *resource = getRefResource(getMotSlot());
    if (resource != nullptr && !resource->name.empty()) {
      return resource->name.c_str();
    }
    const char *motion = GfDataMob::getMotionName(id);
    if (motion == nullptr || *motion == '\0') {
      return nullptr;
    }
    return motion;
  }
  return nullptr;
}

const char *GfAssetSetupMob::getStpFile(GfAssetType type) { return nullptr; }

const char *GfAssetSetupMob::getPath() const { return "/model/"; }

const char *GfAssetSetupMob::getEfpFile(GfAssetType type) { return getMdlFile(type); }

const char *GfAssetSetupMob::getEabFile(GfAssetType type) {
  if (getAssetType() == type) {
    return GfDataMob::getEffectName(id);
  }
  return nullptr;
}

const char *GfAssetSetupMob::getEfbFile(GfAssetType type) { return getEabFile(type); }

void GfAssetSetupEventMob::setup(GF_ASSET_HANDLE *handle, const GfInitParamMob &param) {
  setupParam(handle, param);
  if (!checkValidResource()) {
    return;
  }

  mm::mtl::FixStr<128> name;
  GfAssetFilesInfo info;
  info.handle = handle;
  info.assetType = getAssetType();
  info.name = name.c_str();
  info.priority = param.priority;
  makeAssetNamePrefix(name, info.assetType, getMdlFile(info.assetType), "Mdl");
  GfAssetPack *corePack = GfAssetManager::createAssetFiles(info);
  requestCoreResource(corePack, handle);

  if (const char *motion = getMdlFile(ASSET_TYPE_BASE)) {
    info.assetType = ASSET_TYPE_TEMPORARY;
    makeAssetNamePrefix(name, info.assetType, motion, "Mot");
    GfAssetPack *pack = GfAssetManager::createAssetFiles(info);
    if (!setupReference(pack, name.c_str(), getRetargetMotSlot())) {
      GfAssetManager::setMotionInfo(handle, motion);
      mm::mtl::FixStr<128> path;
      path.format("%s%s%s", getEvtPath(), motion, ".mot");
      pack->files.addResource(getRetargetMotSlot(), path.c_str());
    }
  }

  if (const char *motion = getMdlFile(ASSET_TYPE_BASE)) {
    info.assetType = ASSET_TYPE_TEMPORARY;
    makeAssetNamePrefix(name, info.assetType, motion, "Mot");
    GfAssetPack *pack = GfAssetManager::createAssetFiles(info);
    if (!setupReference(pack, name.c_str(), getMotSlot())) {
      mm::mtl::FixStr<128> path;
      path.format("%s%s%s", getPath(), motion, ".mot");
      pack->files.addResource(getMotSlot(), path.c_str());
    }
  }

  if (strcmp(getMdlFile(ASSET_TYPE_BASE), getMotFile(ASSET_TYPE_BASE)) != 0) {
    const char *motion = getMotFile(ASSET_TYPE_BASE);
    info.assetType = ASSET_TYPE_TEMPORARY;
    makeAssetNamePrefix(name, info.assetType, motion, "Mot");
    GfAssetPack *pack = GfAssetManager::createAssetFiles(info);
    if (!setupReference(pack, name.c_str(), ADD_MOTION_FILE_INDEX)) {
      mm::mtl::FixStr<128> path;
      path.format("%s%s%s", getPath(), motion, ".mot");
      pack->files.addResource(ADD_MOTION_FILE_INDEX, path.c_str());
    }
  }

  requestFootStepSePackFile(info, getFootStepId(), FOOT_STEP_SE_FILE_INDEX, FOOT_STEP_SE_SUB_FILE_INDEX);
}

const char *GfAssetSetupEventMob::getEvtStpFile(GfAssetType type) {
  if (getAssetType() == type) {
    return getValidName(getRscValue(this, BDAT_RSC_MOB_LIST, "Motion"));
  }
  return nullptr;
}

const char *GfAssetSetupEventMob::getEvtPath() const { return "/event/"; }

GfAssetSetupGimmick::GfAssetSetupGimmick() : gimmickType(0) {}

void GfAssetSetupGimmick::setup(GF_ASSET_HANDLE *handle, const GfInitParamGimmick &param) {
  setupParam(handle, param);
  gimmickType = param.gimmickType;
  if (!checkValidResource()) {
    return;
  }

  mm::mtl::FixStr<128> name;
  GfAssetFilesInfo info;
  info.handle = handle;
  info.name = name.c_str();
  info.priority = param.priority;
  makeAssetNamePrefix(name, getAssetType(), getMdlFile(getAssetType()), "");
  info.assetType = getAssetType();
  info.name = name.c_str();
  GfAssetPack *corePack = GfAssetManager::createAssetFiles(info);
  requestCoreResource(corePack, handle);

  info.name = name.c_str();
  info.assetType = ASSET_TYPE_OPTION;
  if (const char *motion = getMotFile(info.assetType)) {
    const char *efbName = getEfbFile(info.assetType);
    makeAssetNamePrefix(name, info.assetType, motion, efbName);
    GfAssetPack *pack = GfAssetManager::createAssetFiles(info);
    if (!setupReference(pack, name.c_str(), getMotSlot())) {
      GfAssetManager::setMotionInfo(handle, motion);
      mm::mtl::FixStr<128> path;
      path.format("%s%s%s", getPath(), motion, ".mot");
      pack->files.addResource(getMotSlot(), path.c_str());
    }
    if (const char *efb = getEfbFile(info.assetType)) {
      mm::mtl::FixStr<128> path;
      path.format("%s%s%s", getEffPath(), efb, ".wiefb");
      pack->files.addResource(getEfbSlot(), path.c_str());
    }
  }

  info.assetType = ASSET_TYPE_TEMPORARY;
  const char *eventMotion = getEvtMotFile(info.assetType);
  if (eventMotion == nullptr) {
    return;
  }
  makeAssetNamePrefix(name, info.assetType, eventMotion, "Evt");
  GfAssetPack *pack = GfAssetManager::createAssetFiles(info);
  if (setupReference(pack, name.c_str(), getEvtMotSlot())) {
    return;
  }
  mm::mtl::FixStr<128> path;
  path.format("%s%s%s", getEvtPath(), eventMotion, ".mot");
  pack->files.addResource(getEvtMotSlot(), path.c_str());
}

const char *GfAssetSetupGimmick::getMdlFile(GfAssetType type) {
  RefResource *resource = getRefResource(getMdlSlot());
  if (resource != nullptr && !resource->name.empty()) {
    return resource->name.c_str();
  }
  const char *model = reinterpret_cast<const char *>(bdat->getValCheck("Model", id, BDAT_TYPE_STRING));
  if (model == nullptr || *model == '\0') {
    return nullptr;
  }
  return model;
}

const char *GfAssetSetupGimmick::getArcFile(GfAssetType type) { return getMdlFile(type); }

const char *GfAssetSetupGimmick::getMotFile(GfAssetType type) {
  if (type == ASSET_TYPE_OPTION) {
    RefResource *resource = getRefResource(getMotSlot());
    if (resource != nullptr && !resource->name.empty()) {
      return resource->name.c_str();
    }
    const char *motion = reinterpret_cast<const char *>(bdat->getValCheck("Motion", id, BDAT_TYPE_STRING));
    if (motion == nullptr || *motion == '\0') {
      return nullptr;
    }
    return motion;
  }
  return nullptr;
}

const char *GfAssetSetupGimmick::getEfpFile(GfAssetType type) { return getMdlFile(type); }

const char *GfAssetSetupGimmick::getEabFile(GfAssetType type) {
  RefResource *resource = getRefResource(getEabSlot());
  if (resource != nullptr && !resource->name.empty()) {
    return resource->name.c_str();
  }
  const CBdatWrapper *rsc = bdat;
  const char *effect = reinterpret_cast<const char *>(rsc->getValCheck("Comp_Eff", id, BDAT_TYPE_STRING));
  if (effect == nullptr || *effect == '\0') {
    effect = getValidName(reinterpret_cast<const char *>(rsc->getValCheck("Model", id, BDAT_TYPE_STRING)));
  }
  return effect;
}

const char *GfAssetSetupGimmick::getEfbFile(GfAssetType type) {
  if (type == ASSET_TYPE_OPTION) {
    return getEabFile(ASSET_TYPE_OPTION);
  }
  return nullptr;
}

const char *GfAssetSetupGimmick::getStpFile(GfAssetType type) {
  if (getAssetType() == type) {
    return getValidName(reinterpret_cast<const char *>(bdat->getValCheck("Motion", id, BDAT_TYPE_STRING)));
  }
  return nullptr;
}

const char *GfAssetSetupGimmick::getPath() const { return "/model/"; }

GfAssetSetupMapObj::GfAssetSetupMapObj() {}

void GfAssetSetupMapObj::setup(GF_ASSET_HANDLE *handle, const GfInitParamMapObj &param) {
  setupParam(handle, param);
  if (!checkValidResource()) {
    return;
  }

  mm::mtl::FixStr<128> name;
  GfAssetFilesInfo info;
  info.handle = handle;
  info.assetType = getAssetType();
  info.name = name.c_str();
  info.priority = param.priority;
  makeAssetNamePrefix(name, info.assetType, getMdlFile(info.assetType), "");
  GfAssetPack *corePack = GfAssetManager::createAssetFiles(info);
  requestCoreResource(corePack, handle);

  info.assetType = ASSET_TYPE_ENEMY_MOTION;
  if (const char *motion = getMotFile(info.assetType)) {
    makeAssetNamePrefix(name, info.assetType, motion, "");
    GfAssetPack *pack = GfAssetManager::createAssetFiles(info);
    if (!setupReference(pack, name.c_str(), getMotSlot())) {
      GfAssetManager::setMotionInfo(handle, motion);
      mm::mtl::FixStr<128> path;
      path.format("%s%s%s", getPath(), motion, ".mot");
      pack->files.addResource(getMotSlot(), path.c_str());
    }
  }

  info.assetType = ASSET_TYPE_TEMPORARY;
  const char *eventMotion = getEvtMotFile(info.assetType);
  if (eventMotion == nullptr) {
    return;
  }
  makeAssetNamePrefix(name, info.assetType, eventMotion, "Evt");
  GfAssetPack *pack = GfAssetManager::createAssetFiles(info);
  if (setupReference(pack, name.c_str(), getEvtMotSlot())) {
    return;
  }
  mm::mtl::FixStr<128> path;
  path.format("%s%s%s", getEvtPath(), eventMotion, ".mot");
  pack->files.addResource(getEvtMotSlot(), path.c_str());
}

const char *GfAssetSetupMapObj::getMdlFile(GfAssetType type) {
  RefResource *resource = getRefResource(getMdlSlot());
  if (resource != nullptr && !resource->name.empty()) {
    return resource->name.c_str();
  }
  const char *model = reinterpret_cast<const char *>(bdat->getValCheck("Model", id, BDAT_TYPE_STRING));
  if (model == nullptr || *model == '\0') {
    return nullptr;
  }
  return model;
}

const char *GfAssetSetupMapObj::getArcFile(GfAssetType type) { return getMdlFile(type); }

const char *GfAssetSetupMapObj::getMotFile(GfAssetType type) {
  if (type == ASSET_TYPE_ENEMY_MOTION) {
    RefResource *resource = getRefResource(getMotSlot());
    if (resource != nullptr && !resource->name.empty()) {
      return resource->name.c_str();
    }
    const char *motion = reinterpret_cast<const char *>(bdat->getValCheck("Motion", id, BDAT_TYPE_STRING));
    if (motion == nullptr || *motion == '\0') {
      return nullptr;
    }
    return motion;
  }
  return nullptr;
}

const char *GfAssetSetupMapObj::getEabFile(GfAssetType type) { return getMdlFile(type); }

const char *GfAssetSetupMapObj::getPath() const { return "/model/"; }

GfAssetSetupFobj::GfAssetSetupFobj() {}

void GfAssetSetupFobj::setup(GF_ASSET_HANDLE *handle, const GfInitParamFobj &param) {
  setupParam(handle, param);
  if (!checkValidResource()) {
    return;
  }

  mm::mtl::FixStr<128> name;
  GfAssetFilesInfo info;
  info.handle = handle;
  info.assetType = getAssetType();
  info.name = name.c_str();
  info.priority = param.priority;
  makeAssetNamePrefix(name, info.assetType, getMdlFile(info.assetType), getMotFile(info.assetType));
  GfAssetPack *corePack = GfAssetManager::createAssetFiles(info);
  requestCoreResource(corePack, handle);
}

const char *GfAssetSetupFobj::getMdlFile(GfAssetType type) {
  RefResource *resource = getRefResource(getMdlSlot());
  if (resource != nullptr && !resource->name.empty()) {
    return resource->name.c_str();
  }
  const char *model = reinterpret_cast<const char *>(bdat->getValCheck("mdo", id, BDAT_TYPE_STRING));
  if (model == nullptr || *model == '\0') {
    return nullptr;
  }
  return model;
}

const char *GfAssetSetupFobj::getEabFile(GfAssetType type) { return getMdlFile(type); }

const char *GfAssetSetupFobj::getPath() const { return "/model/oj/"; }

GfAssetSetupWeapon::GfAssetSetupWeapon() {}

void GfAssetSetupWeapon::setup(GF_ASSET_HANDLE *handle, const GfInitParamWeapon &param) {
  setupParam(handle, param);
  append = param.append;
  if (!checkValidResource()) {
    return;
  }

  mm::mtl::FixStr<128> name;
  GfAssetFilesInfo info;
  info.handle = handle;
  info.assetType = getAssetType();
  info.name = name.c_str();
  info.priority = param.priority;
  makeAssetNamePrefix(name, info.assetType, getMdlFile(info.assetType), "");
  if (param.isDeathBlowWeapon) {
    name += "DBW";
  }
  GfAssetPack *corePack = GfAssetManager::createAssetFiles(info);
  requestCoreResource(corePack, handle);
}

const char *GfAssetSetupWeapon::getMdlFile(GfAssetType type) {
  static mm::mtl::FixStr<128> s_model;
  RefResource *resource = getRefResource(getMdlSlot());
  if (resource != nullptr) {
    makeWeaponFileName(s_model, resource->name, append.getModelName(), initParam->isDeathBlowWeapon);
  } else {
    mm::mtl::FixStr<128> empty;
    makeWeaponFileName(s_model, empty, append.getModelName(), initParam->isDeathBlowWeapon);
  }
  return s_model.empty() ? nullptr : s_model.c_str();
}

const char *GfAssetSetupWeapon::getArcFile(GfAssetType type) {
  static mm::mtl::FixStr<128> s_arc;
  RefResource *resource = getRefResource(getMdlSlot());
  if (resource != nullptr) {
    makeWeaponFileName(s_arc, resource->name, append.getModelName(), initParam->isDeathBlowWeapon);
  } else {
    mm::mtl::FixStr<128> empty;
    makeWeaponFileName(s_arc, empty, append.getModelName(), initParam->isDeathBlowWeapon);
  }
  return s_arc.empty() ? nullptr : s_arc.c_str();
}

const char *GfAssetSetupWeapon::getMotFile(GfAssetType type) {
  static mm::mtl::FixStr<128> s_motion;
  RefResource *resource = getRefResource(getMotSlot());
  if (resource != nullptr) {
    makeWeaponFileName(s_motion, resource->name, append.getMotionName(), initParam->isDeathBlowWeapon);
  } else {
    mm::mtl::FixStr<128> empty;
    makeWeaponFileName(s_motion, empty, append.getMotionName(), initParam->isDeathBlowWeapon);
  }
  return s_motion.empty() ? nullptr : s_motion.c_str();
}

const char *GfAssetSetupWeapon::getEfpFile(GfAssetType type) {
  static mm::mtl::FixStr<128> s_efp;
  RefResource *resource = getRefResource(getMdlSlot());
  if (resource != nullptr) {
    makeWeaponFileName(s_efp, resource->name, append.getModelName(), initParam->isDeathBlowWeapon);
  } else {
    mm::mtl::FixStr<128> empty;
    makeWeaponFileName(s_efp, empty, append.getModelName(), initParam->isDeathBlowWeapon);
  }
  return s_efp.empty() ? nullptr : s_efp.c_str();
}

const char *GfAssetSetupWeapon::getStpFile(GfAssetType type) { return getValidName(append.getModelName()); }

const char *GfAssetSetupWeapon::getPath() const { return GfAssetPath::getMdoModel(); }

GfAssetSetupWeaponEventCS::GfAssetSetupWeaponEventCS() {}

void GfAssetSetupWeaponEventCS::setup(GF_ASSET_HANDLE *handle, const GfInitParamWeapon &param) {
  GfAssetSetupWeapon::setup(handle, param);
  if (!checkValidResource()) {
    return;
  }

  mm::mtl::FixStr<128> name;
  GfAssetFilesInfo info;
  info.handle = handle;
  info.name = name.c_str();
  info.priority = param.priority;
  info.assetType = ASSET_TYPE_TEMPORARY;
  const char *eventMotion = getEvtMotFile(info.assetType);
  if (eventMotion == nullptr) {
    return;
  }
  makeAssetNamePrefix(name, ASSET_TYPE_TEMPORARY, eventMotion, "Evt");
  GfAssetPack *pack = GfAssetManager::createAssetFiles(info);
  if (setupReference(pack, eventMotion, getEvtMotSlot())) {
    return;
  }
  mm::mtl::FixStr<128> path;
  path.format("%s%s%s", getEvtPath(), eventMotion, ".mot");
  pack->files.addResource(getEvtMotSlot(), path.c_str());
}

const char *GfAssetSetupWeaponEventCS::getEvtMotFile(GfAssetType type) {
  if (type == ASSET_TYPE_TEMPORARY) {
    return getMotFile(ASSET_TYPE_TEMPORARY);
  }
  return nullptr;
}

const char *GfAssetSetupWeaponEventCS::getEvtPath() const { return "/event/mot/"; }

GfAssetSetupEnWeapon::GfAssetSetupEnWeapon() {}

void GfAssetSetupEnWeapon::setup(GF_ASSET_HANDLE *handle, const GfInitParamEnWeapon &param) {
  setupParam(handle, param);
  append = param.append;
  if (!checkValidResource()) {
    return;
  }

  mm::mtl::FixStr<128> name;
  GfAssetFilesInfo info;
  info.handle = handle;
  info.assetType = getAssetType();
  info.name = name.c_str();
  info.priority = param.priority;
  makeAssetNamePrefix(name, info.assetType, getMdlFile(info.assetType), getMotFile(info.assetType));
  GfAssetPack *corePack = GfAssetManager::createAssetFiles(info);
  requestCoreResource(corePack, handle);
}

const char *GfAssetSetupEnWeapon::getMdlFile(GfAssetType type) {
  RefResource *resource = getRefResource(getMdlSlot());
  if (resource != nullptr && !resource->name.empty()) {
    return resource->name.c_str();
  }
  const char *model = append.getModelName();
  if (model == nullptr || *model == '\0') {
    return nullptr;
  }
  return model;
}

const char *GfAssetSetupEnWeapon::getArcFile(GfAssetType type) { return getMdlFile(type); }

const char *GfAssetSetupEnWeapon::getMotFile(GfAssetType type) {
  RefResource *resource = getRefResource(getMotSlot());
  if (resource != nullptr && !resource->name.empty()) {
    return resource->name.c_str();
  }
  const char *motion = append.getMotionName();
  if (motion == nullptr || *motion == '\0') {
    return nullptr;
  }
  return motion;
}

const char *GfAssetSetupEnWeapon::getEfpFile(GfAssetType type) { return getMdlFile(type); }

const char *GfAssetSetupEnWeapon::getStpFile(GfAssetType type) { return getValidName(append.getModelName()); }

const char *GfAssetSetupEnWeapon::getPath() const { return GfAssetPath::getMdoModel(); }

GfAssetSetupBelonging::GfAssetSetupBelonging() {}

void GfAssetSetupBelonging::setup(GF_ASSET_HANDLE *handle, const GfInitParamBelonging &param) {
  setupParam(handle, param);
  append = param.append;
  if (!checkValidResource()) {
    return;
  }

  mm::mtl::FixStr<128> name;
  GfAssetFilesInfo info;
  info.handle = handle;
  info.assetType = getAssetType();
  info.name = name.c_str();
  info.priority = param.priority;
  makeAssetNamePrefix(name, info.assetType, getMdlFile(info.assetType), getMotFile(info.assetType));
  GfAssetPack *corePack = GfAssetManager::createAssetFiles(info);
  requestCoreResource(corePack, handle);
}

const char *GfAssetSetupBelonging::getMdlFile(GfAssetType type) {
  RefResource *resource = getRefResource(getMdlSlot());
  if (resource != nullptr && !resource->name.empty()) {
    return resource->name.c_str();
  }
  const char *model = append.getModelName();
  if (model == nullptr || *model == '\0') {
    return nullptr;
  }
  return model;
}

const char *GfAssetSetupBelonging::getArcFile(GfAssetType type) { return getMdlFile(type); }

const char *GfAssetSetupBelonging::getMotFile(GfAssetType type) {
  if (getMotSlot() >= 0) {
    RefResource *resource = getRefResource(getMotSlot());
    if (resource != nullptr && !resource->name.empty()) {
      return resource->name.c_str();
    }
    const char *motion = append.getMotionName();
    if (motion == nullptr || *motion == '\0') {
      return nullptr;
    }
    return motion;
  }
  return nullptr;
}

const char *GfAssetSetupBelonging::getPath() const { return GfAssetPath::getMdoModel(); }

GfAssetSetupExtra::GfAssetSetupExtra() {}

void GfAssetSetupExtra::setup(GF_ASSET_HANDLE *handle, const GfInitParamExtra &param) {
  setupParam(handle, param);
  append = param.append;
  if (!checkValidResource()) {
    return;
  }

  mm::mtl::FixStr<128> name;
  GfAssetFilesInfo info;
  info.handle = handle;
  info.assetType = getAssetType();
  info.name = name.c_str();
  info.priority = param.priority;
  makeAssetNamePrefix(name, info.assetType, getMdlFile(info.assetType), getMotFile(info.assetType));
  GfAssetPack *corePack = GfAssetManager::createAssetFiles(info);
  requestCoreResource(corePack, handle);
}

const char *GfAssetSetupExtra::getMdlFile(GfAssetType type) {
  RefResource *resource = getRefResource(getMdlSlot());
  if (resource != nullptr && !resource->name.empty()) {
    return resource->name.c_str();
  }
  const char *model = append.getModelName();
  if (model == nullptr || *model == '\0') {
    return nullptr;
  }
  return model;
}

const char *GfAssetSetupExtra::getArcFile(GfAssetType type) { return getMdlFile(type); }

const char *GfAssetSetupExtra::getMotFile(GfAssetType type) {
  RefResource *resource = getRefResource(getMotSlot());
  if (resource != nullptr && !resource->name.empty()) {
    return resource->name.c_str();
  }
  const char *motion = append.getMotionName();
  if (motion == nullptr || *motion == '\0') {
    return nullptr;
  }
  return motion;
}

const char *GfAssetSetupExtra::getStpFile(GfAssetType type) { return getValidName(append.getModelName()); }

const char *GfAssetSetupExtra::getPath() const { return GfAssetPath::getMdoModel(); }

GfAssetSetupMapSeamless::GfAssetSetupMapSeamless() : useMapId(false) {}

const char *GfAssetSetupMapSeamless::getMdlFile(GfAssetType type) {
  RefResource *resource = getRefResource(getMdlSlot());
  if (resource != nullptr && !resource->name.empty()) {
    return resource->name.c_str();
  }
  const char *model = useMapId ? GfDataMap::getMapResourceNameByMapID(id) : GfDataMap::getMapResourceName(id);
  model = getValidName(model);
  if (!modelName.empty()) {
    model = modelName.c_str();
  }
  return model;
}

const char *GfAssetSetupMapSeamless::getColFile(GfAssetType type) { return getMdlFile(type); }

const char *GfAssetSetupMapSeamless::getNaviFile(GfAssetType type) { return getMdlFile(type); }

const char *GfAssetSetupMapSeamless::getEfbFile(GfAssetType type) {
  effectPackName = util::getFilePtrFromPath(getMdlFile(type));
  if (!effectPackName.empty()) {
    int last = effectPackName.length() - 1;
    if (effectPackName.c_str()[last] == 'a') {
      effectPackName.resize(last);
    }
    effectPackName += "_pack";
  }
  return effectPackName.c_str();
}

const char *GfAssetSetupMapSeamless::getGIblFile(GfAssetType type) { return getMdlFile(type); }

const char *GfAssetSetupMapSeamless::getLIblFile(GfAssetType type) { return getMdlFile(type); }

void GfAssetSetupMapSeamless::requestCoreResource(GfAssetPack *pack, GF_ASSET_HANDLE *handle) {
  if (pack == nullptr) {
    return;
  }

  GfAssetFiles &files = pack->files;

  if (const char *file = getMdlFile(getAssetType())) {
    if (!setupReference(pack, file, getMdlSlot())) {
      mm::mtl::FixStr<128> path;
      path.format("%s%s%s", getPath(), file, ".wismhd");
      files.addResource(getMdlSlot(), path.c_str());
    }
  }

  if (const char *file = getColFile(getAssetType())) {
    if (!setupReference(pack, file, getColSlot())) {
      mm::mtl::FixStr<128> path;
      path.format("%s%s%s", getPath(), file, ".wiidcm");
      files.addResource(getColSlot(), path.c_str());
    }
  }

  if (const char *file = getNaviFile(getAssetType())) {
    if (!setupReference(pack, file, getNaviSlot())) {
      mm::mtl::FixStr<128> path;
      path.format("%s%s%s", getPath(), file, ".winvhe");
      files.addResource(getNaviSlot(), path.c_str());
    }
  }

  if (const char *file = getEfbFile(getAssetType())) {
    if (!setupReference(pack, file, getEpkSlot())) {
      mm::mtl::FixStr<128> path;
      path.format("/effect/ma/%s%s", file, ".wiefb");
      files.addResource(getEpkSlot(), path.c_str());
    }
  }

  if (const char *file = getGIblFile(getAssetType())) {
    if (!setupReference(pack, file, getGIblSlot())) {
      mm::mtl::FixStr<128> path;
      path.format("%s%s%s", getPath(), file, ".wiibl");
      files.addResource(getGIblSlot(), path.c_str());
    }
  }

  if (const char *file = getLIblFile(getAssetType())) {
    if (!setupReference(pack, file, getLIblSlot())) {
      mm::mtl::FixStr<128> path;
      path.format("%s%s_libl%s", getPath(), file, ".wilgt");
      files.addResource(getLIblSlot(), path.c_str());
    }
  }
}

const char *GfAssetSetupMapSeamless::getPath() const { return modelName.empty() ? GfAssetPath::getMdoMap() : ""; }

GfAssetSetupMapMdl::GfAssetSetupMapMdl() {}

void GfAssetSetupMapMdl::setup(GF_ASSET_HANDLE *handle, const GfInitParamMap &param) {
  setupParam(handle, param);
  path = param.path.c_str();
  if (!checkValidResource()) {
    return;
  }

  GfAssetFilesInfo info;
  info.handle = handle;
  info.priority = param.priority;
  info.assetType = getAssetType();
  info.name = util::getFilePtrFromPath(getPath());
  GfAssetPack *corePack = GfAssetManager::createAssetFiles(info);
  requestCoreResource(corePack, handle);
}

const char *GfAssetSetupMapMdl::getMdlFile(GfAssetType type) { return "exist"; }

const char *GfAssetSetupMapMdl::getColFile(GfAssetType type) { return getMdlFile(type); }

const char *GfAssetSetupMapMdl::getLodFile(GfAssetType type) { return getMdlFile(type); }

const char *GfAssetSetupMapMdl::getMpfFile(GfAssetType type) { return getMdlFile(type); }

const char *GfAssetSetupMapMdl::getLgtFile(GfAssetType type) { return getMdlFile(type); }

const char *GfAssetSetupMapMdl::getGIblFile(GfAssetType type) { return getMdlFile(type); }

const char *GfAssetSetupMapMdl::getAcoFile(GfAssetType type) { return getMdlFile(type); }

const char *GfAssetSetupMapMdl::getClpFile(GfAssetType type) { return getMdlFile(type); }

const char *GfAssetSetupMapMdl::getPath() const { return path.c_str(); }

GfAssetSetupEventObj::GfAssetSetupEventObj() {}

void GfAssetSetupEventObj::setup(GF_ASSET_HANDLE *handle, const GfInitParamEventObj &param) {
  setupParam(handle, param);
  if (param.bdat != nullptr) {
    // __LINE__ must be 5106 as in the original source: it is the line argument of operator new.
#line 5106
    bdat = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) CBdatWrapper(*param.bdat);
  }
  if (!checkValidResource()) {
    return;
  }

  mm::mtl::FixStr<128> name;
  GfAssetFilesInfo info;
  info.handle = handle;
  info.assetType = getAssetType();
  info.name = name.c_str();
  info.priority = param.priority;
  makeAssetNamePrefix(name, info.assetType, getMdlFile(info.assetType), getMotFile(info.assetType));
  name += "Evt";
  if (hasRefResource) {
    name += "Out";
  }
  GfAssetPack *corePack = GfAssetManager::createAssetFiles(info);
  requestCoreResource(corePack, handle);
}

const char *GfAssetSetupEventObj::getMdlFile(GfAssetType type) {
  RefResource *resource = getRefResource(getMdlSlot());
  if (resource != nullptr && !resource->name.empty()) {
    return resource->name.c_str();
  }
  return nullptr;
}

const char *GfAssetSetupEventObj::getArcFile(GfAssetType type) {
  RefResource *resource = getRefResource(getArcSlot());
  if (resource != nullptr && !resource->name.empty()) {
    return resource->name.c_str();
  }
  return nullptr;
}

const char *GfAssetSetupEventObj::getEfpFile(GfAssetType type) {
  RefResource *resource = getRefResource(getEfpSlot());
  if (resource != nullptr && !resource->name.empty()) {
    return resource->name.c_str();
  }
  return nullptr;
}

const char *GfAssetSetupEventObj::getEabFile(GfAssetType type) {
  RefResource *resource = getRefResource(getEabSlot());
  if (resource != nullptr && !resource->name.empty()) {
    return resource->name.c_str();
  }
  return nullptr;
}

const char *GfAssetSetupEventObj::getEfbFile(GfAssetType type) {
  RefResource *resource = getRefResource(getEfbSlot());
  if (resource != nullptr && !resource->name.empty()) {
    return resource->name.c_str();
  }
  return nullptr;
}

GfAssetSetupUiObj::GfAssetSetupUiObj() {}

void GfAssetSetupUiObj::setup(GF_ASSET_HANDLE *handle, const GfInitParamUiObj &param) {
  setupParam(handle, param);
  if (!checkValidResource()) {
    return;
  }

  mm::mtl::FixStr<128> name;
  GfAssetFilesInfo info;
  info.handle = handle;
  info.name = name.c_str();
  info.priority = param.priority;
  info.assetType = getAssetType();
  makeAssetNamePrefix(name, info.assetType, getMdlFile(info.assetType), "");
  GfAssetPack *corePack = GfAssetManager::createAssetFiles(info);
  requestCoreResource(corePack, handle);
}

const char *GfAssetSetupUiObj::getMdlFile(GfAssetType type) {
  RefResource *resource = getRefResource(getMdlSlot());
  if (resource != nullptr && !resource->name.empty()) {
    return resource->name.c_str();
  }
  const char *model = GfBdatRsc::get()->getRSC_MapObjListModel(id);
  if (model == nullptr || *model == '\0') {
    return nullptr;
  }
  return model;
}

const char *GfAssetSetupUiObj::getArcFile(GfAssetType type) { return getMdlFile(type); }

const char *GfAssetSetupUiObj::getPath() const { return "/model/"; }

} // namespace gf
