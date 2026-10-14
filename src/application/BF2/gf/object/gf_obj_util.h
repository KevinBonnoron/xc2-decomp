#pragma once
#include "gf/object/gf_obj_manager.h"
#include "gf/object/gf_obj_setup.h"
#include "types.h"

namespace gf {

struct GF_OBJ_HANDLE;

class GfObjUtil {
public:
  static GfObjSetup *getObjSetup(GF_OBJ_HANDLE *handle);
  static u32 getHp(GF_OBJ_HANDLE *handle);
  static bool testFlag(GF_OBJ_HANDLE *handle, u32 flag);

  template <typename T> static T *getObjSetup(GF_OBJ_HANDLE *handle) {
    GFOBJ_INFO *info = GfObjManager::getObjInfo(handle);
    if (info == nullptr || info->setup == nullptr) {
      return nullptr;
    }

    if (info->setup->objType != info->property->objType || info->property->objType != T::OBJECT_TYPE) {
      return nullptr;
    }

    return mm::mtl::dynamicCast<T>(info->setup);
  }
};

} // namespace gf
