#pragma once
#include "gf/menu/gf_menu_object.h"
#include "types.h"

namespace gf {

class GfMenuObjOpeningTelop : public GfMenuObject {
public:
  void initialize() override;
  void finalize() override;
  static void openCenter(u32 telop);
  static void closeCenter();
  static void openLeft(u32 telop);
  static void closeLeft();
  static void openRight(u32 telop);
  static void closeRight();
};

} // namespace gf
