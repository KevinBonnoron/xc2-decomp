#pragma once
#include "types.h"

namespace ml {

class DrPixlPostObjCubeMapIBL {
public:
  void render();
  void setUniformBlock(u32 index) const;
};

} // namespace ml
