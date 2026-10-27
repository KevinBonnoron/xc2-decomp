#include "framework/coli/coli_object.h"
#include "framework/navi/navi_manager.h"
#include "gf/asset/gf_asset_def.h"
#include "gf/asset/gf_asset_manager.h"
#include "gf/asset/gf_asset_resource.h"
#include "gf/gf_manager.h"
#include "gf/map/gf_map_manager.h"
#include "ml/scn.h"
#include "ml/scn_obj_model.h"
#include "mm_mtl/reference_object.h"
#include "scn/scn_obj_model_dr_sys.h"

namespace ml {
class DrMdlObj;
} // namespace ml

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

namespace {

// Original name unknown: common body of MapMdl::createLod and MapMdl::createMpf.
void unknown001(MapMdl &map, GF_ASSET_HANDLE *handle, GfFileIdx index) {
  if (map.unknown00 == nullptr) {
    GfAssetResource *resource = GfAssetManager::getResource(handle, index, ASSET_TYPE_BASE);
    if (resource != nullptr) {
      map.unknown00 = GfManager::getSetupParam().unknown00->createMdl(resource->getAssetData(), resource->getAssetName(), 0);
    }
  }
}

// Original name unknown: release of a scene object, common body of the destroy functions of the map parts.
template <typename T> void unknown002(T *&object) {
  if (object != nullptr) {
    GfManager::getSetupParam().unknown00->releaseItem(object);
    object = nullptr;
  }
}

} // namespace

MapMdl::~MapMdl() {}

void MapMdl::createLod(GF_ASSET_HANDLE *handle) { unknown001(*this, handle, MAP_FILE_IDX_UNKNOWN_4); }

void MapMdl::createMpf(GF_ASSET_HANDLE *handle) { unknown001(*this, handle, MAP_FILE_IDX_UNKNOWN_5); }

void MapMdl::destroy() { unknown002(unknown00); }

ml::ScnObjModel *MapMdl::getModel() const { return unknown00; }

ml::DrMdlObj *MapMdl::getDrModel() const {
  if (unknown00 != nullptr) {
    return static_cast<ml::ScnObjModelDrSys *>(unknown00)->unknown3d8;
  }
  return nullptr;
}

MapGIBL::~MapGIBL() {}

void MapGIBL::create(GF_ASSET_HANDLE *handle) {
  if (unknown00 == nullptr) {
    GfAssetResource *resource = GfAssetManager::getResource(handle, MAP_FILE_IDX_UNKNOWN_7, ASSET_TYPE_BASE);
    if (resource != nullptr) {
      unknown00 = GfManager::getSetupParam().unknown00->createIBL(resource->getAssetData(), 0);
    }
  }
}

void MapGIBL::destroy() { unknown002(unknown00); }

MapLIBL::~MapLIBL() {}

void MapLIBL::create(GF_ASSET_HANDLE *handle) {
  if (unknown00 == nullptr) {
    GfAssetResource *resource = GfAssetManager::getResource(handle, MAP_FILE_IDX_UNKNOWN_8, ASSET_TYPE_BASE);
    if (resource != nullptr) {
      unknown00 = GfManager::getSetupParam().unknown00->createLgt(resource->getAssetData(), 0);
    }
  }
}

void MapLIBL::destroy() { unknown002(unknown00); }

MapLgt::~MapLgt() {}

void MapLgt::create(GF_ASSET_HANDLE *handle) {
  GfAssetResource *resource = GfAssetManager::getResource(handle, MAP_FILE_IDX_UNKNOWN_3, ASSET_TYPE_BASE);
  if (resource != nullptr && unknown00 == nullptr) {
    unknown00 = GfManager::getSetupParam().unknown00->createLgt(resource->getAssetData(), 0);
  }
}

void MapLgt::destroy() { unknown002(unknown00); }

MapClip::~MapClip() {}

void MapClip::create(GF_ASSET_HANDLE *handle) {
  if (unknown00 == nullptr) {
    GfAssetResource *resource = GfAssetManager::getResource(handle, MAP_FILE_IDX_UNKNOWN_10, ASSET_TYPE_BASE);
    if (resource != nullptr) {
      unknown00 = GfManager::getSetupParam().unknown00->createClip(resource->getAssetData(), 0);
    }
  }
}

void MapClip::destroy() { unknown002(unknown00); }

MapAco::~MapAco() {}

void MapAco::create(GF_ASSET_HANDLE *handle) {
  GfAssetResource *resource = GfAssetManager::getResource(handle, MAP_FILE_IDX_UNKNOWN_9, ASSET_TYPE_BASE);
  if (resource != nullptr && unknown00 == nullptr) {
    unknown00 = GfManager::getSetupParam().unknown00->createEnvColi(resource->getAssetData(), 0);
  }
}

void MapAco::destroy() { unknown002(unknown00); }

MapSe::~MapSe() {}

void MapSe::create(GF_ASSET_HANDLE *handle) { GfAssetManager::getResource(handle, MAP_FILE_IDX_UNKNOWN_9, ASSET_TYPE_BASE); }

void MapSe::destroy() {}

} // namespace gf
