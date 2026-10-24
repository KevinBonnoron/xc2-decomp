#pragma once

namespace gf {

struct GF_OBJ_HANDLE;

class GfMenuObjChainIcon {
public:
  struct OpenParam {
    GF_OBJ_HANDLE *unknown00; // Inferred role: handle; original member name unknown.
  };

  static void open(const OpenParam &param);
};

} // namespace gf
