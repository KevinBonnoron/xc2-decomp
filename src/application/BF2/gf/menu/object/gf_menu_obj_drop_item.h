#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_many_objects.h"
#include "gf/menu/gf_menu_object.h"
#include "types.h"
#include "ui/event/ui_object_listener.h"
#include "ui/ui_object_acc.h"

namespace gf {

class GfMenuObjDropItem : public GfMenuObject {
public:
  // Queued by GfMenuManyObjects; the game gives it its own vtable, inheriting the dispose of the base.
  struct DropItemInfo : GfMenuManyObjects::InfoType {};

  class ListListener : public ui::UIObjectListener {
  public:
    ListListener(GfMenuObjDropItem *owner) : _0c(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x1c - 0x0c];
    u8 _1c[0x20 - 0x1c];
    GfMenuObjDropItem *unknown20; // Inferred role: owner; original member name unknown.
  };

  GfMenuObjDropItem(u32 handle);
  ~GfMenuObjDropItem() override;
  void initialize() override;
  void finalize() override;
  void update() override;
  static void removeObject(ui::UIObjectAcc acc);
  static void setupPlugin(u32 handle, u32 type);
  static void setupScreen(u32 handle, int type, int number, int item);
  static void close(u32 handle);
  static void closeAll();
};

static_assert(sizeof(GfMenuObjDropItem::DropItemInfo) == 0x10, "");
static_assert(offsetof(GfMenuObjDropItem::ListListener, unknown20) == 0x20, "");
static_assert(sizeof(GfMenuObjDropItem::ListListener) == 0x28, "");

} // namespace gf
