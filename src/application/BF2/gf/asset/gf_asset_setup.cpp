#include "gf/asset/gf_asset_setup.h"

#include "gf/asset/gf_asset_manager.h"
#include "gf/asset/gf_asset_pack.h"
#include "gf/asset/gf_asset_resource.h"
#include "gf/data/gf_bdat_wrapper.h"
#include "gf/data/gf_data_sound.h"
#include "gf/gf_allocator.h"
#include "gf/object/gf_init_param.h"
#include "gf/util/gf_util.h"
#include "mm_mtl/fixed_queue.h"

namespace gf {

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

} // namespace gf
