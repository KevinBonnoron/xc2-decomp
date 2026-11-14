#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_many_objects.h"
#include "gf/menu/gf_menu_object.h"
#include "mm_math/mm_vec3.h"
#include "types.h"
#include "ui/event/ui_object_listener.h"
#include "ui/ui_object_acc.h"

namespace gf {

class GfMenuObjDamageValue : public GfMenuObject {
public:
  // Queued by GfMenuManyObjects; the game gives it its own vtable, inheriting the dispose of the base. Layout from open, which compares
  // the position with the queued ones.
  struct DamageInfo : GfMenuManyObjects::InfoType {
    mm::Vec3 unknown10; // Inferred role: position of the damage value; original member name unknown.
  };

  class ListListener : public ui::UIObjectListener {
  public:
    ListListener(GfMenuObjDamageValue *owner) : _0c(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x1c - 0x0c];
    u8 _1c[0x20 - 0x1c];
    GfMenuObjDamageValue *unknown20; // Inferred role: owner; original member name unknown.
  };

  GfMenuObjDamageValue(u32 handle);
  ~GfMenuObjDamageValue() override;
  void initialize() override;
  void finalize() override;
  void update() override;
  static void removeObject(ui::UIObjectAcc acc);
  static void close(u32 handle);
  static void closeAll();
};

static_assert(offsetof(GfMenuObjDamageValue::DamageInfo, unknown10) == 0x10, "");
static_assert(sizeof(GfMenuObjDamageValue::DamageInfo) == 0x20, "");
static_assert(offsetof(GfMenuObjDamageValue::ListListener, unknown20) == 0x20, "");
static_assert(sizeof(GfMenuObjDamageValue::ListListener) == 0x28, "");

} // namespace gf
