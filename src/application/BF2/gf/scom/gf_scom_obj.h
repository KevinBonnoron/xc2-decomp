#pragma once
#include "types.h"

namespace gf {

struct GF_OBJ_HANDLE;

class SCOM_DESTROY_GAME_OBJ {
public:
  static void create(GF_OBJ_HANDLE *handle, f32 fadeTime, u32 attribute);
};

} // namespace gf
