#pragma once
#include "types.h"

namespace gf {

struct GF_OBJ_HANDLE;
class GfObjSetup;

class GfObjUtil {
public:
  static GfObjSetup *getObjSetup(GF_OBJ_HANDLE *handle);
  static u32 getHp(GF_OBJ_HANDLE *handle);
};

} // namespace gf
