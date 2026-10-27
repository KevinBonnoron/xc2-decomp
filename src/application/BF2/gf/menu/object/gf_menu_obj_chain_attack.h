#pragma once
#include "gf/menu/gf_menu_object.h"
#include "types.h"

namespace gf {

class GfMenuObjChainAttack : public GfMenuObject {
public:
  static void closeResult();
  static void closeRoundExtend();
  static void openRoundExtend();
  static void closeStatus();
  static void changeCharacter(u32 character);
  void initialize() override;
  void finalize() override;
  void update() override;
};

} // namespace gf
