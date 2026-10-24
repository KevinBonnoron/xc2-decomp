#pragma once
#include "types.h"

namespace gf {

class GfMenuObjSaveLoad2 {
public:
  struct OpenParam {
    u16 unknown00; // Inferred role: mode; original member name unknown.
  };

  static void registOpenParam(const OpenParam &param);
};

} // namespace gf
