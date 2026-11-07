#include "gf/object/gf_obj_factory.h"

#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_setup.h"
#include "gf/object/gf_obj_util.h"

namespace gf {

void GfObjFactory::destroyObj(GF_OBJ_HANDLE *handle) { GfObjUtil::destroy(handle); }

GF_OBJ_HANDLE *GfObjFactory::createDebugMap(const GfInitParamMap &) { return INVALID_HANDLE; }

void setSkelType(u32 type, GfObjSetup *setup) {
  s32 skelType;
  switch (type) {
  case 1:
    skelType = 0;
    break;
  case 2:
    skelType = 4;
    break;
  case 3:
    skelType = 1;
    break;
  case 4:
    skelType = 3;
    break;
  case 5:
    skelType = 5;
    break;
  case 6:
    skelType = 6;
    break;
  case 7:
    skelType = 7;
    break;
  case 8:
    skelType = 8;
    break;
  case 9:
    skelType = 9;
    break;
  case 10:
    skelType = 10;
    break;
  default:
    skelType = -1;
    break;
  }
  setup->unknown68 = skelType;
}

} // namespace gf
