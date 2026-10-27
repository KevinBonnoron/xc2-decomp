#pragma once
#include "gf/object/gf_obj_manager.h"
#include "mm_mtl/fixed_array.h"
#include "types.h"
#include <stddef.h>

namespace gf {

struct GF_MOUNT_HANDLE;
struct GF_OBJ_HANDLE;
struct GfSetupParam;

enum OPTMNT {
  OPTMNT_WIRE = 2,
  OPTMNT_BLADE = 3,
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

class GfMountManager {
public:
  static void build(const GfSetupParam &param);
  static void destroy();
  static GfWeapon *getGfWeapon(GF_OBJ_HANDLE *handle, GFATTACH attach);
  static GfWeapon *getAppendHandles(GF_OBJ_HANDLE *handle, GFATTACH attach);
  static GF_OBJ_HANDLE *getHandle(GF_OBJ_HANDLE *handle, GFATTACH attach, OPTMNT type);
  static OPTMNT getMountType(GF_OBJ_HANDLE *handle, GFATTACH attach);
  static void setMountType(GF_OBJ_HANDLE *handle, GFATTACH attach, OPTMNT type);
  static void addMountHandle(GF_MOUNT_HANDLE *mountHandle, GF_OBJ_HANDLE *handle);
  static void removeMountHandle(GF_OBJ_HANDLE *handle, GFATTACH attach);
  static void gevGameObjEnter(GF_OBJ_HANDLE *handle);
  static void gevGameObjLeave(GF_OBJ_HANDLE *handle);
  static void execMount(GF_OBJ_HANDLE *handle, GFATTACH attach, OPTMNT type);
  static void resetMount(GF_OBJ_HANDLE *handle, GFATTACH attach, OPTMNT type);
};

} // namespace gf
