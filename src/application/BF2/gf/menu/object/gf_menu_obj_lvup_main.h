#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "gf/menu/gf_menu_sequence.h"
#include "gf/sound/gf_sound.h"
#include "types.h"
#include "ui/event/ui_object_listener.h"

namespace ui {
class UICtrlCursorSelect;
class UISelectObjList;
} // namespace ui
namespace gf {
class GfMenuCallContext;
class GfMenuDriverList;

class GfMenuObjLvupMain : public GfMenuObject {
public:
  class MainListener : public ui::UIObjectListener {
  public:
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x20 - 0x0c];
    GfMenuObjLvupMain *unknown20; // Inferred role: owner; original member name unknown.
  };

  GfMenuObjLvupMain(u32 handle);
  ~GfMenuObjLvupMain() override;
  void initialize() override;
  void finalize() override;
  void update() override;
  void refreshLevelUpInfo();
  bool seqClose2();
  bool seqClose3();
  bool seqEndLevelUp();
  bool seqExecLevelUp();

  u8 _24[0x28 - 0x24];
  ui::UISelectObjList *unknown28;    // Inferred role: mode tag objects; original member name unknown.
  GfMenuDriverList *unknown30;       // Inferred role: driver list; original member name unknown.
  ui::UISelectObjList *unknown38;    // Inferred role: driver info objects; original member name unknown.
  ui::UICtrlCursorSelect *unknown40; // Inferred role: driver info cursor; original member name unknown.
  u32 unknown48;                     // Inferred role: selected driver, 0xff when none; original member name unknown.
  u8 _4c[0x50 - 0x4c];
  GfMenuSequence<GfMenuObjLvupMain, 8> unknown50; // Inferred role: level up and close steps; original member name unknown.
  bool unknown2e0;                                // Inferred role: unused; original member name unknown.
  u8 _2e1[0x2e4 - 0x2e1];
  u32 unknown2e4; // Inferred role: unused; original member name unknown.
  u8 _2e8[0x2f0 - 0x2e8];
  GfMenuCallContext *unknown2f0; // Inferred role: call context; original member name unknown.
  GfMenuCallContext *unknown2f8; // Inferred role: call context; original member name unknown.
  bool unknown300;               // Inferred role: unused; original member name unknown.
  u8 _301[0x304 - 0x301];
  SoundHandle unknown304; // Inferred role: level up jingle; original member name unknown.
};

static_assert(offsetof(GfMenuObjLvupMain, unknown28) == 0x28, "");
static_assert(offsetof(GfMenuObjLvupMain, unknown30) == 0x30, "");
static_assert(offsetof(GfMenuObjLvupMain, unknown38) == 0x38, "");
static_assert(offsetof(GfMenuObjLvupMain, unknown40) == 0x40, "");
static_assert(offsetof(GfMenuObjLvupMain, unknown48) == 0x48, "");
static_assert(offsetof(GfMenuObjLvupMain, unknown50) == 0x50, "");
static_assert(offsetof(GfMenuObjLvupMain::MainListener, unknown20) == 0x20, "");
static_assert(offsetof(GfMenuObjLvupMain, unknown2e0) == 0x2e0, "");
static_assert(offsetof(GfMenuObjLvupMain, unknown2e4) == 0x2e4, "");
static_assert(offsetof(GfMenuObjLvupMain, unknown2f0) == 0x2f0, "");
static_assert(offsetof(GfMenuObjLvupMain, unknown2f8) == 0x2f8, "");
static_assert(offsetof(GfMenuObjLvupMain, unknown300) == 0x300, "");
static_assert(offsetof(GfMenuObjLvupMain, unknown304) == 0x304, "");
static_assert(sizeof(GfMenuObjLvupMain) == 0x310, "");

} // namespace gf
