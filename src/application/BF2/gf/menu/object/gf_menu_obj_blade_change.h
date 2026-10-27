#pragma once
#include "gf/menu/gf_menu_object.h"

namespace gf {

class GfMenuObjBladeChange : public GfMenuObject {
public:
  static void close();
  static void exitChainAttack();
  static void open();
  static void pushGroupUp();
  void initialize() override;
  void finalize() override;
  static void enableAwakening(bool);
  static void pushBladeChange(unsigned int blade);
};

} // namespace gf
