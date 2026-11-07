#pragma once
#include "gf/menu/gf_menu_object.h"
#include "types.h"

namespace gf {

class GfMenuCallContext;

class GfMenuObjChainAttack : public GfMenuObject {
public:
  static void openStatus(GfMenuCallContext *context);
  static void openStart(GfMenuCallContext *context);
  static void openFullBurst(GfMenuCallContext *context);
  static void closeTurnSelect(GfMenuCallContext *context);
  static void closeResult();
  static void closeRoundExtend();
  static void openRoundExtend();
  static void closeStatus();
  static void changeCharacter(u32 character);
  void initialize() override;
  void finalize() override;
  void update() override;
  bool isEnableSelect(u32 handle, int index);
};

} // namespace gf
