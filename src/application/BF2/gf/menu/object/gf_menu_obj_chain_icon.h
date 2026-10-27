#pragma once
#include "gf/menu/gf_menu_object.h"

namespace gf {

struct GF_OBJ_HANDLE;

class GfMenuObjChainIcon : public GfMenuObject {
public:
  void initialize() override;
  void finalize() override;
  void update() override;
  struct OpenParam {
    GF_OBJ_HANDLE *unknown00; // Inferred role: handle; original member name unknown.
  };

  static void open(const OpenParam &param);
};

} // namespace gf
