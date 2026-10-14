#pragma once
#include "mm_mtl/bitflag.h"
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
  u8 _00[0x06 - 0x00];
  u16 state;
  GF_OBJ_HANDLE *handle;
  GF_ASSET_HANDLE *assetHandle;
  GfObj *obj;
  u8 _20[0x30 - 0x20];
  GfObjSetup *setup;
  mm::mtl::BitFlag<64> flags;
  u8 _40[0x90 - 0x40];
  GF_OBJ_HANDLE *owner;
  GfObjProperty *property;
  u8 _a0[0xb8 - 0xa0];
  GFOBJ_MOUNT mounts[4];
  GfVolumeFade *volumeFade;
  u8 _3e0[0x404 - 0x3e0];
  char modelBaseName[0x10];
};

static_assert(offsetof(GFOBJ_INFO, state) == 0x06, "");
static_assert(offsetof(GFOBJ_INFO, handle) == 0x08, "");
static_assert(offsetof(GFOBJ_INFO, assetHandle) == 0x10, "");
static_assert(offsetof(GFOBJ_INFO, obj) == 0x18, "");
static_assert(offsetof(GFOBJ_INFO, setup) == 0x30, "");
static_assert(offsetof(GFOBJ_INFO, flags) == 0x38, "");
static_assert(offsetof(GFOBJ_INFO, owner) == 0x90, "");
static_assert(offsetof(GFOBJ_INFO, property) == 0x98, "");
static_assert(offsetof(GFOBJ_INFO, mounts) == 0xb8, "");
static_assert(offsetof(GFOBJ_INFO, volumeFade) == 0x3d8, "");
static_assert(offsetof(GFOBJ_INFO, modelBaseName) == 0x404, "");

class GfObjManager : public mm::mtl::PtrSingleton<GfObjManager> {
public:
  static GFOBJ_INFO *getObjInfo(GF_OBJ_HANDLE *handle);
  void addApplyParam(GF_OBJ_HANDLE *handle);
};

} // namespace gf
