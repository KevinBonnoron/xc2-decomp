#include "framework/coli/coli_object.h"
#include "framework/navi/navi_manager.h"
#include "gf/asset/gf_asset_def.h"
#include "gf/asset/gf_asset_manager.h"
#include "gf/asset/gf_asset_resource.h"
#include "gf/gf_manager.h"
#include "gf/map/gf_map_manager.h"
#include "ml/scn.h"
#include "mm_mtl/reference_object.h"

namespace gf {
struct GF_ASSET_HANDLE;

MapNavi::~MapNavi() {}

void MapNavi::create(GF_ASSET_HANDLE *handle) {
  if (!unknown00) {
    GfAssetResource *resource = GfAssetManager::getResource(handle, MAP_FILE_IDX_UNKNOWN_2, ASSET_TYPE_BASE);
    if (resource != nullptr) {
      unknown00 = fw::NaviManager::get()->createNaviMesh(resource->getAssetData(), resource->getAssetName());
    }
  }
}

void MapNavi::destroy() {
  if (unknown00) {
    fw::NaviManager::get()->releaseNaviMesh();
    unknown00 = false;
  }
}

MapColi::~MapColi() {}

void MapColi::create(GF_ASSET_HANDLE *handle) {
  if (unknown00 == nullptr) {
    GfAssetResource *resource = GfAssetManager::getResource(handle, MAP_FILE_IDX_COLLISION, ASSET_TYPE_BASE);
    if (resource != nullptr) {
      unknown00 = fw::ColiObject::createColiGrand(resource->getAssetData());
    }
  }
}

void MapColi::destroy() { mm::mtl::safeRelease(unknown00); }

MapGIBL::~MapGIBL() {}

void MapGIBL::create(GF_ASSET_HANDLE *handle) {
  if (unknown00 == nullptr) {
    GfAssetResource *resource = GfAssetManager::getResource(handle, MAP_FILE_IDX_UNKNOWN_7, ASSET_TYPE_BASE);
    if (resource != nullptr) {
      unknown00 = GfManager::getSetupParam().unknown00->createIBL(resource->getAssetData(), 0);
    }
  }
}

void MapGIBL::destroy() {
  if (unknown00 != nullptr) {
    GfManager::getSetupParam().unknown00->releaseItem(unknown00);
    unknown00 = nullptr;
  }
}

MapLIBL::~MapLIBL() {}

void MapLIBL::create(GF_ASSET_HANDLE *handle) {
  if (unknown00 == nullptr) {
    GfAssetResource *resource = GfAssetManager::getResource(handle, MAP_FILE_IDX_UNKNOWN_8, ASSET_TYPE_BASE);
    if (resource != nullptr) {
      unknown00 = GfManager::getSetupParam().unknown00->createLgt(resource->getAssetData(), 0);
    }
  }
}

void MapLIBL::destroy() {
  if (unknown00 != nullptr) {
    GfManager::getSetupParam().unknown00->releaseItem(unknown00);
    unknown00 = nullptr;
  }
}

} // namespace gf
