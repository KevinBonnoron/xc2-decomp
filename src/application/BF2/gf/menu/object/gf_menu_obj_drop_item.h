#pragma once
#include "gf/menu/gf_menu_many_objects.h"
#include "gf/menu/gf_menu_object.h"
#include "types.h"
#include "ui/ui_object_acc.h"

namespace gf {

class GfMenuObjDropItem : public GfMenuObject {
public:
  // Queued by GfMenuManyObjects; the game gives it its own vtable, inheriting the dispose of the base.
  struct DropItemInfo : GfMenuManyObjects::InfoType {};

  GfMenuObjDropItem(u32 handle);
  ~GfMenuObjDropItem() override;
  void initialize() override;
  void finalize() override;
  void update() override;
  static void removeObject(ui::UIObjectAcc acc);
  static void setupPlugin(u32 handle, u32 type);
  static void close(u32 handle);
  static void closeAll();
};

static_assert(sizeof(GfMenuObjDropItem::DropItemInfo) == 0x10, "");

} // namespace gf
