#pragma once
#include "gf/object/gf_obj_manager.h"
#include "types.h"
#include <stddef.h>

namespace gf {

struct GF_MOUNT_HANDLE;
struct GF_OBJ_HANDLE;

enum OPTMNT {};

class GfWeapon {
public:
  virtual ~GfWeapon();

  GF_OBJ_HANDLE **getCurrentHandles() { return isAlternate ? alternateHandles : handles; }

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

  GF_OBJ_HANDLE *handles[10];
  GF_OBJ_HANDLE *alternateHandles[10];
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
