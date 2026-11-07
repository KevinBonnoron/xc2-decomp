#pragma once
#include "gf/menu/gf_menu_object.h"

namespace gf {
class GfMenuCallContext;

class GfMenuObjBladeChange : public GfMenuObject {
public:
  static void close();
  static void startChainAttack(GfMenuCallContext *context);
  static void exitChainAttack();
  static void open();
  static void pushGroupUp();
  void initialize() override;
  void finalize() override;
  void update() override;
  static void enableAwakening(bool);
  static void pushBladeChange(unsigned int blade);
  static void dispInfo(bool isDisp);
};

} // namespace gf
