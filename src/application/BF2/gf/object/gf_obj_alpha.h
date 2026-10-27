#pragma once
#include "types.h"

namespace gf {

struct GF_OBJ_HANDLE;
class GfComProperty;

class GfObjAlpha {
public:
  static void updateCamera(GF_OBJ_HANDLE *handle, f32 deltaTime, bool isForce);
  static f32 getTotalAlpha(const GfComProperty *property);
};

} // namespace gf
