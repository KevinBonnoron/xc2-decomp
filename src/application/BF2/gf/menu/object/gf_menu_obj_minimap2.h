#pragma once
#include "gf/menu/gf_menu_object.h"

namespace gf {

class GfMenuObjMinimap2 : public GfMenuObject {
public:
  static void changeMap();
  static void close();
  static void open();
  void initialize() override;
  void finalize() override;

  static void enable();
  static void disable();
};

} // namespace gf
