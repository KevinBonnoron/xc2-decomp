#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "gf/menu/gf_menu_sequence.h"
#include "mm_math/mm_pnt.h"
#include "mm_math/mm_vec2.h"
#include "types.h"
#include "ui/event/ui_object_listener.h"

namespace ui {
class UICtrlCursorSelect;
class UISelectObjList;
} // namespace ui

namespace gf {

class GfMenuBladeList;
struct GAME_VOICE_HANDLE;

class GfMenuObjBladeBook : public GfMenuObject {
public:
  class MainListener : public ui::UIObjectListener {
  public:
    void reciveEvent(const ui::EventData &event, u32 handle) override;
  };

  GfMenuObjBladeBook(u32 handle);
  ~GfMenuObjBladeBook() override;
  void initialize() override;
  void finalize() override;
  void update() override;
  void stopVoice();
  void playVoice(const char *name);
  void getScreenOverSize(u32 handle, f32 scale, s16 &width, s16 &height);
  void refreshBladeList();
  bool seqOpenImage();
  bool seqEffReleaseA();
  bool seqEffReleaseB();
  bool seqEffReleaseC();
  bool seqEffReleaseD();
  bool seqConfirmBoosterGet();
  bool seqResumeRelease();
  bool seqConfirmRelease();
  bool seqExecRelease();

  u8 _24[0x28 - 0x24];
  GfMenuBladeList *unknown28;                      // Inferred role: blades; original member name unknown.
  ui::UISelectObjList *unknown30;                  // Inferred role: blade objects; original member name unknown.
  ui::UICtrlCursorSelect *unknown38;               // Inferred role: blade cursor; original member name unknown.
  GfMenuSequence<GfMenuObjBladeBook, 8> unknown40; // Inferred role: page steps; original member name unknown.
  bool unknown2d0;                                 // Role and original member name unknown, cleared by the constructor.
  u8 _2d1[0x2d8 - 0x2d1];
  GAME_VOICE_HANDLE *unknown2d8; // Inferred role: playing voice; original member name unknown.
  mm::Pnt<s16> unknown2e0;       // Role and original member name unknown, cleared by the constructor.
  u8 _2e4[0x2f0 - 0x2e4];
  mm::Vec2 unknown2f0; // Role and original member name unknown, cleared by the constructor.
  u8 _300[0x310 - 0x300];
};

static_assert(offsetof(GfMenuObjBladeBook, unknown28) == 0x28, "");
static_assert(offsetof(GfMenuObjBladeBook, unknown30) == 0x30, "");
static_assert(offsetof(GfMenuObjBladeBook, unknown38) == 0x38, "");
static_assert(offsetof(GfMenuObjBladeBook, unknown40) == 0x40, "");
static_assert(offsetof(GfMenuObjBladeBook, unknown2d0) == 0x2d0, "");
static_assert(offsetof(GfMenuObjBladeBook, unknown2d8) == 0x2d8, "");
static_assert(offsetof(GfMenuObjBladeBook, unknown2e0) == 0x2e0, "");
static_assert(offsetof(GfMenuObjBladeBook, unknown2f0) == 0x2f0, "");
static_assert(sizeof(GfMenuObjBladeBook) == 0x310, "");

bool isUnuseBlade(u32 blade);

} // namespace gf
