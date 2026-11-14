#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "gf/menu/gf_menu_reference_list.h"
#include "mm_mtl/intrusive_ptr.h"
#include "types.h"
#include "ui/event/ui_object_listener.h"

namespace ui {
class UICtrlCursorSelect;
class UICtrlSlideSelect;
class UISelectObjList;
} // namespace ui

namespace gf {

class GfMenuItemList;

class GfMenuObjItemList : public GfMenuObject {
public:
  class MainListener : public ui::UIObjectListener {
  public:
    MainListener(GfMenuObjItemList *owner) : _0c(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x1c - 0x0c];          // Actively zero-initialized unknown byte range, NOT padding; original name/role unknown.
    GfMenuObjItemList *unknown20; // Inferred role: owner; original member name unknown.
  };

  class TypeListener : public ui::UIObjectListener {
  public:
    TypeListener(GfMenuObjItemList *owner) : _0c(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x1c - 0x0c];          // Actively zero-initialized unknown byte range, NOT padding; original name/role unknown.
    GfMenuObjItemList *unknown20; // Inferred role: owner; original member name unknown.
  };

  class ListListener : public ui::UIObjectListener {
  public:
    ListListener(GfMenuObjItemList *owner) : _0c(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x1c - 0x0c];          // Actively zero-initialized unknown byte range, NOT padding; original name/role unknown.
    GfMenuObjItemList *unknown20; // Inferred role: owner; original member name unknown.
  };

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

static_assert(offsetof(GfMenuObjItemList::MainListener, unknown20) == 0x20, "");
static_assert(sizeof(GfMenuObjItemList::MainListener) == 0x28, "");
static_assert(offsetof(GfMenuObjItemList::TypeListener, unknown20) == 0x20, "");
static_assert(sizeof(GfMenuObjItemList::TypeListener) == 0x28, "");
static_assert(offsetof(GfMenuObjItemList::ListListener, unknown20) == 0x20, "");
static_assert(sizeof(GfMenuObjItemList::ListListener) == 0x28, "");
static_assert(offsetof(GfMenuObjItemList, unknown28) == 0x28, "");
static_assert(offsetof(GfMenuObjItemList, unknown30) == 0x30, "");
static_assert(offsetof(GfMenuObjItemList, unknown38) == 0x38, "");
static_assert(offsetof(GfMenuObjItemList, unknown40) == 0x40, "");
static_assert(offsetof(GfMenuObjItemList, unknown48) == 0x48, "");
static_assert(offsetof(GfMenuObjItemList, unknownf0) == 0xf0, "");

} // namespace gf
