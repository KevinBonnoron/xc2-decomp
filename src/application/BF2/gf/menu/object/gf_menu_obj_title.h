#pragma once
#include "gf/menu/gf_menu_object.h"

namespace gf {

class GfMenuObjTitle : public GfMenuObject {
public:
  void initialize() override;
  void finalize() override;

  static bool isEnableNewGame();
  static bool isEnableNewGameAdv();
  static bool isEnableContinue();
  static bool isEnableOption();

  static bool s_NoSaveData;
};

} // namespace gf
