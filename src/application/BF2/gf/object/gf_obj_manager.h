#pragma once
#include "mm_math/mm_vec3.h"
#include "mm_mtl/bitflag.h"
#include "mm_mtl/fixed_list.h"
#include "mm_mtl/singleton.h"
#include "types.h"
#include <stddef.h>

namespace gf {

struct GF_ASSET_HANDLE;
struct GF_MOUNT_HANDLE;
struct GF_OBJ_HANDLE;
class GfObj;
class GfObjProperty;
class GfObjSetup;
class GfVolumeFade;

enum GFATTACH {
  GFATTACH_WEAPON = 0,
  GFATTACH_BELONGING = 2,
};

enum {
  GFOBJ_STATE_LOADING = 1,
  GFOBJ_STATE_UPDATE = 2,
};

struct GFOBJ_MOUNT {
  GF_MOUNT_HANDLE *handle;
  u8 _08[0xc8 - 0x08];
};

static_assert(sizeof(GFOBJ_MOUNT) == 0xc8, "");

struct GFOBJ_INFO {
  u16 multiBindUniqId;
  u16 view;
  u8 _04[0x06 - 0x04];
  u16 state;
  GF_OBJ_HANDLE *handle;
  GF_ASSET_HANDLE *assetHandle;
  GfObj *obj;
  u8 _20[0x30 - 0x20];
  GfObjSetup *setup;
  mm::mtl::BitFlag<64> flags;
  u8 _40[0x48 - 0x40];
  u32 dispFlags;
  u8 _4c[0x70 - 0x4c];
  u64 userData[3];
  GF_OBJ_HANDLE *master;
  GF_OBJ_HANDLE *owner;
  GfObjProperty *property;
  mm::Vec3 modelScale;
  u8 _b0[0xb8 - 0xb0];
  GFOBJ_MOUNT mounts[4];
  GfVolumeFade *volumeFade;
  u8 _3e0[0x404 - 0x3e0];
  char modelBaseName[0x10];
};

static_assert(offsetof(GFOBJ_INFO, view) == 0x02, "");
static_assert(offsetof(GFOBJ_INFO, state) == 0x06, "");
static_assert(offsetof(GFOBJ_INFO, handle) == 0x08, "");
static_assert(offsetof(GFOBJ_INFO, assetHandle) == 0x10, "");
static_assert(offsetof(GFOBJ_INFO, obj) == 0x18, "");
static_assert(offsetof(GFOBJ_INFO, setup) == 0x30, "");
static_assert(offsetof(GFOBJ_INFO, flags) == 0x38, "");
static_assert(offsetof(GFOBJ_INFO, dispFlags) == 0x48, "");
static_assert(offsetof(GFOBJ_INFO, userData) == 0x70, "");
static_assert(offsetof(GFOBJ_INFO, master) == 0x88, "");
static_assert(offsetof(GFOBJ_INFO, owner) == 0x90, "");
static_assert(offsetof(GFOBJ_INFO, property) == 0x98, "");
static_assert(offsetof(GFOBJ_INFO, modelScale) == 0xa0, "");
static_assert(offsetof(GFOBJ_INFO, mounts) == 0xb8, "");
static_assert(offsetof(GFOBJ_INFO, volumeFade) == 0x3d8, "");
static_assert(offsetof(GFOBJ_INFO, modelBaseName) == 0x404, "");

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

class GfObjManager : public mm::mtl::PtrSingleton<GfObjManager> {
public:
  static GFOBJ_INFO *getObjInfo(GF_OBJ_HANDLE *handle);
  static void addListener(IGfObjListener *listener, IGfObjListener::OBJEVT event);
  static void removeListener(IGfObjListener *listener);
  bool isValidMultiBind(GF_OBJ_HANDLE *handle, u32 uniqId) const;
  void addDestroyObj(GF_OBJ_HANDLE *handle, bool isImmediate);
  void addApplyParam(GF_OBJ_HANDLE *handle);
  bool isSuspendUpdate() const;
  bool hasReloadObjForDebug();
  bool getFollowObj(mm::mtl::FixedList<GF_OBJ_HANDLE *, 768> &objs, GF_OBJ_HANDLE *handle);
};

} // namespace gf
