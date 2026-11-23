#pragma once
#include <stddef.h>

#include "gf/asset/gf_asset_def.h"
#include "gf/event/gf_event.h"
#include "gf/object/gf_obj_manager.h"
#include "mm_mtl/intrusive_ptr.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace fw {
class ColiObject;
class EffectPack;
class ModelObject;
struct UpdateInfo;
class DynamicWindResource;
} // namespace fw

namespace ml {
class DrMdlObj;
class ScnObj;
class ScnObjModel;
} // namespace ml

namespace mm {
struct Vec3;
} // namespace mm

namespace gf {

struct GF_ASSET_HANDLE;
struct GF_OBJ_HANDLE;
struct GfSetupParam;
class GfAssetResource;

const GfFileIdx MAP_FILE_IDX_UNKNOWN_1 = static_cast<GfFileIdx>(1); // Inferred role: map file idx collision; original name unknown.
const GfFileIdx MAP_FILE_IDX_UNKNOWN_2 = static_cast<GfFileIdx>(2);
const GfFileIdx MAP_FILE_IDX_UNKNOWN_3 = static_cast<GfFileIdx>(3);
const GfFileIdx MAP_FILE_IDX_UNKNOWN_4 = static_cast<GfFileIdx>(4);
const GfFileIdx MAP_FILE_IDX_UNKNOWN_5 = static_cast<GfFileIdx>(5);
const GfFileIdx MAP_FILE_IDX_UNKNOWN_6 = static_cast<GfFileIdx>(6);
const GfFileIdx MAP_FILE_IDX_UNKNOWN_7 = static_cast<GfFileIdx>(7);
const GfFileIdx MAP_FILE_IDX_UNKNOWN_8 = static_cast<GfFileIdx>(8);
const GfFileIdx MAP_FILE_IDX_UNKNOWN_9 = static_cast<GfFileIdx>(9);
const GfFileIdx MAP_FILE_IDX_UNKNOWN_10 = static_cast<GfFileIdx>(10);

class MapEff {
public:
  MapEff() : unknown00(false), m_effectPack(nullptr) {}
  ~MapEff();
  void create(GF_ASSET_HANDLE *handle, fw::ModelObject *model);
  void destroy();
  void destroyEffefct();
  void update(const fw::UpdateInfo &info);

  bool unknown00;               // Inferred role: initialized; original member name unknown.
  fw::EffectPack *m_effectPack; // Inferred role: effect pack; named after the game accessor gf::GfMapManager::getEffectPack.
};

static_assert(sizeof(MapEff) == 0x10, "");

class MapNavi {
public:
  MapNavi() : unknown00(false) {}
  ~MapNavi();
  void create(GF_ASSET_HANDLE *handle);
  void destroy();

  bool unknown00; // Inferred role: created; original member name unknown.
};

class MapColi {
public:
  MapColi() : unknown00(nullptr) {}
  ~MapColi();
  void create(GF_ASSET_HANDLE *handle);
  void destroy();

  fw::ColiObject *unknown00; // Inferred role: coli object; original member name unknown.
};

class MapMdl {
public:
  MapMdl() : m_model(nullptr) {}
  ~MapMdl();
  void createLod(GF_ASSET_HANDLE *handle);
  void createMpf(GF_ASSET_HANDLE *handle);
  void destroy();
  ml::ScnObjModel *getModel() const;
  ml::DrMdlObj *getDrModel() const;

  ml::ScnObjModel *m_model; // Inferred role: model; named after the game accessor gf::MapMdl::getModel.
};

static_assert(sizeof(MapMdl) == 0x8, "");

class MapGIBL {
public:
  MapGIBL() : unknown00(nullptr) {}
  ~MapGIBL();
  void create(GF_ASSET_HANDLE *handle);
  void destroy();
  void setReferencePos(const mm::Vec3 &position);

  ml::ScnObj *unknown00; // Inferred role: ibl; original member name unknown.
};

class MapLIBL {
public:
  MapLIBL() : unknown00(nullptr) {}
  ~MapLIBL();
  void create(GF_ASSET_HANDLE *handle);
  void destroy();

  ml::ScnObj *unknown00; // Inferred role: ibl; original member name unknown.
};

class MapLgt {
public:
  MapLgt() : unknown00(nullptr) {}
  ~MapLgt();
  void create(GF_ASSET_HANDLE *handle);
  void destroy();

  ml::ScnObj *unknown00; // Inferred role: light; original member name unknown.
};

class MapClip {
public:
  MapClip() : unknown00(nullptr) {}
  ~MapClip();
  void create(GF_ASSET_HANDLE *handle);
  void destroy();

  ml::ScnObj *unknown00; // Inferred role: clip; original member name unknown.
};

class MapAco {
public:
  MapAco() : unknown00(nullptr) {}
  ~MapAco();
  void create(GF_ASSET_HANDLE *handle);
  void destroy();

  ml::ScnObj *unknown00; // Inferred role: environment collision; original member name unknown.
};

class MapSe {
public:
  ~MapSe();
  void create(GF_ASSET_HANDLE *handle);
  void destroy();
};

class GfMapManager : public mm::mtl::PtrSingleton<GfMapManager>, public IGfObjListener, public IGfEvent {
public:
  GfMapManager(const GfSetupParam &param);
  void initialize(const GfSetupParam &param);
  ~GfMapManager();
  static void build(const GfSetupParam &param);
  static void destroy();
  void finalize();
  static bool isInitialized();
  void listenerGfObj(OBJEVT event, GF_OBJ_HANDLE *handle, u32 objectType) override;
  void setupMapHandle(GF_OBJ_HANDLE *handle);
  static void buildMapData(GF_OBJ_HANDLE *handle);
  void destroyMapData(GF_OBJ_HANDLE *handle);
  void resetMapHandle(GF_OBJ_HANDLE *handle);
  void createIdColi();
  void destroyIdColi();
  void createNavi();
  void destroyNavi();
  void createEffect();
  static fw::ModelObject *getModelObject();
  void destroyEffect();
  void createGlobalIBL();
  void destroyGlobalIBL();
  void createLocalIBL();
  void destroyLocalIBL();
  static GF_OBJ_HANDLE *getGfObjHandle();
  static void destroyObj();
  static bool isMapReady();
  static bool isExistObj();
  static u32 getMapJumpID();
  static u32 getMapID();
  static fw::EffectPack *getEffectPack();
  static void setEnvTime(u32 hour, u32 minute);
  static void setEnvWeather(u32 weatherType);
  static void setGlobalIBLReferencePos(const mm::Vec3 &position);
  void gevMapjump(GEV event, const MapjumpCallbackInfo &info) override;
  static const char *getMapName();
  static const char *getAssetName();
  void createWind();
  void destoryWind();
  void updateMapSpeed(const fw::UpdateInfo &info);
  static GfAssetResource *getModelResource();
  static fw::ColiObject *getColiObject();
  static GfAssetResource *getColiResource();
  static bool isColisionExist();
  void postUpdate(const fw::UpdateInfo &info);
  void update(const fw::UpdateInfo &info);

  bool unknown18;                                           // Inferred role: initialized; original member name unknown.
  GF_OBJ_HANDLE *m_gfObjHandle;                             // Inferred role: map handle; named after the game accessor gf::GfMapManager::getGfObjHandle.
  u32 m_mapJumpID;                                          // Inferred role: map jump id; named after the game accessor gf::GfMapManager::getMapJumpID.
  u32 m_mapID;                                              // Inferred role: map id; named after the game accessor gf::GfMapManager::getMapID.
  GF_ASSET_HANDLE *m_GF_ASSET_HANDLE;                       // Inferred role: asset handle; original member name unknown.
  mm::mtl::IntrusivePtr<fw::DynamicWindResource> unknown38; // Inferred role: wind resource; original member name unknown.
  MapEff m_mapEff;                                          // Inferred role: effect; original member name unknown.
  MapNavi m_mapNavi;                                        // Inferred role: navi; original member name unknown.
  MapColi m_mapColi;                                        // Inferred role: coli; original member name unknown.
  MapGIBL m_mapGIBL;                                        // Inferred role: global ibl; original member name unknown.
  MapLIBL m_mapLIBL;                                        // Inferred role: local ibl; original member name unknown.
};

static_assert(offsetof(GfMapManager, unknown18) == 0x18, "");
static_assert(offsetof(GfMapManager, m_gfObjHandle) == 0x20, "");
static_assert(offsetof(GfMapManager, m_mapJumpID) == 0x28, "");
static_assert(offsetof(GfMapManager, m_mapID) == 0x2c, "");
static_assert(offsetof(GfMapManager, m_GF_ASSET_HANDLE) == 0x30, "");
static_assert(offsetof(GfMapManager, unknown38) == 0x38, "");
static_assert(offsetof(GfMapManager, m_mapEff) == 0x40, "");
static_assert(offsetof(GfMapManager, m_mapNavi) == 0x50, "");
static_assert(offsetof(GfMapManager, m_mapColi) == 0x58, "");
static_assert(offsetof(GfMapManager, m_mapGIBL) == 0x60, "");
static_assert(offsetof(GfMapManager, m_mapLIBL) == 0x68, "");
static_assert(sizeof(GfMapManager) == 0x70, "");

} // namespace gf
