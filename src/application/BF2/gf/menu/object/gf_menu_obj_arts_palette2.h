#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "mm_mtl/bitflag.h"
#include "mm_mtl/intrusive_ptr.h"
#include "types.h"
#include "ui/event/ui_object_listener.h"

namespace ui {
class UICtrlCursorSelect;
class UISelectObjList;
} // namespace ui

namespace gf {
class GfMenuCallContext;
class GfMenuReferenceNumber;

class GfMenuObjArtsPalette2 : public GfMenuObject {
public:
  class MainListener : public ui::UIObjectListener {
  public:
    // Inferred role: cursor display state and selection flag; original type name unknown.
    struct unknown004 {
      int unknown00; // Inferred role: cursor display state, 0 hidden and 1 shown; original member name unknown.
      int unknown04; // Inferred role: selection flag of the last 0x100 event; original member name unknown.
    };

    MainListener(GfMenuObjArtsPalette2 *owner) : unknown0c(0), unknown10(), _18(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    int unknown0c; // Inferred role: control of the cursor display, -1 when none; original member name unknown.
    unknown004 unknown10;
    u8 _18[0x1c - 0x18];              // Actively zero-initialized unknown byte range, NOT padding; original name/role unknown.
    GfMenuObjArtsPalette2 *unknown20; // Inferred role: owner; original member name unknown.
  };

  GfMenuObjArtsPalette2(u32 handle);
  ~GfMenuObjArtsPalette2() override;
  static void attachCallContext(GfMenuCallContext *context);
  static void close();
  static void open();
  static void resetSelection();
  static void setArtsSelection(GfMenuCallContext *context, bool isSelection);
  void initialize() override;
  void finalize() override;
  void update() override;

  int unknown24;                     // Inferred role: control of the third party gauge, -1 at start; original member name unknown.
  ui::UISelectObjList *unknown28;    // Inferred role: arts objects; original member name unknown.
  ui::UICtrlCursorSelect *unknown30; // Inferred role: arts cursor; original member name unknown.
  union {
    u64 unknown38_u64; // 64-bit view of the selected row and the row of the last button event: the button event handler loads both with one 64-bit load; original member name unknown.
    struct {
      u32 unknown38; // Inferred role: selected row; original member name unknown.
      u32 unknown3c; // Inferred role: row of the last button event; original member name unknown.
    };
  };
  u32 unknown40;                                          // Inferred role: column kind of the selection, 0 left, 1 middle and 2 right; original member name unknown.
  u32 unknown44;                                          // Role and original member name unknown, cleared by the constructor.
  mm::mtl::unknown027<32> unknown48;                      // Inferred role: arts slot flags set by the recast events; original member name unknown.
  mm::mtl::unknown027<32> unknown4c;                      // Inferred role: arts slot flags set by the special level events; original member name unknown.
  mm::mtl::IntrusivePtr<GfMenuReferenceNumber> unknown50; // Inferred role: reference number; original member name unknown.
};

static_assert(offsetof(GfMenuObjArtsPalette2, unknown24) == 0x24, "");
static_assert(offsetof(GfMenuObjArtsPalette2, unknown28) == 0x28, "");
static_assert(offsetof(GfMenuObjArtsPalette2, unknown30) == 0x30, "");
static_assert(offsetof(GfMenuObjArtsPalette2, unknown38) == 0x38, "");
static_assert(offsetof(GfMenuObjArtsPalette2, unknown38_u64) == 0x38, "");
static_assert(offsetof(GfMenuObjArtsPalette2, unknown3c) == 0x3c, "");
static_assert(offsetof(GfMenuObjArtsPalette2, unknown40) == 0x40, "");
static_assert(offsetof(GfMenuObjArtsPalette2, unknown44) == 0x44, "");
static_assert(offsetof(GfMenuObjArtsPalette2, unknown48) == 0x48, "");
static_assert(offsetof(GfMenuObjArtsPalette2, unknown4c) == 0x4c, "");
static_assert(offsetof(GfMenuObjArtsPalette2, unknown50) == 0x50, "");
static_assert(offsetof(GfMenuObjArtsPalette2::MainListener, unknown20) == 0x20, "");
static_assert(sizeof(GfMenuObjArtsPalette2::MainListener) == 0x28, "");

} // namespace gf
