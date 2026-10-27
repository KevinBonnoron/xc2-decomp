#pragma once
#include "gf/menu/gf_menu_object.h"
#include "types.h"

namespace gf {

class GfMenuCallContext;

class GfMenuObjDummyTutorial : public GfMenuObject {
public:
  void initialize() override;
  void finalize() override;
  void update() override;
  struct OpenParam {
    u32 unknown00; // Inferred role: tutorial; original member name unknown.
  };

  static void open(GfMenuCallContext *context, const OpenParam &param);
};

} // namespace gf
