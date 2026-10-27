#pragma once
#include <stddef.h>

#include "gf/object/gf_obj_manager.h"
#include "mm_mtl/fixed_array.h"
#include "mm_mtl/fixed_list.h"
#include "mm_mtl/reference_object.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace fw {
class MessageObject;
struct Message;
} // namespace fw

namespace gf {

struct GF_MOUNT_HANDLE;
struct GF_OBJ_HANDLE;
struct GfSetupParam;
class GfAppendInfo;

enum OPTMNT : u32 {
  OPTMNT_UNKNOWN_0 = 0,
  OPTMNT_UNKNOWN_1 = 1,
  OPTMNT_WIRE = 2,
  OPTMNT_BLADE = 3,
  OPTMNT_UNKNOWN_4 = 4,
  OPTMNT_UNKNOWN_FFFFFFFF = 0xffffffff,
};

class GfWeapon {
public:
  virtual ~GfWeapon();

  mm::mtl::FixedArray<GF_OBJ_HANDLE *, 10> &getCurrentHandles() { return unknowna8 ? unknown58 : unknown08; }

  GF_OBJ_HANDLE *getHandle(bool isAlternateSet, u16 index) const { return isAlternateSet ? unknown58[index] : unknown08[index]; }

  bool isExistHandle(GF_OBJ_HANDLE *handle) {
    for (u32 index = 0; index < 10; index++) {
      if (getCurrentHandles()[index] == handle) {
        return true;
      }
    }

    return false;
  }

  u16 getRscRight() const;
  u16 getRscLeft() const;

  mm::mtl::FixedArray<GF_OBJ_HANDLE *, 10> unknown08; // Inferred role: handles; original member name unknown.
  mm::mtl::FixedArray<GF_OBJ_HANDLE *, 10> unknown58; // Inferred role: alternate handles; original member name unknown.
  bool unknowna8;                                     // Inferred role: alternate; original member name unknown.
};

static_assert(offsetof(GfWeapon, unknown08) == 0x08, "");
static_assert(offsetof(GfWeapon, unknown58) == 0x58, "");
static_assert(offsetof(GfWeapon, unknowna8) == 0xa8, "");

class GfGameMount : public mm::mtl::ReferenceObject {
public:
  virtual bool execMount(OPTMNT type);
  virtual bool setWeaponOwner(OPTMNT type);
  virtual GF_OBJ_HANDLE *getHandle(OPTMNT type);
  virtual GfAppendInfo *getAppendInfo();
  ~GfGameMount() override;
  u32 getAllWeapons() const;
  GF_OBJ_HANDLE *getAllWeapons(u32 index) const;
  void setWeaponOwner(GF_OBJ_HANDLE *owner);

  GF_OBJ_HANDLE *unknown10; // Inferred role: owner handle; original member name unknown.
  GfWeapon *unknown18;      // Inferred role: mounted handles; original member name unknown.
  OPTMNT unknown20;         // Inferred role: current mount type; original member name unknown.
  OPTMNT unknown24;         // Inferred role: pending mount type; original member name unknown.
  bool unknown28;           // Inferred role: mount type reset; original member name unknown.
  GFATTACH unknown2c;       // Inferred role: attach; original member name unknown.
};

static_assert(offsetof(GfGameMount, unknown10) == 0x10, "");
static_assert(offsetof(GfGameMount, unknown18) == 0x18, "");
static_assert(offsetof(GfGameMount, unknown20) == 0x20, "");
static_assert(offsetof(GfGameMount, unknown24) == 0x24, "");
static_assert(offsetof(GfGameMount, unknown28) == 0x28, "");
static_assert(offsetof(GfGameMount, unknown2c) == 0x2c, "");
static_assert(sizeof(GfGameMount) == 0x30, "");

class GfGameMountBlade : public GfGameMount {
public:
  bool execMount(OPTMNT type) override;
  bool setWeaponOwner(OPTMNT type) override;
  GF_OBJ_HANDLE *getHandle(OPTMNT type) override;
  GfAppendInfo *getAppendInfo() override;

  GF_OBJ_HANDLE *unknown30; // Inferred role: blade handle; original member name unknown.
};

static_assert(offsetof(GfGameMountBlade, unknown30) == 0x30, "");
static_assert(sizeof(GfGameMountBlade) == 0x38, "");

class GfMountManager : public mm::mtl::PtrSingleton<GfMountManager>, public IGfObjListener {
public:
  struct MINFO {
    GfGameMount *unknown00;     // Inferred role: mount; original member name unknown.
    GF_MOUNT_HANDLE *unknown08; // Inferred role: mount handle; original member name unknown.
  };

  static void build(const GfSetupParam &param);
  static void destroy();
  void finalize();
  static bool isInitialized();
  GF_MOUNT_HANDLE *createHandle();
  static void destroyMount(GF_MOUNT_HANDLE *mountHandle);
  static GfGameMount *getMount(GF_MOUNT_HANDLE *mountHandle);
  static void sendMessage(GF_OBJ_HANDLE *handle, GFATTACH attach, fw::MessageObject *receiver, fw::Message &message);
  static GfWeapon *getGfWeapon(GF_OBJ_HANDLE *handle, GFATTACH attach);
  static GfWeapon *getAppendHandles(GF_OBJ_HANDLE *handle, GFATTACH attach);
  static GF_OBJ_HANDLE *getHandle(GF_OBJ_HANDLE *handle, GFATTACH attach, OPTMNT type);
  static OPTMNT getMountType(GF_OBJ_HANDLE *handle, GFATTACH attach);
  static void setMountType(GF_OBJ_HANDLE *handle, GFATTACH attach, OPTMNT type);
  static void resetMountType(GF_OBJ_HANDLE *handle, GFATTACH attach);
  static void addMountHandle(GF_MOUNT_HANDLE *mountHandle, GF_OBJ_HANDLE *handle);
  static void removeMountHandle(GF_OBJ_HANDLE *handle, GFATTACH attach);
  static GF_OBJ_HANDLE *getOptionRight(GF_OBJ_HANDLE *handle, GFATTACH attach);
  static GF_OBJ_HANDLE *getOptionLeft(GF_OBJ_HANDLE *handle, GFATTACH attach);
  void execDetachMount(GF_OBJ_HANDLE *handle, GFATTACH attach);
  void execAttachMount(GF_OBJ_HANDLE *handle, GFATTACH attach);
  static void gevGameObjEnter(GF_OBJ_HANDLE *handle);
  static void gevGameObjLeave(GF_OBJ_HANDLE *handle);
  static void setAlphaMount(GF_OBJ_HANDLE *handle, GFATTACH attach, f32 alpha);
  static void execMount(GF_OBJ_HANDLE *handle, GFATTACH attach, OPTMNT type);
  static void resetMount(GF_OBJ_HANDLE *handle, GFATTACH attach, OPTMNT type);
  void listenerGfObj(OBJEVT event, GF_OBJ_HANDLE *handle, u32 objectType) override;

  mm::mtl::FixedList<MINFO, 256> unknown10; // Inferred role: mounts; original member name unknown.
  u64 unknown1a38;                          // Inferred role: next mount handle; original member name unknown.
  bool unknown1a40;                         // Inferred role: initialized; original member name unknown.
};

static_assert(offsetof(GfMountManager, unknown10) == 0x10, "");
static_assert(offsetof(GfMountManager, unknown1a38) == 0x1a38, "");
static_assert(offsetof(GfMountManager, unknown1a40) == 0x1a40, "");
static_assert(sizeof(GfMountManager) == 0x1a48, "");

} // namespace gf
