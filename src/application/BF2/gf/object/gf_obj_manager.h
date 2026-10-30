#pragma once
#include "gf/event/gf_event.h"
#include "gf/object/gf_append_info.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/bitflag.h"
#include "mm_mtl/fixed_list.h"
#include "mm_mtl/singleton.h"
#include "types.h"
#include <stddef.h>

namespace fw {
struct UpdateInfo;
}

namespace gf {

struct GF_ASSET_HANDLE;
struct GF_MOUNT_HANDLE;
struct GF_OBJ_HANDLE;
class GfAssetMultiBind;
class GfObj;
class GfObjProperty;
class GfObjSetup;
struct GfSetupParam;
class GfVolumeFade;

enum GFATTACH {
  GFATTACH_WEAPON = 0,
  GFATTACH_APPEND = 1,
  GFATTACH_BELONGING = 2,
  GFATTACH_WEAPON_EXTRA = 3,
};

enum {
  GFOBJ_STATE_LOADING = 1,
  GFOBJ_STATE_UPDATE = 2,
};

struct GFOBJ_MOUNT {
  GF_MOUNT_HANDLE *unknown00; // Inferred role: handle; original member name unknown.
  u32 unknown08;              // Inferred role: append index; original member name unknown.
  u8 _0c[0x10 - 0x0c];
  GfAppendInfo unknown10; // Inferred role: append info; original member name unknown.
};

static_assert(offsetof(GFOBJ_MOUNT, unknown08) == 0x08, "");
static_assert(offsetof(GFOBJ_MOUNT, unknown10) == 0x10, "");
static_assert(sizeof(GFOBJ_MOUNT) == 0xc8, "");

struct GFOBJ_INFO {
  u16 unknown00; // Inferred role: multi bind unique id; original member name unknown.
  u16 unknown02; // Inferred role: view; original member name unknown.
  u8 _04[0x06 - 0x04];
  u16 unknown06;              // Inferred role: state; original member name unknown.
  GF_OBJ_HANDLE *unknown08;   // Inferred role: handle; original member name unknown.
  GF_ASSET_HANDLE *unknown10; // Inferred role: asset handle; original member name unknown.
  GfObj *unknown18;           // Inferred role: object; original member name unknown.
  u8 _20[0x30 - 0x20];
  GfObjSetup *unknown30;             // Inferred role: setup; original member name unknown.
  mm::mtl::unknown027<64> unknown38; // Inferred role: flags; original member name unknown.
  u8 _40[0x48 - 0x40];
  u32 unknown48; // Inferred role: disp flags; original member name unknown.
  u8 _4c[0x70 - 0x4c];
  u64 unknown70[3];         // Inferred role: user data; original member name unknown.
  GF_OBJ_HANDLE *unknown88; // Inferred role: master; original member name unknown.
  GF_OBJ_HANDLE *unknown90; // Inferred role: owner; original member name unknown.
  GfObjProperty *unknown98; // Inferred role: property; original member name unknown.
  mm::Vec3 unknowna0;       // Inferred role: model scale; original member name unknown.
  int unknownb0;            // Inferred role: coli priority; original member name unknown.
  u8 _b4[0xb8 - 0xb4];
  GFOBJ_MOUNT unknownb8[4]; // Inferred role: mounts; original member name unknown.
  GfVolumeFade *unknown3d8; // Inferred role: volume fade; original member name unknown.
  u8 _3e0[0x404 - 0x3e0];
  char unknown404[0x10]; // Inferred role: model base name; original member name unknown.
};

static_assert(offsetof(GFOBJ_INFO, unknown02) == 0x02, "");
static_assert(offsetof(GFOBJ_INFO, unknown06) == 0x06, "");
static_assert(offsetof(GFOBJ_INFO, unknown08) == 0x08, "");
static_assert(offsetof(GFOBJ_INFO, unknown10) == 0x10, "");
static_assert(offsetof(GFOBJ_INFO, unknown18) == 0x18, "");
static_assert(offsetof(GFOBJ_INFO, unknownb0) == 0xb0, "");
static_assert(offsetof(GFOBJ_INFO, unknown30) == 0x30, "");
static_assert(offsetof(GFOBJ_INFO, unknown38) == 0x38, "");
static_assert(offsetof(GFOBJ_INFO, unknown48) == 0x48, "");
static_assert(offsetof(GFOBJ_INFO, unknown70) == 0x70, "");
static_assert(offsetof(GFOBJ_INFO, unknown88) == 0x88, "");
static_assert(offsetof(GFOBJ_INFO, unknown90) == 0x90, "");
static_assert(offsetof(GFOBJ_INFO, unknown98) == 0x98, "");
static_assert(offsetof(GFOBJ_INFO, unknowna0) == 0xa0, "");
static_assert(offsetof(GFOBJ_INFO, unknownb8) == 0xb8, "");
static_assert(offsetof(GFOBJ_INFO, unknown3d8) == 0x3d8, "");
static_assert(offsetof(GFOBJ_INFO, unknown404) == 0x404, "");

class IGfObjListener {
public:
  enum OBJEVT {
    OBJEVT_ALL,
    OBJEVT_ENTRY,
    OBJEVT_LOADED,
    OBJEVT_DESTROY,
    OBJEVT_REMOVE,
  };

  virtual void listenerGfObj(OBJEVT event, GF_OBJ_HANDLE *handle, u32 objectType) = 0;
};

class GfObjManager : public mm::mtl::PtrSingleton<GfObjManager>, public IGfEvent {
public:
  struct ObjListener {
    IGfObjListener *unknown00;        // Inferred role: listener; original member name unknown.
    IGfObjListener::OBJEVT unknown08; // Inferred role: event; original member name unknown.
  };

  static GfObjManager *s_pThis;
  static mm::mtl::FixedList<ObjListener, 256> m_aListenerObj;

  static void build(const GfSetupParam &param);
  static void destroy();
  void update(const fw::UpdateInfo &info);
  void postUpdate(const fw::UpdateInfo &info);
  static GFOBJ_INFO *getObjInfo(GF_OBJ_HANDLE *handle);
  static void addListener(IGfObjListener *listener, IGfObjListener::OBJEVT event);
  static void removeListener(IGfObjListener *listener);
  static int getGfObjCapacity(u32 objectType);
  static int getObjectNum(u32 objectType);
  bool isValidMultiBind(GF_OBJ_HANDLE *handle, u32 uniqId) const;
  GfAssetMultiBind *getAssetMultiBind(u32 uniqId) const;
  GfAssetMultiBind *getMultiBinder(GF_OBJ_HANDLE *handle);
  void loadedMultiBind(GF_OBJ_HANDLE *handle, u32 uniqId);
  void unloadedMultiBind(GF_OBJ_HANDLE *handle, u32 uniqId);
  void addDestroyObj(GF_OBJ_HANDLE *handle, bool isImmediate);
  void addApplyParam(GF_OBJ_HANDLE *handle);
  bool isSuspendUpdate() const;
  bool hasReloadObjForDebug();
  static void enterStayObject(GF_OBJ_HANDLE *handle);
  void addHandle(GF_OBJ_HANDLE *handle);
  void setStateLoading(GF_OBJ_HANDLE *handle);
  bool getFollowObj(mm::mtl::FixedList<GF_OBJ_HANDLE *, 768> &objs, GF_OBJ_HANDLE *handle);
  static bool isInitialized();
  void requestDestroyAll();
  void callGfObjListener(IGfObjListener::OBJEVT event, GF_OBJ_HANDLE *handle);
  void addApplyParamObj(GfObj *obj);
  void checkLoadingAndCreate(GF_OBJ_HANDLE *handle);
  bool isEmptyObj() const;
  void destroyLayerObj(u32 layer);
  void destroyAllObj(bool isIgnoreMap);
  void getObjList(mm::mtl::FixedList<GF_OBJ_HANDLE *, 768> &objs);
  bool isExistGfObj(bool isIgnoreMap) const;
  bool isExistLayerObj(u32 layer) const;
  const mm::mtl::FixedList<GF_OBJ_HANDLE *, 4096> *getLoadingObj() const;
  const mm::mtl::FixedList<GF_OBJ_HANDLE *, 4096> *getDestroyObj() const;
  u32 createGfObjHandle(const GFOBJ_INFO *info, u32 index, int multiBind);

  bool unknown10; // Inferred role: initialized; original member name unknown.
  u32 unknown14;  // Inferred role: handle generation; original member name unknown.
  u8 _18[0x420228 - 0x18];
  u32 *unknown420228;        // Inferred role: usage bit flags of the object infos; original member name unknown.
  GFOBJ_INFO *unknown420230; // Inferred role: object infos; original member name unknown.
  u8 _420238[0x420240 - 0x420238];
  mm::mtl::FixedList<GF_OBJ_HANDLE *, 4096> unknown420240; // Inferred role: loading objects; original member name unknown.
  mm::mtl::FixedList<GF_OBJ_HANDLE *, 2048> unknown432260; // Inferred role: destroying objects; original member name unknown.
  u8 _43b280[0x44d2a0 - 0x43b280];
  mm::mtl::FixedList<GF_OBJ_HANDLE *, 4096> unknown44d2a0; // Inferred role: objects to destroy; original member name unknown.
  u8 _45f2c0[0x484538 - 0x45f2c0];
  u32 unknown484538; // Inferred role: object count of the last list; original member name unknown.
  u8 _48453c[0x484540 - 0x48453c];
  s16 unknown484540[16];                                    // Inferred role: object count per type; original member name unknown.
  mm::mtl::FixedList<GfAssetMultiBind *, 64> unknown484560; // Inferred role: multi binds; original member name unknown.
  u8 _4849c0[0x484a28 - 0x4849c0];
  bool unknown484a28; // Inferred role: update suspended; original member name unknown.
  int unknown484a2c;  // Inferred role: capacity of the effect objects; original member name unknown.
};

static_assert(offsetof(GfObjManager, unknown420228) == 0x420228, "");
static_assert(offsetof(GfObjManager, unknown420240) == 0x420240, "");
static_assert(offsetof(GfObjManager, unknown432260) == 0x432260, "");
static_assert(offsetof(GfObjManager, unknown44d2a0) == 0x44d2a0, "");
static_assert(offsetof(GfObjManager, unknown484540) == 0x484540, "");
static_assert(offsetof(GfObjManager, unknown484560) == 0x484560, "");
static_assert(offsetof(GfObjManager, unknown484a28) == 0x484a28, "");
static_assert(offsetof(GfObjManager, unknown484a2c) == 0x484a2c, "");

} // namespace gf
