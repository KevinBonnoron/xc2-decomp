#pragma once
#include "types.h"

namespace gf {

class GfMenuObjSaveLoad2 {
public:
  struct OpenParam {
    u16 mode;
  };

  static void registOpenParam(const OpenParam &param);
};

} // namespace gf
