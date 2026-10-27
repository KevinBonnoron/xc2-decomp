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

const GfFileIdx MAP_FILE_IDX_COLLISION = static_cast<GfFileIdx>(1);
const GfFileIdx MAP_FILE_IDX_UNKNOWN_2 = static_cast<GfFileIdx>(2);
const GfFileIdx MAP_FILE_IDX_UNKNOWN_4 = static_cast<GfFileIdx>(4);
const GfFileIdx MAP_FILE_IDX_UNKNOWN_5 = static_cast<GfFileIdx>(5);
const GfFileIdx MAP_FILE_IDX_UNKNOWN_7 = static_cast<GfFileIdx>(7);
const GfFileIdx MAP_FILE_IDX_UNKNOWN_8 = static_cast<GfFileIdx>(8);

class MapEff {
public:
  MapEff() : unknown00(false), unknown08(nullptr) {}
  ~MapEff();
  void create(GF_ASSET_HANDLE *handle, fw::ModelObject *model);
  void destroy();
  void destroyEffefct();
  void update(const fw::UpdateInfo &info);

  bool unknown00;            // Inferred role: initialized; original member name unknown.
  fw::EffectPack *unknown08; // Inferred role: effect pack; original member name unknown.
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
  MapMdl() : unknown00(nullptr) {}
  ~MapMdl();
  void createLod(GF_ASSET_HANDLE *handle);
  void createMpf(GF_ASSET_HANDLE *handle);
  void destroy();
  ml::ScnObjModel *getModel() const;
  ml::DrMdlObj *getDrModel() const;

  ml::ScnObjModel *unknown00; // Inferred role: model; original member name unknown.
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
  GF_OBJ_HANDLE *unknown20;                                 // Inferred role: map handle; original member name unknown.
  u32 unknown28;                                            // Inferred role: map jump id; original member name unknown.
  u32 unknown2c;                                            // Inferred role: map id; original member name unknown.
  GF_ASSET_HANDLE *unknown30;                               // Inferred role: asset handle; original member name unknown.
  mm::mtl::IntrusivePtr<fw::DynamicWindResource> unknown38; // Inferred role: wind resource; original member name unknown.
  MapEff unknown40;                                         // Inferred role: effect; original member name unknown.
  MapNavi unknown50;                                        // Inferred role: navi; original member name unknown.
  MapColi unknown58;                                        // Inferred role: coli; original member name unknown.
  MapGIBL unknown60;                                        // Inferred role: global ibl; original member name unknown.
  MapLIBL unknown68;                                        // Inferred role: local ibl; original member name unknown.
};

static_assert(offsetof(GfMapManager, unknown18) == 0x18, "");
static_assert(offsetof(GfMapManager, unknown20) == 0x20, "");
static_assert(offsetof(GfMapManager, unknown28) == 0x28, "");
static_assert(offsetof(GfMapManager, unknown2c) == 0x2c, "");
static_assert(offsetof(GfMapManager, unknown30) == 0x30, "");
static_assert(offsetof(GfMapManager, unknown38) == 0x38, "");
static_assert(offsetof(GfMapManager, unknown40) == 0x40, "");
static_assert(offsetof(GfMapManager, unknown50) == 0x50, "");
static_assert(offsetof(GfMapManager, unknown58) == 0x58, "");
static_assert(offsetof(GfMapManager, unknown60) == 0x60, "");
static_assert(offsetof(GfMapManager, unknown68) == 0x68, "");
static_assert(sizeof(GfMapManager) == 0x70, "");

} // namespace gf
