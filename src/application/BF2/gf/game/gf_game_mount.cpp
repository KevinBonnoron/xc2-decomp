#include "gf/game/gf_game_mount.h"

#include "gf/data/gf_data_blade.h"
#include "gf/data/gf_object_type.h"
#include "gf/game/gf_game_util.h"
#include "gf/gf_allocator.h"
#include "gf/object/component/animation/gf_com_asm.h"
#include "gf/object/gf_append.h"
#include "gf/object/gf_append_info.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_setup.h"
#include "gf/object/gf_obj_util.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"

namespace gf {

// Inferred role: sets the idle weapon state on every mounted weapon; original name unknown.
static void unknown001(GfWeapon *weapon) {
  for (u32 index = 0; index < 10; index++) {
    GfObj *obj = GfObjUtil::getObj(weapon->getCurrentHandles()[index]);
    if (obj != nullptr) {
      GfComAsm *comAsm = obj->getComponent<GfComAsm>();
      if (comAsm != nullptr) {
        GfObjAcc acc(GfGameUtil::getWeaponOwner(obj->unknownf8));
        mm::mtl::FixStr<32> state;
        GfGameUtil::makeWeaponStateIdle(state, acc.getHandle(), acc.isBattle());
        comAsm->setState(state.c_str(), ANIM_LAYER_UNKNOWN_0);
      }
    }
  }
}

GfGameMount::~GfGameMount() {
  if (unknown18 != nullptr) {
    delete unknown18;
    unknown18 = nullptr;
  }
}

GF_OBJ_HANDLE *GfGameMount::getHandle(OPTMNT type) {
  switch (type) {
  case OPTMNT_UNKNOWN_1:
  case OPTMNT_UNKNOWN_2:
  case OPTMNT_UNKNOWN_4:
    return unknown10;
  default:
    return unknown020;
  }
}

void GfGameMount::setScaleMount(f32 scale) {
  for (u32 index = 0; index < 10; index++) {
    GF_OBJ_HANDLE *handle = unknown18->getCurrentHandles()[index];
    if (handle != unknown020) {
      GfObjSetup *setup = GfObjUtil::getObjSetup(handle);
      GfAppend *append = GfObjUtil::getAppend(handle, unknown2c);
      f32 mountScale = 1.0f;
      if (append != nullptr) {
        mountScale = append->unknown7c * setup->unknown40;
      }
      GfObjAcc acc(unknown18->getCurrentHandles()[index]);
      acc.setModelScale(mountScale * scale);
    }
  }
}

void GfGameMount::detach() {
  for (u32 index = 0; index < 10; index++) {
    GF_OBJ_HANDLE *handle = unknown18->getCurrentHandles()[index];
    if (handle != unknown020) {
      GfObjUtil::unmountFromBone(handle);
    }
  }
  if (unknown28) {
    unknown28 = false;
  }
  setScaleMount(1.0f);
}

void GfGameMount::attach(OPTMNT type, GF_OBJ_HANDLE *handle) {
  if (handle == unknown020) {
    return;
  }
  GfAppendInfo *info = getAppendInfo();
  if (info != nullptr && info->unknown00[1].size() != 0) {
    u32 offset = type - OPTMNT_UNKNOWN_1;
    bool isMain = offset < 2;
    info->unknownb0 = !isMain;
    unknown18->unknowna8 = !isMain;
    GfMountManager::setAlphaMount(handle, unknown2c, 0.0f);
    unknown001(unknown18);
    info->unknownb0 = isMain;
    unknown18->unknowna8 = isMain;
    GfMountManager::setAlphaMount(handle, unknown2c, 1.0f);
    unknown001(unknown18);
  }
  for (u32 index = 0; index < 10; index++) {
    GfObjAcc acc(unknown18->getCurrentHandles()[index]);
    if (acc.isValidModel()) {
      GF_OBJ_HANDLE *parent = GfObjUtil::getParentHandle(acc.getHandle());
      if (GfObjUtil::isUpdate(handle) && acc.isValidModel() && parent == unknown020) {
        GfAppend *append = GfObjUtil::getAppend(acc.getHandle(), unknown2c);
        if (append != nullptr) {
          GfObjUtil::mountToBone(acc.getHandle(), handle, append->getBone(type));
        }
      }
    }
  }
  if (type == OPTMNT_UNKNOWN_3) {
    GfObjAcc bladeAcc(handle);
    if (bladeAcc.getType() == OBJECT_TYPE_BLADE) {
      setScaleMount(GfDataBlade::getWpnScale(bladeAcc.getBladeId()));
    }
  }
}

GfAppendInfo *GfGameMount::getAppendInfo() { return GfObjUtil::getAppendInfo(unknown10, unknown2c); }

u32 GfGameMount::getAllWeapons() const {
  u32 count = 0;
  for (u32 index = 0; index < 10; index++) {
    if (unknown18->unknown08[index] != unknown020) {
      count++;
    }
    if (unknown18->unknown58[index] != unknown020) {
      count++;
    }
  }
  return count;
}

GF_OBJ_HANDLE *GfGameMount::getAllWeapons(u32 index) const {
  u32 count = 0;
  for (u32 i = 0; i < 10; i++) {
    if (unknown18->unknown08[i] != unknown020) {
      if (count == index) {
        return unknown18->unknown08[i];
      }
      count++;
    }
    if (unknown18->unknown58[i] != unknown020) {
      if (count == index) {
        return unknown18->unknown58[i];
      }
      count++;
    }
  }
  return unknown020;
}

void GfGameMount::setWeaponOwner(GF_OBJ_HANDLE *owner) {
  for (u32 index = 0; index < 10; index++) {
    GF_OBJ_HANDLE *handle = unknown18->getCurrentHandles()[index];
    if (handle != unknown020) {
      GfObjUtil::setOwner(handle, owner);
    }
  }
}

bool GfGameMount::setWeaponOwner(OPTMNT type) {
  if (type < 5 && type != OPTMNT_UNKNOWN_3) {
    setWeaponOwner(getHandle(OPTMNT_UNKNOWN_2));
    return true;
  }
  return false;
}

bool GfGameMountBlade::execMount(OPTMNT type) {
  if (GfGameMount::execMount(type)) {
    return true;
  }
  if (type != OPTMNT_UNKNOWN_3) {
    return false;
  }
  if (GfObjUtil::getObj(unknown30) != nullptr) {
    detach();
    attach(OPTMNT_UNKNOWN_3, unknown30);
    unknown20 = OPTMNT_UNKNOWN_3;
  }
  return true;
}

GF_OBJ_HANDLE *GfGameMountBlade::getHandle(OPTMNT type) {
  GF_OBJ_HANDLE *handle;
  switch (type) {
  case OPTMNT_UNKNOWN_1:
  case OPTMNT_UNKNOWN_2:
  case OPTMNT_UNKNOWN_4:
    handle = unknown10;
    break;
  default:
    handle = unknown020;
    break;
  }
  if (type == OPTMNT_UNKNOWN_3 && handle == unknown020) {
    handle = unknown30;
  }
  return handle;
}

bool GfGameMountBlade::setWeaponOwner(OPTMNT type) {
  GF_OBJ_HANDLE *owner;
  switch (type) {
  case OPTMNT_UNKNOWN_0:
  case OPTMNT_UNKNOWN_1:
  case OPTMNT_UNKNOWN_2:
  case OPTMNT_UNKNOWN_4:
    owner = getHandle(OPTMNT_UNKNOWN_2);
    break;
  case OPTMNT_UNKNOWN_3:
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

GfMountManager::GfMountManager(const GfSetupParam &param) : unknown1a38(0), unknown1a40(false) { initialize(param); }

void GfMountManager::initialize(const GfSetupParam &) {
  GfObjManager::addListener(this, OBJEVT_UNKNOWN_0);
  unknown1a38 = 0;
  unknown1a40 = true;
}

void GfMountManager::build(const GfSetupParam &param) {
// __LINE__ must be 55 as in the original file: it is an argument of the allocation.
#line 55
  new (getAllocator(ALLOCATOR_UNKNOWN_1), __FILE__, __LINE__, 8) GfMountManager(param);
}

void GfMountManager::destroy() {
  GfMountManager *manager = get();
  manager->finalize();
  delete manager;
}

GF_MOUNT_HANDLE *GfMountManager::createMount(GF_OBJ_HANDLE *handle, GF_OBJ_HANDLE *blade, GFATTACH attach, OPTMNT type) {
  GfMountManager *manager = get();
// __LINE__ must be 107, 111 and 113 as in the original file: they are arguments of the allocations.
#line 107
  GfWeapon *weapon = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) GfWeapon;
  GfGameMount *mount;
  if (attach == GFATTACH_UNKNOWN_1) {
#line 111
    mount = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) GfGameMount(handle, weapon, type, attach);
  } else {
#line 113
    mount = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) GfGameMountBlade(handle, weapon, type, attach, blade);
  }
  MINFO info = {mount, manager->createHandle()};
  manager->unknown10.push_back(info);
  return info.unknown08;
}

GF_MOUNT_HANDLE *GfMountManager::createMount(GF_OBJ_HANDLE *handle, GFATTACH attach, OPTMNT type) { return createMount(handle, unknown020, attach, type); }

void GfMountManager::sendMessage(GF_OBJ_HANDLE *handle, GFATTACH attach, fw::MessageObject *receiver, fw::Message &message) {
  GfGameMount *mount = getMount(GfObjUtil::getMountHandle(handle, attach));
  if (mount != nullptr) {
    mount->unknown18->sendMessage(receiver, message);
  }
}

void GfMountManager::addMountHandle(GF_MOUNT_HANDLE *mountHandle, GF_OBJ_HANDLE *handle) {
  if (mountHandle != reinterpret_cast<GF_MOUNT_HANDLE *>(-1) && handle != unknown020) {
    GFOBJ_INFO *info = GfObjManager::getObjInfo(handle);
    if (info != nullptr) {
      GfGameMount *mount = getMount(mountHandle);
      mount->addRef();
      info->unknownb8[mount->unknown2c].unknown00 = mountHandle;
    }
  }
}

void GfMountManager::removeMountHandle(GF_OBJ_HANDLE *handle, GFATTACH attach) {
  GFOBJ_INFO *info = GfObjManager::getObjInfo(handle);
  if (info == nullptr) {
    return;
  }

  GF_MOUNT_HANDLE *mountHandle = info->unknownb8[attach].unknown00;
  if (mountHandle == reinterpret_cast<GF_MOUNT_HANDLE *>(-1)) {
    return;
  }

  info->unknownb8[attach].unknown00 = reinterpret_cast<GF_MOUNT_HANDLE *>(-1);
  mm::mtl::FixedList<MINFO, 256>::iterator it = get()->unknown10.begin();
  while (it->unknown08 != mountHandle) {
    ++it;
  }

  GfGameMount *mount = it->unknown00;
  mount->unknown18->eraseHandle(handle);
  int count = mount->getRefCount() - 1;
  if (count <= 0) {
    if (mount != nullptr) {
      mount->release();
    }

    destroyMount(mountHandle);
  } else if (mount != nullptr) {
    mount->release();
  }
}

GfMountManager::~GfMountManager() {}

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
  return unknown020;
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
  return unknown020;
}

GF_OBJ_HANDLE *GfMountManager::getOptionLeft(GF_OBJ_HANDLE *handle, GFATTACH attach) {
  if (GfObjUtil::getMountHandle(handle, attach) != reinterpret_cast<GF_MOUNT_HANDLE *>(-1)) {
    GfGameMount *mount = getMount(GfObjUtil::getMountHandle(handle, attach));
    if (mount != nullptr && mount->unknown18 != nullptr) {
      return mount->unknown18->getCurrentHandles()[1];
    }
  }
  return unknown020;
}

void GfMountManager::listenerGfObj(OBJEVT event, GF_OBJ_HANDLE *handle, u32) {
  if (event == OBJEVT_UNKNOWN_4) {
    for (int attach = GFATTACH_UNKNOWN_0; attach <= GFATTACH_UNKNOWN_3; attach++) {
      removeMountHandle(handle, static_cast<GFATTACH>(attach));
    }
  } else if (event == OBJEVT_UNKNOWN_3) {
    for (int attach = GFATTACH_UNKNOWN_0; attach <= GFATTACH_UNKNOWN_3; attach++) {
      execDetachMount(handle, static_cast<GFATTACH>(attach));
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

void GfMountManager::gevGameObjEnter(GF_OBJ_HANDLE *handle) {
  for (int attach = GFATTACH_UNKNOWN_0; attach <= GFATTACH_UNKNOWN_3; attach++) {
    get()->execAttachMount(handle, static_cast<GFATTACH>(attach));
  }
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
  case OBJECT_TYPE_PC:
  case OBJECT_TYPE_BLADE:
  case OBJECT_TYPE_ENEMY:
  case OBJECT_TYPE_PC_WEAPON:
  case OBJECT_TYPE_EN_WEAPON:
  case OBJECT_TYPE_OPTION:
    execMount(handle, attach, type);
    break;
  default:
    break;
  }
}

void GfMountManager::gevGameObjLeave(GF_OBJ_HANDLE *) {}

void GfMountManager::setAlphaMount(GF_OBJ_HANDLE *handle, GFATTACH attach, f32 alpha) {
  GfGameMount *mount = getMount(GfObjUtil::getMountHandle(handle, attach));
  if (mount == nullptr) {
    return;
  }
  for (u32 index = 0; index < 10; index++) {
    GF_OBJ_HANDLE *weapon = mount->unknown18->getCurrentHandles()[index];
    if (weapon != unknown020) {
      GfObjAcc acc(weapon);
      acc.setAlphaNormal(alpha);
    }
  }
}

void GfMountManager::setScaleMount(GF_OBJ_HANDLE *handle, GFATTACH attach, f32 scale) {
  GfGameMount *mount = getMount(GfObjUtil::getMountHandle(handle, attach));
  if (mount != nullptr) {
    mount->setScaleMount(scale);
  }
}

} // namespace gf

template mm::mtl::PtrSingleton<gf::GfMountManager>::~PtrSingleton();
