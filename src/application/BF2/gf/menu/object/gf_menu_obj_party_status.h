#pragma once
#include "gf/menu/gf_menu_object.h"

namespace gf {

class GfMenuCallContext;

class GfMenuObjPartyStatus : public GfMenuObject {
public:
  void initialize() override;
  void finalize() override;
  void update() override;
  static void lock(bool lock);
  static void attachComboRequest(GfMenuCallContext *context);
};

} // namespace gf
