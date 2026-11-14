#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "mm_mtl/intrusive_ptr.h"
#include "types.h"
#include "ui/event/ui_object_listener.h"

namespace ui {
class UICtrlCursorSelect;
class UIObjectAcc;
} // namespace ui

namespace gf {

class GfMenuCallContext;
class GfMenuItemList;
class GfMenuReferenceItem;

class GfMenuObjPouch : public GfMenuObject {
public:
  class MainListener : public ui::UIObjectListener {
  public:
    MainListener(GfMenuObjPouch *owner) : _0c(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x1c - 0x0c];       // Actively zero-initialized unknown byte range, NOT padding; original name/role unknown.
    GfMenuObjPouch *unknown20; // Inferred role: owner; original member name unknown.
  };

  class DescriptionListener : public ui::UIObjectListener {
  public:
    DescriptionListener(GfMenuObjPouch *owner) : _0c(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x1c - 0x0c];       // Actively zero-initialized unknown byte range, NOT padding; original name/role unknown.
    GfMenuObjPouch *unknown20; // Inferred role: owner; original member name unknown.
  };

  class PouchListener : public ui::UIObjectListener {
  public:
    PouchListener(GfMenuObjPouch *owner) : _0c(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x1c - 0x0c];       // Actively zero-initialized unknown byte range, NOT padding; original name/role unknown.
    GfMenuObjPouch *unknown20; // Inferred role: owner; original member name unknown.
  };

  class ItemListListener : public ui::UIObjectListener {
  public:
    ItemListListener(GfMenuObjPouch *owner) : _0c(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x1c - 0x0c];       // Actively zero-initialized unknown byte range, NOT padding; original name/role unknown.
    GfMenuObjPouch *unknown20; // Inferred role: owner; original member name unknown.
  };

  GfMenuObjPouch(u32 handle);
  ~GfMenuObjPouch() override;
  static void sendEvent(u32 handle, u32 type, u32 param);
  static int setFadeIn(u32 handle);
  static int setFadeOut(u32 handle);
  void initialize() override;
  void finalize() override;
  void update() override;
  static void setupPouch(ui::UIObjectAcc &);
  static void updateItemList(GfMenuItemList *list);
  static void setupItemList(ui::UIObjectAcc &acc, GfMenuItemList *list);
  static void setupDescription(ui::UIObjectAcc &acc, mm::mtl::IntrusivePtr<GfMenuReferenceItem> &item);

  u8 _24[0x28 - 0x24];
  GfMenuItemList *unknown28;                            // Inferred role: items; original member name unknown.
  ui::UICtrlCursorSelect *unknown30;                    // Inferred role: item cursor; original member name unknown.
  ui::UICtrlCursorSelect *unknown38;                    // Inferred role: pouch cursor; original member name unknown.
  GfMenuCallContext *unknown40;                         // Inferred role: call context; original member name unknown.
  u32 unknown48;                                        // Inferred role: selected pouch slot; original member name unknown.
  u32 unknown4c;                                        // Inferred role: shown window; original member name unknown.
  mm::mtl::IntrusivePtr<GfMenuReferenceItem> unknown50; // Inferred role: reference item; original member name unknown.
};

static_assert(offsetof(GfMenuObjPouch, unknown28) == 0x28, "");
static_assert(offsetof(GfMenuObjPouch, unknown30) == 0x30, "");
static_assert(offsetof(GfMenuObjPouch, unknown38) == 0x38, "");
static_assert(offsetof(GfMenuObjPouch, unknown40) == 0x40, "");
static_assert(offsetof(GfMenuObjPouch, unknown48) == 0x48, "");
static_assert(offsetof(GfMenuObjPouch, unknown4c) == 0x4c, "");
static_assert(offsetof(GfMenuObjPouch, unknown50) == 0x50, "");
static_assert(offsetof(GfMenuObjPouch::MainListener, unknown20) == 0x20, "");
static_assert(sizeof(GfMenuObjPouch::MainListener) == 0x28, "");
static_assert(offsetof(GfMenuObjPouch::DescriptionListener, unknown20) == 0x20, "");
static_assert(sizeof(GfMenuObjPouch::DescriptionListener) == 0x28, "");
static_assert(offsetof(GfMenuObjPouch::PouchListener, unknown20) == 0x20, "");
static_assert(sizeof(GfMenuObjPouch::PouchListener) == 0x28, "");
static_assert(offsetof(GfMenuObjPouch::ItemListListener, unknown20) == 0x20, "");
static_assert(sizeof(GfMenuObjPouch::ItemListListener) == 0x28, "");

} // namespace gf
