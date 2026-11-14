#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "gf/menu/gf_menu_sequence.h"
#include "mm_mtl/fixed_vector.h"
#include "types.h"
#include "ui/event/ui_object_listener.h"

namespace ui {
class UICtrlObject;
class UISelectObjList;
struct EventData;
} // namespace ui

namespace gf {

class GfMenuCallContext;

class GfMenuObjMainMenu : public GfMenuObject {
public:
  // Inferred role: layer parameter read when the menu opens; original type name unknown.
  struct unknown001 {
    u16 unknown00; // Inferred role: selected menu; original member name unknown.
  };

  class MainListener : public ui::UIObjectListener {
  public:
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x1c - 0x0c];
    GfMenuObjMainMenu *unknown20; // Inferred role: owner; original member name unknown.
  };

  GfMenuObjMainMenu(u32 handle);
  ~GfMenuObjMainMenu() override;
  void initialize() override;
  void finalize() override;
  void update() override;
  void suspendInput();
  void resumeInput();
  bool seqStartOpen();
  bool seqAppearPhase1();
  bool seqAppearPhase2();
  bool seqAppearPhase3();
  bool seqAppearPhase4();
  bool seqEndCommon();
  bool seqStartCommon();
  bool seqCloseJog();
  bool seqOpenJog();
  bool seqSwapPhase2();
  void listenerPartySelect(const ui::EventData &event);
  void setBustupCtrlChar(u32 character, u32 flag, bool isDisp);

  u8 _24[0x28 - 0x24];
  mm::mtl::FixedVector<int, 12> unknown28; // Inferred role: menu entries; original member name unknown.
  u8 _60[0x68 - 0x60];
  GfMenuSequence<GfMenuObjMainMenu, 8> unknown68; // Inferred role: appear, swap and close steps; original member name unknown.
  int unknown2f8;                                 // Inferred role: control of the current step, -1 when idle; original member name unknown.
  GfMenuCallContext *unknown300;                  // Inferred role: call context; original member name unknown.
  u32 unknown308;                                 // Role and original member name unknown, cleared by the constructor.
  u32 unknown30c;                                 // Inferred role: input suspend state set by the layer events; original member name unknown.
  u32 unknown310;                                 // Role and original member name unknown, cleared by the constructor.
  u8 _314[0x318 - 0x314];
  ui::UICtrlObject *unknown318;    // Inferred role: party select control; original member name unknown.
  ui::UISelectObjList *unknown320; // Inferred role: party objects; original member name unknown.
  u32 unknown328;                  // Role and original member name unknown, cleared by the constructor.
  u8 _32c[0x330 - 0x32c];
  mm::mtl::FixedVector<u32, 3> unknown330; // Inferred role: party members; original member name unknown.
  u8 _348[0x350 - 0x348];
  u32 unknown350; // Inferred role: unused, 0xffffffff at start; original member name unknown.
  u32 unknown354; // Role and original member name unknown, cleared by the constructor.
};

static_assert(offsetof(GfMenuObjMainMenu::MainListener, unknown20) == 0x20, "");
static_assert(sizeof(GfMenuObjMainMenu::MainListener) == 0x28, "");

static_assert(sizeof(GfMenuObjMainMenu::unknown001) == 0x02, "");
static_assert(offsetof(GfMenuObjMainMenu, unknown28) == 0x28, "");
static_assert(offsetof(GfMenuObjMainMenu, unknown68) == 0x68, "");
static_assert(offsetof(GfMenuObjMainMenu, unknown2f8) == 0x2f8, "");
static_assert(offsetof(GfMenuObjMainMenu, unknown300) == 0x300, "");
static_assert(offsetof(GfMenuObjMainMenu, unknown308) == 0x308, "");
static_assert(offsetof(GfMenuObjMainMenu, unknown30c) == 0x30c, "");
static_assert(offsetof(GfMenuObjMainMenu, unknown310) == 0x310, "");
static_assert(offsetof(GfMenuObjMainMenu, unknown318) == 0x318, "");
static_assert(offsetof(GfMenuObjMainMenu, unknown320) == 0x320, "");
static_assert(offsetof(GfMenuObjMainMenu, unknown328) == 0x328, "");
static_assert(offsetof(GfMenuObjMainMenu, unknown330) == 0x330, "");
static_assert(offsetof(GfMenuObjMainMenu, unknown350) == 0x350, "");
static_assert(offsetof(GfMenuObjMainMenu, unknown354) == 0x354, "");

} // namespace gf
