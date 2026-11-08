#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "mm_mtl/fixed_vector.h"
#include "types.h"
#include "ui/event/ui_object_listener.h"

namespace ui {
class UIObjectAcc;
class UISelectObjList;
class UIStr;
} // namespace ui

namespace gf {

class GfMenuItemList;

class GfMenuObjItemList2 : public GfMenuObject {
public:
  class MainListener : public ui::UIObjectListener {
  public:
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x20 - 0x0c];
    GfMenuObjItemList2 *unknown20; // Inferred role: owner; original member name unknown.
  };

  GfMenuObjItemList2(u32 handle);
  ~GfMenuObjItemList2() override;
  static void sendEvent(u32 handle, u32 type, u32 param, u32 delay);
  static int setFadeIn(u32 handle);
  static int setFadeOut(u32 handle);
  void initialize() override;
  void finalize() override;
  void update() override;
  static void setFadeOutSub(u32 handle);
  static void refreshItemList(ui::UIObjectAcc &acc, GfMenuItemList *list, ui::UISelectObjList *selectList);
  static void setupFilter(ui::UIObjectAcc &acc, u32 index);
  static void getFilterText(u32 index, ui::UIStr &text);

  u8 _24[0x28 - 0x24];
  GfMenuItemList *unknown28;               // Inferred role: item list; original member name unknown.
  ui::UISelectObjList *unknown30;          // Inferred role: item objects; original member name unknown.
  mm::mtl::FixedVector<int, 21> unknown38; // Inferred role: item types of the filter icons; original member name unknown.
  u64 unknown98;                           // Role and original member name unknown, cleared by the constructor.
  bool unknowna0;                          // Role and original member name unknown, set by the constructor.
};

static_assert(offsetof(GfMenuObjItemList2::MainListener, unknown20) == 0x20, "");
static_assert(offsetof(GfMenuObjItemList2, unknown28) == 0x28, "");
static_assert(offsetof(GfMenuObjItemList2, unknown30) == 0x30, "");
static_assert(offsetof(GfMenuObjItemList2, unknown38) == 0x38, "");
static_assert(offsetof(GfMenuObjItemList2, unknown98) == 0x98, "");
static_assert(offsetof(GfMenuObjItemList2, unknowna0) == 0xa0, "");

} // namespace gf
