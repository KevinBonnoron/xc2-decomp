#pragma once
#include "types.h"

namespace gf {

class GfMenuObjMainRoot {
public:
  struct OpenParam {
    u32 menu;
  };

  static void registOpenParam(const OpenParam &param);
};

} // namespace gf
