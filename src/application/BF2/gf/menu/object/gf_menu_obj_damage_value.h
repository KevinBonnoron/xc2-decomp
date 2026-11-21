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
    DamageInfo() {}
    DamageInfo(u32 handle, const mm::Vec3 &position) : InfoType(handle), unknown10(position) {}

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
  // Layout from open (0x7100445578): the three words and the flags are read there; original member names unknown.
  struct OpenParam {
    u32 unknown00; // Inferred role: kind of damage text; original member name unknown.
    u32 unknown04; // Inferred role: amount, formatted with "%d"; original member name unknown.
    u32 unknown08; // Inferred role: target, narrowed to 16 bits in the event; original member name unknown.
    u32 unknown0c; // Inferred role: damage level, its low two bits shifted by three in the event flags; original member name unknown.
    u8 unknown10;  // Inferred role: bit 0 of the event flags, which scales the number in setupScreen; original member name unknown.
    u8 unknown11;  // Inferred role: bit 1 of the event flags, which ListListener::reciveEvent uses to choose its control; original member name unknown.
    u8 unknown12;  // Inferred role: bit 2 of the event flags, which shows the IMG_spbg background in setupScreen; original member name unknown.
    u8 _13[0x20 - 0x13];
    mm::Vec3 unknown20; // Inferred role: world position; original member name unknown.
  };

  static u32 open(const OpenParam &param);
  static void setupScreen(u32 handle, int type, int text, int target, int flags);
  static void removeObject(ui::UIObjectAcc acc);
  static void close(u32 handle);
  static void closeAll();
};

static_assert(offsetof(GfMenuObjDamageValue::DamageInfo, unknown10) == 0x10, "");
static_assert(sizeof(GfMenuObjDamageValue::DamageInfo) == 0x20, "");
static_assert(offsetof(GfMenuObjDamageValue::OpenParam, unknown20) == 0x20, "");
static_assert(sizeof(GfMenuObjDamageValue::OpenParam) == 0x30, "");
static_assert(offsetof(GfMenuObjDamageValue::ListListener, unknown20) == 0x20, "");
static_assert(sizeof(GfMenuObjDamageValue::ListListener) == 0x28, "");

} // namespace gf
