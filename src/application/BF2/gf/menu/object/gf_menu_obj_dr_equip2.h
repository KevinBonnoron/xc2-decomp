#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "mm_mtl/intrusive_ptr.h"
#include "types.h"
#include "ui/event/ui_object_listener.h"

namespace mm {
namespace mtl {
class ReferenceObject;
} // namespace mtl
} // namespace mm

namespace ui {
class UIObjectAcc;
class UISelectObjList;
} // namespace ui

namespace gf {

class GfMenuCallContext;
class GfMenuDriverList;
class GfMenuItemList;
class GfMenuReferenceItem;

class GfMenuObjDrEquip2 : public GfMenuObject {
public:
  class MainListener : public ui::UIObjectListener {
  public:
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x20 - 0x0c];
    GfMenuObjDrEquip2 *unknown20; // Inferred role: owner; original member name unknown.
  };

  GfMenuObjDrEquip2(u32 handle);
  ~GfMenuObjDrEquip2() override;
  static void sendEvent(u32 handle, u32 type, u32 param);
  static int setFadeIn(u32 handle, u32 type);
  static int setFadeOut(u32 handle, u32 type);
  void initialize() override;
  void finalize() override;
  void update() override;
  static void setupEquipItem(ui::UIObjectAcc &acc, GfMenuItemList *list);

  u32 unknown24;  // Role and original member name unknown, cleared by the constructor.
  bool unknown28; // Role and original member name unknown, cleared by the constructor.
  u8 _29[0x30 - 0x29];
  GfMenuItemList *unknown30;                            // Inferred role: equipment items; original member name unknown.
  mm::mtl::ReferenceObject *unknown38;                  // Inferred role: reference-counted object; type and original member name unknown.
  GfMenuItemList *unknown40;                            // Inferred role: filtered items; original member name unknown.
  ui::UISelectObjList *unknown48;                       // Inferred role: item objects; original member name unknown.
  mm::mtl::ReferenceObject *unknown50;                  // Inferred role: reference-counted object; type and original member name unknown.
  mm::mtl::IntrusivePtr<GfMenuReferenceItem> unknown58; // Inferred role: reference item; original member name unknown.
  GfMenuCallContext *unknown60;                         // Inferred role: call context; original member name unknown.
  GfMenuDriverList *unknown68;                          // Inferred role: drivers; original member name unknown.
  GfMenuCallContext *unknown70;                         // Inferred role: call context; original member name unknown.
  u8 _78[0x7c - 0x78];
  u32 unknown7c; // Role and original member name unknown, cleared by the constructor.
};

static_assert(offsetof(GfMenuObjDrEquip2::MainListener, unknown20) == 0x20, "");
static_assert(offsetof(GfMenuObjDrEquip2, unknown24) == 0x24, "");
static_assert(offsetof(GfMenuObjDrEquip2, unknown28) == 0x28, "");
static_assert(offsetof(GfMenuObjDrEquip2, unknown30) == 0x30, "");
static_assert(offsetof(GfMenuObjDrEquip2, unknown38) == 0x38, "");
static_assert(offsetof(GfMenuObjDrEquip2, unknown40) == 0x40, "");
static_assert(offsetof(GfMenuObjDrEquip2, unknown48) == 0x48, "");
static_assert(offsetof(GfMenuObjDrEquip2, unknown50) == 0x50, "");
static_assert(offsetof(GfMenuObjDrEquip2, unknown58) == 0x58, "");
static_assert(offsetof(GfMenuObjDrEquip2, unknown60) == 0x60, "");
static_assert(offsetof(GfMenuObjDrEquip2, unknown68) == 0x68, "");
static_assert(offsetof(GfMenuObjDrEquip2, unknown70) == 0x70, "");
static_assert(offsetof(GfMenuObjDrEquip2, unknown7c) == 0x7c, "");
static_assert(sizeof(GfMenuObjDrEquip2) == 0x80, "");

} // namespace gf
