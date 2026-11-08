#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "gf/menu/gf_menu_sequence.h"
#include "mm_mtl/fixed_vector.h"
#include "types.h"

namespace ui {
class UISelectObjList;
} // namespace ui

namespace gf {
class GfMenuCallContext;

class GfMenuObjTitle : public GfMenuObject {
public:
  GfMenuObjTitle(u32 handle);
  ~GfMenuObjTitle() override;
  static bool attach(GfMenuCallContext *context);
  void initialize() override;
  void finalize() override;
  void update() override;
  bool seqConfirmNewGame();

  static bool isEnableNewGame();
  static bool isEnableNewGameAdv();
  static bool isEnableContinue();
  static bool isEnableOption();
  static void setDispMode(u32 handle, int mode);
  static void setInputMode(u32 handle, int mode);

  static bool s_NoSaveData;

  u8 _24[0x28 - 0x24];
  mm::mtl::FixedVector<int, 5> unknown28; // Inferred role: enabled menu entries; original member name unknown.
  u32 unknown48;                          // Inferred role: call context type returned with the confirmation result; original member name unknown.
  u8 _4c[0x50 - 0x4c];
  ui::UISelectObjList *unknown50;              // Inferred role: menu objects; original member name unknown.
  GfMenuSequence<GfMenuObjTitle, 4> unknown58; // Inferred role: queued steps; original member name unknown.
  bool unknown1b8;                             // Inferred role: confirmation window opened; original member name unknown.
};

static_assert(offsetof(GfMenuObjTitle, unknown28) == 0x28, "");
static_assert(offsetof(GfMenuObjTitle, unknown48) == 0x48, "");
static_assert(offsetof(GfMenuObjTitle, unknown50) == 0x50, "");
static_assert(offsetof(GfMenuObjTitle, unknown58) == 0x58, "");
static_assert(offsetof(GfMenuObjTitle, unknown1b8) == 0x1b8, "");
static_assert(sizeof(GfMenuObjTitle) == 0x1c0, "");

} // namespace gf
