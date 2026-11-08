#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "gf/menu/gf_menu_reference_list.h"
#include "mm_mtl/intrusive_ptr.h"
#include "types.h"

namespace ui {
class UICtrlCursorSelect;
class UICtrlSlideSelect;
class UISelectObjList;
} // namespace ui

namespace gf {

class GfMenuItemList;

class GfMenuObjItemList : public GfMenuObject {
public:
  GfMenuObjItemList(u32 handle);
  ~GfMenuObjItemList() override;
  void initialize() override;
  void finalize() override;
  void update() override;

  u8 _24[0x28 - 0x24];
  ui::UISelectObjList *unknown28;                                       // Inferred role: item objects; original member name unknown.
  ui::UICtrlCursorSelect *unknown30;                                    // Inferred role: item cursor; original member name unknown.
  ui::UISelectObjList *unknown38;                                       // Inferred role: tab objects; original member name unknown.
  ui::UICtrlSlideSelect *unknown40;                                     // Inferred role: tab slider; original member name unknown.
  GfMenuItemList *unknown48[21];                                        // Inferred role: item lists of the tabs; original member name unknown.
  mm::mtl::IntrusivePtr<GfMenuReferenceList<GfMenuItemList>> unknownf0; // Inferred role: reference to the first item list; original member name unknown.
};

static_assert(offsetof(GfMenuObjItemList, unknown28) == 0x28, "");
static_assert(offsetof(GfMenuObjItemList, unknown30) == 0x30, "");
static_assert(offsetof(GfMenuObjItemList, unknown38) == 0x38, "");
static_assert(offsetof(GfMenuObjItemList, unknown40) == 0x40, "");
static_assert(offsetof(GfMenuObjItemList, unknown48) == 0x48, "");
static_assert(offsetof(GfMenuObjItemList, unknownf0) == 0xf0, "");

} // namespace gf
