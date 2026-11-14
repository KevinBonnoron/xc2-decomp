#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "gf/menu/gf_menu_sequence.h"
#include "mm_mtl/intrusive_ptr.h"
#include "types.h"
#include "ui/event/ui_object_listener.h"

namespace ui {
class UICtrlRevolveSelect;
class UISelectObjList;
struct EventData;
} // namespace ui

namespace gf {

class GfMenuBladeList;
class GfMenuCallContext;
class GfMenuIDList;
class GfMenuReferenceNumber;
class GfMenuReferenceQuest;

class GfMenuObjMercenaryTop : public GfMenuObject {
public:
  class MainListener : public ui::UIObjectListener {
  public:
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x20 - 0x0c];
    GfMenuObjMercenaryTop *unknown20; // Inferred role: owner; original member name unknown.
  };

  struct OpenParam {
    u32 unknown00; // Role and original member name unknown.
  };

  GfMenuObjMercenaryTop(u32 handle);
  ~GfMenuObjMercenaryTop() override;
  static void registOpenParam(const OpenParam &param);
  void sendOpenEvent(u32 handle, int type);
  void sendCloseEvent(u32 handle, int type);
  void listenerCtrl(const ui::EventData &event);
  bool seqExit();
  void updateMissionList();
  void refreshMissionList();
  void updateBladeList();
  void updateTargetTeam();
  bool seqUnitBreak();
  bool seqCanNotOrder();
  static void setDispUnitReady(u32 handle, u32 index);
  static void setDispUnitProgress(u32 handle, u32 index);
  static void setDispUnitReturn(u32 handle, u32 index);
  void initialize() override;
  void finalize() override;
  void update() override;

  u8 _24[0x28 - 0x24];
  GfMenuIDList *unknown28;            // Inferred role: identifiers; original member name unknown.
  GfMenuIDList *unknown30;            // Inferred role: identifiers; original member name unknown.
  GfMenuBladeList *unknown38;         // Inferred role: blades, not cleared by the constructor; original member name unknown.
  GfMenuBladeList *unknown40;         // Inferred role: blades, not cleared by the constructor; original member name unknown.
  ui::UISelectObjList *unknown48;     // Inferred role: list objects; original member name unknown.
  ui::UICtrlRevolveSelect *unknown50; // Inferred role: ring control; original member name unknown.
  f32 unknown58;                      // Inferred role: ring offset, set to 1.0 by the constructor; original member name unknown.
  u8 _5c[0x60 - 0x5c];
  ui::UISelectObjList *unknown60; // Inferred role: list objects; original member name unknown.
  ui::UISelectObjList *unknown68; // Inferred role: list objects; original member name unknown.
  ui::UISelectObjList *unknown70; // Inferred role: list objects; original member name unknown.
  u8 _78[0x80 - 0x78];
  mm::mtl::IntrusivePtr<GfMenuReferenceNumber> unknown80; // Inferred role: reference number; original member name unknown.
  mm::mtl::IntrusivePtr<GfMenuReferenceNumber> unknown88; // Inferred role: reference number; original member name unknown.
  mm::mtl::IntrusivePtr<GfMenuReferenceQuest> unknown90;  // Inferred role: quest reference; original member name unknown.
  GfMenuCallContext *unknown98;                           // Inferred role: call context; original member name unknown.
  GfMenuSequence<GfMenuObjMercenaryTop, 8> unknown0a0;    // Inferred role: queued steps; original member name unknown.
  bool unknown330;                                        // Role and original member name unknown, cleared by the constructor.
  u8 _331[0x334 - 0x331];
  u32 unknown334;                // Role and original member name unknown, cleared by the constructor.
  GfMenuCallContext *unknown338; // Inferred role: call context; original member name unknown.
  bool unknown340;               // Role and original member name unknown, set to true by the constructor.
};

static_assert(offsetof(GfMenuObjMercenaryTop, unknown28) == 0x28, "");
static_assert(offsetof(GfMenuObjMercenaryTop, unknown58) == 0x58, "");
static_assert(offsetof(GfMenuObjMercenaryTop, unknown80) == 0x80, "");
static_assert(offsetof(GfMenuObjMercenaryTop, unknown98) == 0x98, "");
static_assert(offsetof(GfMenuObjMercenaryTop, unknown0a0) == 0xa0, "");
static_assert(offsetof(GfMenuObjMercenaryTop, unknown330) == 0x330, "");
static_assert(offsetof(GfMenuObjMercenaryTop, unknown334) == 0x334, "");
static_assert(offsetof(GfMenuObjMercenaryTop, unknown338) == 0x338, "");
static_assert(offsetof(GfMenuObjMercenaryTop, unknown340) == 0x340, "");
static_assert(offsetof(GfMenuObjMercenaryTop::MainListener, unknown20) == 0x20, "");

} // namespace gf
