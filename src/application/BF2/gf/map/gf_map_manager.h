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
class ScnObj;
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

class MapEff {
public:
  MapEff() : isInitialized(false), effectPack(nullptr) {}
  ~MapEff();
  void create(GF_ASSET_HANDLE *handle, fw::ModelObject *model);
  void destroy();
  void destroyEffefct();
  void update(const fw::UpdateInfo &info);

  bool isInitialized;
  fw::EffectPack *effectPack;
};

static_assert(sizeof(MapEff) == 0x10, "");

class MapNavi {
public:
  MapNavi() : isCreated(false) {}
  ~MapNavi();
  void create(GF_ASSET_HANDLE *handle);
  void destroy();

  bool isCreated;
};

class MapColi {
public:
  MapColi() : coliObject(nullptr) {}
  ~MapColi();
  void create(GF_ASSET_HANDLE *handle);
  void destroy();

  fw::ColiObject *coliObject;
};

class MapGIBL {
public:
  MapGIBL() : ibl(nullptr) {}
  ~MapGIBL();
  void create(GF_ASSET_HANDLE *handle);
  void destroy();
  void setReferencePos(const mm::Vec3 &position);

  ml::ScnObj *ibl;
};

class MapLIBL {
public:
  MapLIBL() : ibl(nullptr) {}
  ~MapLIBL();
  void create(GF_ASSET_HANDLE *handle);
  void destroy();

  ml::ScnObj *ibl;
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

  bool initialized;
  GF_OBJ_HANDLE *mapHandle;
  u32 mapJumpId;
  u32 mapId;
  GF_ASSET_HANDLE *assetHandle;
  mm::mtl::IntrusivePtr<fw::DynamicWindResource> windResource;
  MapEff effect;
  MapNavi navi;
  MapColi coli;
  MapGIBL globalIbl;
  MapLIBL localIbl;
};

static_assert(offsetof(GfMapManager, initialized) == 0x18, "");
static_assert(offsetof(GfMapManager, mapHandle) == 0x20, "");
static_assert(offsetof(GfMapManager, mapJumpId) == 0x28, "");
static_assert(offsetof(GfMapManager, mapId) == 0x2c, "");
static_assert(offsetof(GfMapManager, assetHandle) == 0x30, "");
static_assert(offsetof(GfMapManager, windResource) == 0x38, "");
static_assert(offsetof(GfMapManager, effect) == 0x40, "");
static_assert(offsetof(GfMapManager, navi) == 0x50, "");
static_assert(offsetof(GfMapManager, coli) == 0x58, "");
static_assert(offsetof(GfMapManager, globalIbl) == 0x60, "");
static_assert(offsetof(GfMapManager, localIbl) == 0x68, "");
static_assert(sizeof(GfMapManager) == 0x70, "");

} // namespace gf
