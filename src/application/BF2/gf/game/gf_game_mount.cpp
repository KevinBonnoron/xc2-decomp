#include "gf/game/gf_game_mount.h"

#include "gf/data/gf_object_type.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_util.h"

namespace gf {

GfGameMount::~GfGameMount() {
  if (unknown18 != nullptr) {
    delete unknown18;
    unknown18 = nullptr;
  }
}

GF_OBJ_HANDLE *GfGameMount::getHandle(OPTMNT type) {
  switch (type) {
  case OPTMNT_UNKNOWN_1:
  case OPTMNT_WIRE:
  case OPTMNT_UNKNOWN_4:
    return unknown10;
  default:
    return INVALID_HANDLE;
  }
}

GfAppendInfo *GfGameMount::getAppendInfo() { return GfObjUtil::getAppendInfo(unknown10, unknown2c); }

u32 GfGameMount::getAllWeapons() const {
  u32 count = 0;
  for (u32 index = 0; index < 10; index++) {
    if (unknown18->unknown08[index] != INVALID_HANDLE) {
      count++;
    }
    if (unknown18->unknown58[index] != INVALID_HANDLE) {
      count++;
    }
  }
  return count;
}

GF_OBJ_HANDLE *GfGameMount::getAllWeapons(u32 index) const {
  u32 count = 0;
  for (u32 i = 0; i < 10; i++) {
    if (unknown18->unknown08[i] != INVALID_HANDLE) {
      if (count == index) {
        return unknown18->unknown08[i];
      }
      count++;
    }
    if (unknown18->unknown58[i] != INVALID_HANDLE) {
      if (count == index) {
        return unknown18->unknown58[i];
      }
      count++;
    }
  }
  return INVALID_HANDLE;
}

void GfGameMount::setWeaponOwner(GF_OBJ_HANDLE *owner) {
  for (u32 index = 0; index < 10; index++) {
    GF_OBJ_HANDLE *handle = unknown18->getCurrentHandles()[index];
    if (handle != INVALID_HANDLE) {
      GfObjUtil::setOwner(handle, owner);
    }
  }
}

bool GfGameMount::setWeaponOwner(OPTMNT type) {
  if (type < 5 && type != OPTMNT_BLADE) {
    setWeaponOwner(getHandle(OPTMNT_WIRE));
    return true;
  }
  return false;
}

GF_OBJ_HANDLE *GfGameMountBlade::getHandle(OPTMNT type) {
  GF_OBJ_HANDLE *handle;
  switch (type) {
  case OPTMNT_UNKNOWN_1:
  case OPTMNT_WIRE:
  case OPTMNT_UNKNOWN_4:
    handle = unknown10;
    break;
  default:
    handle = INVALID_HANDLE;
    break;
  }
  if (type == OPTMNT_BLADE && handle == INVALID_HANDLE) {
    handle = unknown30;
  }
  return handle;
}

bool GfGameMountBlade::setWeaponOwner(OPTMNT type) {
  GF_OBJ_HANDLE *owner;
  switch (type) {
  case OPTMNT_UNKNOWN_0:
  case OPTMNT_UNKNOWN_1:
  case OPTMNT_WIRE:
  case OPTMNT_UNKNOWN_4:
    owner = getHandle(OPTMNT_WIRE);
    break;
  case OPTMNT_BLADE:
    owner = unknown30;
    break;
  default:
    return false;
  }
  GfGameMount::setWeaponOwner(owner);
  return true;
}

GfAppendInfo *GfGameMountBlade::getAppendInfo() {
  GfAppendInfo *info = GfObjUtil::getAppendInfo(unknown30, unknown2c);
  if (info != nullptr) {
    return info;
  }
  return GfObjUtil::getAppendInfo(unknown10, unknown2c);
}

GfGameMount *GfMountManager::getMount(GF_MOUNT_HANDLE *mountHandle) {
  for (mm::mtl::FixedList<MINFO, 256>::iterator it = get()->unknown10.begin(); it != get()->unknown10.end(); ++it) {
    if (it->unknown08 == mountHandle) {
      return it->unknown00;
    }
  }
  return nullptr;
}

bool GfMountManager::isInitialized() {
  GfMountManager *manager = get();
  if (manager != nullptr) {
    return manager->unknown1a40;
  }
  return false;
}

GF_MOUNT_HANDLE *GfMountManager::createHandle() {
  u64 handle = unknown1a38;
  u64 next = handle + 1;
  if (next == 0xffffffffffffffff) {
    next = 0;
  }
  unknown1a38 = next;
  return reinterpret_cast<GF_MOUNT_HANDLE *>(handle);
}

void GfMountManager::finalize() {
  GfObjManager::removeListener(this);
  unknown1a40 = false;
}

void GfMountManager::destroyMount(GF_MOUNT_HANDLE *mountHandle) {
  for (mm::mtl::FixedList<MINFO, 256>::iterator it = get()->unknown10.begin(); it != get()->unknown10.end(); ++it) {
    if (it->unknown08 == mountHandle) {
      get()->unknown10.erase(it);
      return;
    }
  }
}

GfWeapon *GfMountManager::getAppendHandles(GF_OBJ_HANDLE *handle, GFATTACH attach) {
  GfGameMount *mount = getMount(GfObjUtil::getMountHandle(handle, attach));
  if (mount != nullptr) {
    return mount->unknown18;
  }
  return nullptr;
}

GfWeapon *GfMountManager::getGfWeapon(GF_OBJ_HANDLE *handle, GFATTACH attach) {
  GfGameMount *mount = getMount(GfObjUtil::getMountHandle(handle, attach));
  if (mount != nullptr) {
    return mount->unknown18;
  }
  return nullptr;
}

GF_OBJ_HANDLE *GfMountManager::getHandle(GF_OBJ_HANDLE *handle, GFATTACH attach, OPTMNT type) {
  GfGameMount *mount = getMount(GfObjUtil::getMountHandle(handle, attach));
  if (mount != nullptr) {
    return mount->getHandle(type);
  }
  return INVALID_HANDLE;
}

OPTMNT GfMountManager::getMountType(GF_OBJ_HANDLE *handle, GFATTACH attach) {
  GfGameMount *mount = getMount(GfObjUtil::getMountHandle(handle, attach));
  if (mount != nullptr) {
    return mount->unknown20;
  }
  return OPTMNT_UNKNOWN_FFFFFFFF;
}

void GfMountManager::setMountType(GF_OBJ_HANDLE *handle, GFATTACH attach, OPTMNT type) {
  GfGameMount *mount = getMount(GfObjUtil::getMountHandle(handle, attach));
  if (mount != nullptr) {
    mount->unknown20 = type;
  }
}

void GfMountManager::resetMountType(GF_OBJ_HANDLE *handle, GFATTACH attach) {
  GfGameMount *mount = getMount(GfObjUtil::getMountHandle(handle, attach));
  if (mount != nullptr) {
    mount->unknown20 = OPTMNT_UNKNOWN_FFFFFFFF;
    mount->unknown28 = true;
  }
}

void GfMountManager::execMount(GF_OBJ_HANDLE *handle, GFATTACH attach, OPTMNT type) {
  GfGameMount *mount = getMount(GfObjUtil::getMountHandle(handle, attach));
  if (mount != nullptr) {
    mount->execMount(type);
  }
}

void GfMountManager::resetMount(GF_OBJ_HANDLE *handle, GFATTACH attach, OPTMNT type) {
  GfGameMount *mount = getMount(GfObjUtil::getMountHandle(handle, attach));
  if (mount != nullptr) {
    mount->execMount(type);
  }
  GfObjUtil::resetWeaponMotion(handle, OPTMNT_UNKNOWN_FFFFFFFF);
}

GF_OBJ_HANDLE *GfMountManager::getOptionRight(GF_OBJ_HANDLE *handle, GFATTACH attach) {
  if (GfObjUtil::getMountHandle(handle, attach) != reinterpret_cast<GF_MOUNT_HANDLE *>(-1)) {
    GfGameMount *mount = getMount(GfObjUtil::getMountHandle(handle, attach));
    if (mount != nullptr && mount->unknown18 != nullptr) {
      return mount->unknown18->getCurrentHandles()[0];
    }
  }
  return INVALID_HANDLE;
}

GF_OBJ_HANDLE *GfMountManager::getOptionLeft(GF_OBJ_HANDLE *handle, GFATTACH attach) {
  if (GfObjUtil::getMountHandle(handle, attach) != reinterpret_cast<GF_MOUNT_HANDLE *>(-1)) {
    GfGameMount *mount = getMount(GfObjUtil::getMountHandle(handle, attach));
    if (mount != nullptr && mount->unknown18 != nullptr) {
      return mount->unknown18->getCurrentHandles()[1];
    }
  }
  return INVALID_HANDLE;
}

void GfMountManager::setAlphaMount(GF_OBJ_HANDLE *handle, GFATTACH attach, f32 alpha) {
  GfGameMount *mount = getMount(GfObjUtil::getMountHandle(handle, attach));
  if (mount == nullptr) {
    return;
  }
  for (u32 index = 0; index < 10; index++) {
    GF_OBJ_HANDLE *weapon = mount->unknown18->getCurrentHandles()[index];
    if (weapon != INVALID_HANDLE) {
      GfObjAcc acc(weapon);
      acc.setAlphaNormal(alpha);
    }
  }
}

void GfMountManager::execDetachMount(GF_OBJ_HANDLE *handle, GFATTACH attach) {
  GfGameMount *mount = getMount(GfObjUtil::getMountHandle(handle, attach));
  if (mount == nullptr) {
    return;
  }
  OPTMNT type = mount->unknown20;
  execMount(handle, attach, OPTMNT_UNKNOWN_0);
  mount->unknown28 = true;
  mount->unknown20 = type;
}

void GfMountManager::execAttachMount(GF_OBJ_HANDLE *handle, GFATTACH attach) {
  GfGameMount *mount = getMount(GfObjUtil::getMountHandle(handle, attach));
  if (mount == nullptr) {
    return;
  }
  if (!mount->unknown28) {
    return;
  }
  OPTMNT type = mount->unknown24;
  if (mount->unknown20 != OPTMNT_UNKNOWN_FFFFFFFF) {
    type = mount->unknown20;
  }
  switch (GfObjUtil::getObjType(handle)) {
  case OBJECT_TYPE_DRIVER:
  case OBJECT_TYPE_BLADE:
  case OBJECT_TYPE_ENEMY:
  case OBJECT_TYPE_PC_WEAPON:
  case OBJECT_TYPE_EN_WEAPON:
  case OBJECT_TYPE_BELONGING:
    execMount(handle, attach, type);
    break;
  default:
    break;
  }
}

void GfMountManager::gevGameObjLeave(GF_OBJ_HANDLE *) {}

} // namespace gf
