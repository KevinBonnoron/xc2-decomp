#pragma once
#include "gf/menu/gf_menu_object.h"
#include "types.h"

namespace gf {

class GfMenuCallContext;

class GfMenuObjElementEff : public GfMenuObject {
public:
  void initialize() override;
  void finalize() override;
  struct StartParam {
    u32 attribute;
  };

  static void start(GfMenuCallContext *context, const StartParam &param);
  static void cancel(GfMenuCallContext *context);
};

} // namespace gf
