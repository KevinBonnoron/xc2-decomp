#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "types.h"
#include "ui/input/ui_input_layer.h"

namespace gf {

class GfMenuCallContext;

class GfMenuObjChainAttack : public GfMenuObject, public ui::IUIInputSelectionChecker {
public:
  GfMenuObjChainAttack(u32 handle);
  ~GfMenuObjChainAttack() override;
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
  bool isEnableSelect(u32 handle, int index) override;

  u64 unknown30; // Role and original member name unknown, cleared by the constructor.
  u64 unknown38; // Role and original member name unknown, cleared by the constructor.
  u64 unknown40; // Role and original member name unknown, cleared by the constructor.
  u64 unknown48; // Role and original member name unknown, cleared by the constructor.
  u32 unknown50; // Role and original member name unknown, cleared by the constructor.
};

static_assert(offsetof(GfMenuObjChainAttack, unknown30) == 0x30, "");
static_assert(offsetof(GfMenuObjChainAttack, unknown38) == 0x38, "");
static_assert(offsetof(GfMenuObjChainAttack, unknown40) == 0x40, "");
static_assert(offsetof(GfMenuObjChainAttack, unknown48) == 0x48, "");
static_assert(offsetof(GfMenuObjChainAttack, unknown50) == 0x50, "");
static_assert(sizeof(GfMenuObjChainAttack) == 0x58, "");

} // namespace gf
