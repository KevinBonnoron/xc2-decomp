#pragma once
#include "gf/object/gf_obj_manager.h"
#include "mm_mtl/fixed_array.h"
#include "types.h"
#include <stddef.h>

namespace gf {

struct GF_MOUNT_HANDLE;
struct GF_OBJ_HANDLE;

enum OPTMNT {};

class GfWeapon {
public:
  virtual ~GfWeapon();

  mm::mtl::FixedArray<GF_OBJ_HANDLE *, 10> &getCurrentHandles() { return isAlternate ? alternateHandles : handles; }

  GF_OBJ_HANDLE *getHandle(bool isAlternateSet, u16 index) const { return isAlternateSet ? alternateHandles[index] : handles[index]; }

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

  mm::mtl::FixedArray<GF_OBJ_HANDLE *, 10> handles;
  mm::mtl::FixedArray<GF_OBJ_HANDLE *, 10> alternateHandles;
  bool isAlternate;
};

static_assert(offsetof(GfWeapon, handles) == 0x08, "");
static_assert(offsetof(GfWeapon, alternateHandles) == 0x58, "");
static_assert(offsetof(GfWeapon, isAlternate) == 0xa8, "");

class GfMountManager {
public:
  static GfWeapon *getGfWeapon(GF_OBJ_HANDLE *handle, GFATTACH attach);
  static OPTMNT getMountType(GF_OBJ_HANDLE *handle, GFATTACH attach);
  static void setMountType(GF_OBJ_HANDLE *handle, GFATTACH attach, OPTMNT type);
  static void addMountHandle(GF_MOUNT_HANDLE *mountHandle, GF_OBJ_HANDLE *handle);
  static void removeMountHandle(GF_OBJ_HANDLE *handle, GFATTACH attach);
};

} // namespace gf
