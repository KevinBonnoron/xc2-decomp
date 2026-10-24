#pragma once
#include "types.h"

namespace gf {

class GfMenuObjMainMenu2 {
public:
  struct OpenParam {
    u32 unknown00; // Inferred role: page; original member name unknown.
  };

  static void registOpenParam(const OpenParam &param);
};

} // namespace gf
