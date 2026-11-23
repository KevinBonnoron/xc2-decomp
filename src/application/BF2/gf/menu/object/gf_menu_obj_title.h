#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "gf/menu/gf_menu_sequence.h"
#include "mm_mtl/fixed_vector.h"
#include "types.h"
#include "ui/event/ui_object_listener.h"

namespace ui {
class UISelectObjList;
} // namespace ui

namespace gf {
class GfMenuCallContext;

class GfMenuObjTitle : public GfMenuObject {
public:
  class ListListener : public ui::UIObjectListener {
  public:
    ListListener(GfMenuObjTitle *owner) : unknown0c(0), _10(), m_menuObjTitle(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    int unknown0c; // Inferred role: input state (0 key wait, 1 list, 2 decided); original member name unknown.
    u8 _10[0x1c - 0x10];
    u8 _1c[0x20 - 0x1c];
    GfMenuObjTitle *m_menuObjTitle; // Inferred role: owner; original member name unknown.
  };

  GfMenuObjTitle(u32 handle);
  ~GfMenuObjTitle() override;
  static bool attach(GfMenuCallContext *context);
  void initialize() override;
  void finalize() override;
  void update() override;
  bool seqConfirmNewGame();
  void moveCursor(u32 handle, int index);

  static bool isEnableNewGame();
  static bool isEnableNewGameAdv();
  static bool isEnableEventsTheater();
  static bool isEnableContinue();
  static bool isEnableOption();
  static void setDispMode(u32 handle, int mode);
  static void setInputMode(u32 handle, int mode);

  static bool s_NoSaveData;

  u8 _24[0x28 - 0x24];
  mm::mtl::FixedVector<u32, 5> unknown28; // Inferred role: enabled menu entries; u32 since moveCursor (0x71004dda94) loads an entry zero-extended; original member name unknown.
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
static_assert(offsetof(GfMenuObjTitle::ListListener, unknown0c) == 0xc, "");
static_assert(offsetof(GfMenuObjTitle::ListListener, m_menuObjTitle) == 0x20, "");
static_assert(sizeof(GfMenuObjTitle::ListListener) == 0x28, "");

} // namespace gf
