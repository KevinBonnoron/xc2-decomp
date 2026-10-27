#pragma once
#include "gf/menu/gf_menu_object.h"

namespace gf {

class GfMenuObjTutorial : public GfMenuObject {
public:
  static void closeAll();
  void initialize() override;
  void finalize() override;
  static bool isWaiting();
};

} // namespace gf
