#pragma once
#include "types.h"

namespace gf {

class GfMenuObjMainMenu2 {
public:
  struct OpenParam {
    u32 page;
  };

  static void registOpenParam(const OpenParam &param);
};

} // namespace gf
