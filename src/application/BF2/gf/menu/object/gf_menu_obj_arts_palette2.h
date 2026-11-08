#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "mm_mtl/intrusive_ptr.h"
#include "types.h"

namespace ui {
class UICtrlCursorSelect;
class UISelectObjList;
} // namespace ui

namespace gf {
class GfMenuCallContext;
class GfMenuReferenceNumber;

class GfMenuObjArtsPalette2 : public GfMenuObject {
public:
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

  int unknown24;                                          // Inferred role: unused, -1 at start; original member name unknown.
  ui::UISelectObjList *unknown28;                         // Inferred role: arts objects; original member name unknown.
  ui::UICtrlCursorSelect *unknown30;                      // Inferred role: arts cursor; original member name unknown.
  u64 unknown38;                                          // Role and original member name unknown, cleared by the constructor.
  u64 unknown40;                                          // Role and original member name unknown, cleared by the constructor.
  u64 unknown48;                                          // Role and original member name unknown, cleared by the constructor.
  mm::mtl::IntrusivePtr<GfMenuReferenceNumber> unknown50; // Inferred role: reference number; original member name unknown.
};

static_assert(offsetof(GfMenuObjArtsPalette2, unknown24) == 0x24, "");
static_assert(offsetof(GfMenuObjArtsPalette2, unknown28) == 0x28, "");
static_assert(offsetof(GfMenuObjArtsPalette2, unknown30) == 0x30, "");
static_assert(offsetof(GfMenuObjArtsPalette2, unknown38) == 0x38, "");
static_assert(offsetof(GfMenuObjArtsPalette2, unknown40) == 0x40, "");
static_assert(offsetof(GfMenuObjArtsPalette2, unknown48) == 0x48, "");
static_assert(offsetof(GfMenuObjArtsPalette2, unknown50) == 0x50, "");

} // namespace gf
