#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/intrusive_ptr.h"
#include "types.h"

namespace ui {
class UICtrlCursorSelect;
class UICtrlSlideSelect;
class UISelectObjList;
} // namespace ui

namespace gf {
class GfMenuCallContext;
class GfMenuReferenceNumber;

class GfMenuObjDrArtsSet : public GfMenuObject {
public:
  GfMenuObjDrArtsSet(u32 handle);
  ~GfMenuObjDrArtsSet() override;
  static bool attach(GfMenuCallContext *context);
  static void sendEvent(u32 handle, u32 type, u32 param);
  static int setFadeIn(u32 handle);
  static int setFadeOut(u32 handle);
  void initialize() override;
  void finalize() override;
  void update() override;

  u8 _24[0x28 - 0x24];
  ui::UISelectObjList *unknown28;                         // Inferred role: arts objects; original member name unknown.
  ui::UICtrlSlideSelect *unknown30;                       // Inferred role: weapon type slider; original member name unknown.
  mm::mtl::IntrusivePtr<GfMenuReferenceNumber> unknown38; // Inferred role: reference number; original member name unknown.
  mm::mtl::IntrusivePtr<GfMenuReferenceNumber> unknown40; // Inferred role: reference number; original member name unknown.
  ui::UICtrlCursorSelect *unknown48;                      // Inferred role: arts cursor; original member name unknown.
  mm::mtl::FixedVector<u32, 27> unknown50;                // Inferred role: weapon types; original member name unknown.
  GfMenuCallContext *unknownc8;                           // Inferred role: call context; original member name unknown.
};

static_assert(offsetof(GfMenuObjDrArtsSet, unknown28) == 0x28, "");
static_assert(offsetof(GfMenuObjDrArtsSet, unknown30) == 0x30, "");
static_assert(offsetof(GfMenuObjDrArtsSet, unknown38) == 0x38, "");
static_assert(offsetof(GfMenuObjDrArtsSet, unknown40) == 0x40, "");
static_assert(offsetof(GfMenuObjDrArtsSet, unknown48) == 0x48, "");
static_assert(offsetof(GfMenuObjDrArtsSet, unknown50) == 0x50, "");
static_assert(offsetof(GfMenuObjDrArtsSet, unknownc8) == 0xc8, "");

} // namespace gf
