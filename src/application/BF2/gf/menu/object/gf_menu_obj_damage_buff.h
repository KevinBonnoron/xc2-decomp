#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_many_objects.h"
#include "gf/menu/gf_menu_object.h"
#include "mm_math/mm_vec3.h"
#include "types.h"
#include "ui/event/ui_object_listener.h"
#include "ui/ui_object_acc.h"

namespace gf {

class GfMenuObjDamageBuff : public GfMenuObject {
public:
  // Queued by GfMenuManyObjects; the game gives it its own vtable, inheriting the dispose of the base.
  struct DamageInfo : GfMenuManyObjects::InfoType {};

  class ListListener : public ui::UIObjectListener {
  public:
    ListListener(GfMenuObjDamageBuff *owner) : _0c(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x1c - 0x0c];
    GfMenuObjDamageBuff *unknown20; // Inferred role: owner; original member name unknown.
  };

  GfMenuObjDamageBuff(u32 handle);
  ~GfMenuObjDamageBuff() override;
  void initialize() override;
  void finalize() override;
  void update() override;
  static void closeAll();
  struct OpenParam {
    OpenParam() : unknown04(0), unknown05(0), unknown08(nullptr), unknown10(nullptr), unknown18(0), unknown1c(0) {}

    u32 unknown00; // Role and original member name unknown.
    u8 unknown04;  // Role and original member name unknown.
    u8 unknown05;  // Role and original member name unknown.
    u8 _06[0x08 - 0x06];
    const char *unknown08; // Inferred role: text used when there is no bdat; original member name unknown.
    u8 *unknown10;         // Inferred role: bdat; original member name unknown.
    u32 unknown18;         // Inferred role: text id; original member name unknown.
    u32 unknown1c;         // Inferred role: icon id; original member name unknown.
    mm::Vec3 unknown20;    // Inferred role: position; original member name unknown.
  };

  struct OpenUniteParam {
    int unknown00; // Role and original member name unknown.
    int unknown04; // Role and original member name unknown.
    u8 _08[0x10 - 0x08];
    mm::Vec3 unknown10; // Inferred role: position; original member name unknown.
  };

  static u32 open(const OpenParam &param);
  static void close(u32 handle);
  static u32 openUniteCombo(const OpenUniteParam &param);
  static void closeUniteCombo(u32 handle);
  static void removeObject(ui::UIObjectAcc acc);
  static void setupPlugin(u32 handle);
  static void setupScreen(u32 handle, int color, int resist, int name, int);
};

static_assert(sizeof(GfMenuObjDamageBuff::DamageInfo) == 0x10, "");
static_assert(offsetof(GfMenuObjDamageBuff::OpenParam, unknown10) == 0x10, "");
static_assert(offsetof(GfMenuObjDamageBuff::OpenParam, unknown20) == 0x20, "");
static_assert(sizeof(GfMenuObjDamageBuff::OpenParam) == 0x30, "");
static_assert(offsetof(GfMenuObjDamageBuff::OpenUniteParam, unknown10) == 0x10, "");
static_assert(sizeof(GfMenuObjDamageBuff::OpenUniteParam) == 0x20, "");
static_assert(offsetof(GfMenuObjDamageBuff::ListListener, unknown20) == 0x20, "");
static_assert(sizeof(GfMenuObjDamageBuff::ListListener) == 0x28, "");

} // namespace gf
