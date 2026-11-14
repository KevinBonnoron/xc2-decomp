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
    MainListener(GfMenuObjItemList2 *owner) : _0c(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x1c - 0x0c];           // Actively zero-initialized unknown byte range, NOT padding; original name/role unknown.
    GfMenuObjItemList2 *unknown20; // Inferred role: owner; original member name unknown.
  };

  class ItemListListener : public ui::UIObjectListener {
  public:
    ItemListListener(GfMenuObjItemList2 *owner) : unknown0c(0), _10(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u32 unknown0c;                 // Inferred role: index of the selected sort; original member name unknown.
    u8 _10[0x1c - 0x10];           // Actively zero-initialized unknown byte range, NOT padding; original name/role unknown.
    GfMenuObjItemList2 *unknown20; // Inferred role: owner; original member name unknown.
  };

  class FilterListener : public ui::UIObjectListener {
  public:
    FilterListener(GfMenuObjItemList2 *owner) : _0c(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x1c - 0x0c];           // Actively zero-initialized unknown byte range, NOT padding; original name/role unknown.
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
  static void setupItemList(ui::UIObjectAcc &acc, GfMenuItemList *list, ui::UISelectObjList *selectList);
  static void updateItemList(GfMenuItemList *list, ui::UISelectObjList *selectList, u32 filter, u32 sort);
  static void refreshItemList(ui::UIObjectAcc &acc, GfMenuItemList *list, ui::UISelectObjList *selectList);
  static void setupFilter(ui::UIObjectAcc &acc, u32 index);
  static void getFilterText(u32 index, ui::UIStr &text);
  void refreshFilterIcon();

  u8 _24[0x28 - 0x24];
  GfMenuItemList *unknown28;      // Inferred role: item list; original member name unknown.
  ui::UISelectObjList *unknown30; // Inferred role: item objects; original member name unknown.
  // Inferred role: filter of each shown filter icon, an index of the filter tables; original member name unknown. The elements are u32: initialize fills it from its u32 counter, they are the
  // unsigned int argument of getFilterText(unsigned int, UIStr &) and updateItemList(..., unsigned int, unsigned int) (mangled symbols), and ItemListListener::reciveEvent zero-extends the index
  // (ldr w8 at 0x710047c0d0, ldrsw with int).
  mm::mtl::FixedVector<u32, 21> unknown38;
  u32 unknown98;  // Inferred role: selected filter; original member name unknown.
  u32 unknown9c;  // Role and original member name unknown, cleared by the constructor.
  bool unknowna0; // Role and original member name unknown, set by the constructor.
};

static_assert(offsetof(GfMenuObjItemList2::MainListener, unknown20) == 0x20, "");
static_assert(offsetof(GfMenuObjItemList2::ItemListListener, unknown0c) == 0x0c, "");
static_assert(offsetof(GfMenuObjItemList2::ItemListListener, unknown20) == 0x20, "");
static_assert(sizeof(GfMenuObjItemList2::ItemListListener) == 0x28, "");
static_assert(offsetof(GfMenuObjItemList2::FilterListener, unknown20) == 0x20, "");
static_assert(sizeof(GfMenuObjItemList2::FilterListener) == 0x28, "");
static_assert(offsetof(GfMenuObjItemList2, unknown28) == 0x28, "");
static_assert(offsetof(GfMenuObjItemList2, unknown30) == 0x30, "");
static_assert(offsetof(GfMenuObjItemList2, unknown38) == 0x38, "");
static_assert(offsetof(GfMenuObjItemList2, unknown98) == 0x98, "");
static_assert(offsetof(GfMenuObjItemList2, unknown9c) == 0x9c, "");
static_assert(offsetof(GfMenuObjItemList2, unknowna0) == 0xa0, "");

} // namespace gf
