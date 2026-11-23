#include "framework/coli/coli_object.h"
#include "framework/effect/effect_lod_manager.h"
#include "framework/effect/effect_manager.h"
#include "framework/effect/effect_pack.h"
#include "framework/navi/navi_manager.h"
#include "fw/fw_update_info.h"
#include "gf/asset/gf_asset_def.h"
#include "gf/asset/gf_asset_manager.h"
#include "gf/asset/gf_asset_resource.h"
#include "gf/gf_manager.h"
#include "gf/map/gf_map_manager.h"
#include "ml/scn.h"
#include "ml/scn_obj_ibl.h"
#include "ml/scn_obj_model.h"
#include "mm_mtl/reference_object.h"
#include "scn/scn_obj_model_dr_sys.h"

namespace mm {
struct Vec3;
} // namespace mm

namespace fw {
class ModelObject;
} // namespace fw
namespace ml {
class DrMdlObj;
} // namespace ml

namespace gf {
struct GF_ASSET_HANDLE;

MapEff::~MapEff() {}

void MapEff::create(GF_ASSET_HANDLE *handle, fw::ModelObject *model) {
  if (handle == unknown018) {
    return;
  }

  GfAssetResource *resource = GfAssetManager::getResource(handle, MAP_FILE_IDX_UNKNOWN_6, ASSET_TYPE_UNKNOWN_0);
  if (resource != nullptr && m_effectPack == nullptr) {
    m_effectPack = fw::EffectPack::createFromMemory(resource->getAssetData(), resource->getAssetSize(), resource->getAssetName(), false);
  }

  if (!unknown00) {
    fw::EffectLodManager::get()->init(model, m_effectPack);
    unknown00 = true;
  }
}

void MapEff::destroy() {
  destroyEffefct();
  mm::mtl::safeRelease(m_effectPack);
}

void MapEff::destroyEffefct() {
  if (unknown00) {
    fw::EffectLodManager::get()->term();
    unknown00 = false;
  }
}

void MapEff::update(const fw::UpdateInfo &info) {
  if (unknown00) {
    fw::EffectLodManager::get()->update(info);
  }

  fw::EffectManager *manager = fw::EffectManager::get();
  // Category 1: the map effects.
  manager->unknown37958[1] = __builtin_fmaxf(info.unknown08, 0.00001f);
}

MapNavi::~MapNavi() {}

void MapNavi::create(GF_ASSET_HANDLE *handle) {
  if (!unknown00) {
    GfAssetResource *resource = GfAssetManager::getResource(handle, MAP_FILE_IDX_UNKNOWN_2, ASSET_TYPE_UNKNOWN_0);
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
    GfAssetResource *resource = GfAssetManager::getResource(handle, MAP_FILE_IDX_UNKNOWN_1, ASSET_TYPE_UNKNOWN_0);
    if (resource != nullptr) {
      unknown00 = fw::ColiObject::createColiGrand(resource->getAssetData());
    }
  }
}

void MapColi::destroy() { mm::mtl::safeRelease(unknown00); }

namespace {

// Original name unknown: common body of MapMdl::createLod and MapMdl::createMpf.
void unknown001(MapMdl &map, GF_ASSET_HANDLE *handle, GfFileIdx index) {
  if (map.m_model == nullptr) {
    GfAssetResource *resource = GfAssetManager::getResource(handle, index, ASSET_TYPE_UNKNOWN_0);
    if (resource != nullptr) {
      map.m_model = GfManager::getSetupParam().unknown00->createMdl(resource->getAssetData(), resource->getAssetName(), 0);
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

void MapMdl::destroy() { unknown002(m_model); }

ml::ScnObjModel *MapMdl::getModel() const { return m_model; }

ml::DrMdlObj *MapMdl::getDrModel() const {
  if (m_model != nullptr) {
    return static_cast<ml::ScnObjModelDrSys *>(m_model)->unknown3d8;
  }
  return nullptr;
}

MapGIBL::~MapGIBL() {}

void MapGIBL::create(GF_ASSET_HANDLE *handle) {
  if (unknown00 == nullptr) {
    GfAssetResource *resource = GfAssetManager::getResource(handle, MAP_FILE_IDX_UNKNOWN_7, ASSET_TYPE_UNKNOWN_0);
    if (resource != nullptr) {
      unknown00 = GfManager::getSetupParam().unknown00->createIBL(resource->getAssetData(), 0);
    }
  }
}

void MapGIBL::destroy() { unknown002(unknown00); }

void MapGIBL::setReferencePos(const mm::Vec3 &position) {
  if (unknown00 != nullptr) {
    static_cast<ml::ScnObjIBL *>(unknown00)->setReferencePos(position);
  }
}

MapLIBL::~MapLIBL() {}

void MapLIBL::create(GF_ASSET_HANDLE *handle) {
  if (unknown00 == nullptr) {
    GfAssetResource *resource = GfAssetManager::getResource(handle, MAP_FILE_IDX_UNKNOWN_8, ASSET_TYPE_UNKNOWN_0);
    if (resource != nullptr) {
      unknown00 = GfManager::getSetupParam().unknown00->createLgt(resource->getAssetData(), 0);
    }
  }
}

void MapLIBL::destroy() { unknown002(unknown00); }

MapLgt::~MapLgt() {}

void MapLgt::create(GF_ASSET_HANDLE *handle) {
  GfAssetResource *resource = GfAssetManager::getResource(handle, MAP_FILE_IDX_UNKNOWN_3, ASSET_TYPE_UNKNOWN_0);
  if (resource != nullptr && unknown00 == nullptr) {
    unknown00 = GfManager::getSetupParam().unknown00->createLgt(resource->getAssetData(), 0);
  }
}

void MapLgt::destroy() { unknown002(unknown00); }

MapClip::~MapClip() {}

void MapClip::create(GF_ASSET_HANDLE *handle) {
  if (unknown00 == nullptr) {
    GfAssetResource *resource = GfAssetManager::getResource(handle, MAP_FILE_IDX_UNKNOWN_10, ASSET_TYPE_UNKNOWN_0);
    if (resource != nullptr) {
      unknown00 = GfManager::getSetupParam().unknown00->createClip(resource->getAssetData(), 0);
    }
  }
}

void MapClip::destroy() { unknown002(unknown00); }

MapAco::~MapAco() {}

void MapAco::create(GF_ASSET_HANDLE *handle) {
  GfAssetResource *resource = GfAssetManager::getResource(handle, MAP_FILE_IDX_UNKNOWN_9, ASSET_TYPE_UNKNOWN_0);
  if (resource != nullptr && unknown00 == nullptr) {
    unknown00 = GfManager::getSetupParam().unknown00->createEnvColi(resource->getAssetData(), 0);
  }
}

void MapAco::destroy() { unknown002(unknown00); }

MapSe::~MapSe() {}

void MapSe::create(GF_ASSET_HANDLE *handle) { GfAssetManager::getResource(handle, MAP_FILE_IDX_UNKNOWN_9, ASSET_TYPE_UNKNOWN_0); }

void MapSe::destroy() {}

} // namespace gf

// The game builds the seam map part in this unit: MapSeam sits between the other map parts in one contiguous range with no other unit between
// (MapEff and MapMdl 0x71003929b4 to 0x7100393034, MapSeam 0x710039306c to 0x7100393208, MapLgt to MapSe 0x7100393214 to 0x710039337c).
#include "gf_map_seam.cpp"
