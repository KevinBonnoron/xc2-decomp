#pragma once

namespace gf {

struct GF_OBJ_HANDLE;

class GfMenuObjChainIcon {
public:
  struct OpenParam {
    GF_OBJ_HANDLE *handle;
  };

  static void open(const OpenParam &param);
};

} // namespace gf
