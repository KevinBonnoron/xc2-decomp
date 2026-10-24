#pragma once
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
  u8 _08[0xc8 - 0x08];
};

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
  GfObjSetup *unknown30;          // Inferred role: setup; original member name unknown.
  mm::mtl::BitFlag<64> unknown38; // Inferred role: flags; original member name unknown.
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

class GfObjManager : public mm::mtl::PtrSingleton<GfObjManager> {
public:
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
  void addDestroyObj(GF_OBJ_HANDLE *handle, bool isImmediate);
  void addApplyParam(GF_OBJ_HANDLE *handle);
  bool isSuspendUpdate() const;
  bool hasReloadObjForDebug();
  bool getFollowObj(mm::mtl::FixedList<GF_OBJ_HANDLE *, 768> &objs, GF_OBJ_HANDLE *handle);
};

} // namespace gf
